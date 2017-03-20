#include "Kinematics.h"
#include <iostream>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QDate>
#include "PinJoint.h"
#include "SliderHinge.h"
#include "Gear.h"
#include "Utils.h"

namespace kinematics {
	Kinematics::Kinematics() {
		show_assemblies = true;
		show_links = true;
		show_bodies = true;
	}

	void Kinematics::load(const QString& filename) {
		QFile file(filename);
		if (!file.open(QFile::ReadOnly | QFile::Text)) throw "Fild cannot open.";

		QDomDocument doc;
		doc.setContent(&file);

		QDomElement root = doc.documentElement();
		if (root.tagName() != "design")	throw "Invalid file format.";

		// clear the data
		joints.clear();
		links.clear();
		bodies.clear();
		trace_end_effector.clear();

		QDomNode node = root.firstChild();
		while (!node.isNull()) {
			if (node.toElement().tagName() == "joints") {
				QDomNode joint_node = node.firstChild();
				while (!joint_node.isNull()) {
					if (joint_node.toElement().tagName() == "joint") {
						// add a joint
						int id = joint_node.toElement().attribute("id").toInt();
						if (joint_node.toElement().attribute("type") == "pin") {
							joints[id] = boost::shared_ptr<Joint>(new PinJoint(joint_node.toElement()));
						}
						else if (joint_node.toElement().attribute("type") == "slider_hinge") {
							joints[id] = boost::shared_ptr<Joint>(new SliderHinge(joint_node.toElement()));
						}
						else if (joint_node.toElement().attribute("type") == "gear") {
							joints[id] = boost::shared_ptr<Joint>(new Gear(joint_node.toElement()));
						}

					}

					joint_node = joint_node.nextSibling();
				}
			}
			else if (node.toElement().tagName() == "links") {
				QDomNode link_node = node.firstChild();
				while (!link_node.isNull()) {
					if (link_node.toElement().tagName() == "link") {
						// add a link
						int start = link_node.toElement().attribute("start").toInt();
						int end = link_node.toElement().attribute("end").toInt();
						bool driver = link_node.toElement().attribute("driver").toLower() == "true" ? true : false;
						int order = link_node.toElement().attribute("order").toInt();
						boost::shared_ptr<Link> link = boost::shared_ptr<Link>(new Link(joints[start], joints[end], driver));
						links.push_back(link);

						// set outgoing link to the point
						joints[start]->out_links.push_back(link);

						// set incoming link to the point
						if (joints[end]->in_links.size() < order + 1) joints[end]->in_links.resize(order + 1);
						joints[end]->in_links[order] = link;
					}

					link_node = link_node.nextSibling();
				}
			}
			else if (node.toElement().tagName() == "bodies") {
				QDomNode body_node = node.firstChild();
				while (!body_node.isNull()) {
					if (body_node.toElement().tagName() == "body") {
						// add a body
						int id1 = body_node.toElement().attribute("id1").toInt();
						int id2 = body_node.toElement().attribute("id2").toInt();
						Body body(id1, id2);

						// setup rotation matrix
						glm::vec2 dir = joints[id2]->pos - joints[id1]->pos;
						double angle = atan2(dir.y, dir.x);
						
						//glm::dvec2 p1 = (joints[id1]->pos + joints[id2]->pos) * 0.5;
						glm::dvec2 p1 = joints[id1]->pos;
						glm::dmat4x4 model;
						model = glm::rotate(model, -angle, glm::dvec3(0, 0, 1));						
												
						QDomNode point_node = body_node.firstChild();
						while (!point_node.isNull()) {
							if (point_node.toElement().tagName() == "point") {
								double x = point_node.toElement().attribute("x").toDouble();
								double y = point_node.toElement().attribute("y").toDouble();

								// convert the coordinates to the local coordinate system
								glm::dvec2 rotated_p = glm::dvec2(model * glm::dvec4(x - p1.x, y - p1.y, 0, 1));
								
								body.points.push_back(rotated_p);
							}

							point_node = point_node.nextSibling();
						}

						bodies.push_back(body);
					}

					body_node = body_node.nextSibling();
				}
			}

			node = node.nextSibling();
		}
		
		// initialize joints
		for (auto it = joints.begin(); it != joints.end(); ++it) {
			it.value()->init(joints);
		}

		//trace_end_effector.resize(assemblies.size());
	}

	void Kinematics::save(const QString& filename) {
		QFile file(filename);
		if (!file.open(QFile::WriteOnly)) throw "File cannot open.";

		QDomDocument doc;

		// set root node
		QDomElement root = doc.createElement("design");
		root.setAttribute("author", "Gen Nishida");
		root.setAttribute("version", "1.0");
		root.setAttribute("date", QDate::currentDate().toString("MM/dd/yyyy"));
		doc.appendChild(root);

		// write points
		QDomElement points_node = doc.createElement("points");
		root.appendChild(points_node);
		for (auto it = joints.begin(); it != joints.end(); ++it) {
			QDomElement point_node = doc.createElement("point");
			point_node.setAttribute("id", it.key());
			point_node.setAttribute("x", it.value()->pos.x);
			point_node.setAttribute("y", it.value()->pos.y);
			points_node.appendChild(point_node);
		}

		// write links
		QDomElement links_node = doc.createElement("links");
		root.appendChild(links_node);
		for (auto it = joints.begin(); it != joints.end(); ++it) {
			for (int j = 0; j < it.value()->in_links.size(); ++j) {
				QDomElement link_node = doc.createElement("link");
				link_node.setAttribute("order", j);
				link_node.setAttribute("start", it.value()->in_links[j]->start);
				link_node.setAttribute("end", it.value()->in_links[j]->end);
				links_node.appendChild(link_node);
			}
		}

		// write bodies
		QDomElement bodies_node = doc.createElement("bodies");
		root.appendChild(bodies_node);
		for (int i = 0; i < bodies.size(); ++i) {
			QDomElement body_node = doc.createElement("body");
			body_node.setAttribute("id1", bodies[i].pivot1);
			body_node.setAttribute("id2", bodies[i].pivot2);
			bodies_node.appendChild(body_node);

			// setup rotation matrix
			glm::dvec2 dir = joints[bodies[i].pivot2]->pos - joints[bodies[i].pivot1]->pos;
			double angle = atan2(dir.y, dir.x);
			glm::dvec2 p1 = (joints[bodies[i].pivot1]->pos + joints[bodies[i].pivot2]->pos) * 0.5;
			glm::dmat4x4 model;
			model = glm::rotate(model, angle, glm::dvec3(0, 0, 1));
			
			for (int k = 0; k < bodies[i].points.size(); ++k) {
				// convert the coordinates to the local coordinate system
				glm::dvec2 rotated_p = glm::dvec2(model * glm::vec4(bodies[i].points[k].x, bodies[i].points[k].y, 0, 1)) + p1;
				QDomElement point_node = doc.createElement("point");
				point_node.setAttribute("x", rotated_p.x);
				point_node.setAttribute("y", rotated_p.y);
				body_node.appendChild(point_node);
			}
		}

		QTextStream out(&file);
		doc.save(out, 4);
	}

	void Kinematics::forwardKinematics() {
		try {
			std::list<boost::shared_ptr<Joint>> queue;
			for (auto it = joints.begin(); it != joints.end(); ++it) {
				queue.push_back(*it);
			}

			QMap<int, bool> updated;
			for (auto it = joints.begin(); it != joints.end(); ++it) {
				updated[it.key()];
			}

			while (!queue.empty()) {
				boost::shared_ptr<Joint> joint = queue.front();
				queue.pop_front();

				if (joint->forwardKinematics(joints, updated)) {
					updated[joint->id] = true;
				}
				else {
					queue.push_back(joint);
				}
			}
		}
		catch (char* ex) {
			throw "forward kinematics error.";
		}
	}

	void Kinematics::stepForward(double time_step) {
		for (int i = 0; i < links.size(); ++i) {
			if (links[i]->driver) {
				if (joints[links[i]->start]->type == Joint::TYPE_GEAR) {
					joints[links[i]->start]->stepForward(time_step);
				}
				else {
					links[i]->stepForward(time_step);
				}
			}
		}

		try {
			forwardKinematics();
		}
		catch (char* ex) {
			for (int i = 0; i < links.size(); ++i) {
				if (links[i]->driver) {
					if (joints[links[i]->start]->type == Joint::TYPE_GEAR) {
						joints[links[i]->start]->stepForward(-time_step);
					}
					else {
						links[i]->stepForward(-time_step);
					}
				}
			}
			throw ex;
		}
	}

	void Kinematics::draw(QPainter& painter) {
		if (show_bodies) {
			for (int i = 0; i < bodies.size(); ++i) {
				painter.save();
				painter.setPen(QPen(QColor(0, 0, 0), 1));
				painter.setBrush(QBrush(QColor(0, 255, 0, 60)));
				glm::dvec2 dir = joints[bodies[i].pivot2]->pos - joints[bodies[i].pivot1]->pos;
				double angle = atan2(-dir.y, dir.x) / M_PI * 180;
				//glm::dvec2 p1 = (joints[bodies[i].pivot1]->pos + joints[bodies[i].pivot2]->pos) * 0.5;
				glm::dvec2 p1 = joints[bodies[i].pivot1]->pos;
				painter.translate(p1.x, 800 - p1.y);
				painter.rotate(angle);
				std::vector<QPointF> points;
				for (int k = 0; k < bodies[i].points.size(); ++k) {
					points.push_back(QPointF(bodies[i].points[k].x, -bodies[i].points[k].y));
				}
				painter.drawPolygon(points.data(), points.size());
				painter.restore();
			}
		}

		if (show_links) {
			// draw links
			painter.setPen(QPen(QColor(0, 0, 0), 3));
			painter.setBrush(QBrush(QColor(255, 255, 255)));
			for (int i = 0; i < links.size(); ++i) {
				painter.drawLine(joints[links[i]->start]->pos.x, 800 - joints[links[i]->start]->pos.y, joints[links[i]->end]->pos.x, 800 - joints[links[i]->end]->pos.y);
				joints[links[i]->start]->draw(painter);
				joints[links[i]->end]->draw(painter);
			}
		}
	}

	void Kinematics::showAssemblies(bool flag) {
		show_assemblies = flag;
	}

	void Kinematics::showLinks(bool flag) {
		show_links = flag;
	}

	void Kinematics::showBodies(bool flag) {
		show_bodies = flag;
	}

}
