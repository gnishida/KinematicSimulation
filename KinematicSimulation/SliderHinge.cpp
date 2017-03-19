#include "SliderHinge.h"
#include "Link.h"
#include "Utils.h"

namespace kinematics {

	SliderHinge::SliderHinge(int id, const glm::dvec2& pos) {
		this->id = id;
		this->type = TYPE_SLIDER_HINGE;
		this->pos = pos;
	}

	SliderHinge::SliderHinge(QDomElement& node) {
		id = node.attribute("id").toInt();
		type = TYPE_SLIDER_HINGE;
		pos.x = node.attribute("x").toDouble();
		pos.y = node.attribute("y").toDouble();
	}

	void SliderHinge::init(const QMap<int, boost::shared_ptr<Joint>>& joints) {
		if (in_links.size() > 0) {
			glm::dvec2 pt = joints[in_links[0]->start]->pos;
			theta = atan2(pt.y - pos.y, pt.x - pos.x);
		}
		else {
			theta = 0;
		}
	}

	void SliderHinge::draw(QPainter& painter) {
		painter.save();
		painter.setPen(QPen(QColor(0, 0, 0), 1));
		painter.setBrush(QBrush(QColor(255, 255, 255)));

		painter.translate(pos.x, 800 - pos.y);
		painter.rotate(-theta);
		painter.drawRect(-20, -5, 40, 10);

		painter.drawEllipse(QPoint(0, 0), 5, 5);
		painter.restore();
	}

	void SliderHinge::stepForward(double step_size) {
	}

	/**
	* Update the position of this joint.
	* Return true if the position is updated.
	* Return false if one of the positions of the parent nodes has not been updated yet.
	*/
	bool SliderHinge::forwardKinematics(const QMap<int, boost::shared_ptr<Joint>>& joints, const QMap<int, bool>& updated) {
		if (in_links.size() == 0) return true;

		if (in_links.size() > 2) throw "forward kinematics error. Overconstrained.";

		// if the parent points are not updated, postpone updating this point
		boost::shared_ptr<Link> l1 = in_links[0];
		if (!updated[l1->start]) {
			return false;
		}
		if (in_links.size() == 2) {
			boost::shared_ptr<Link> l2 = in_links[1];
			if (!updated[l2->start]) {
				return false;
			}

			// update this point based on two adjacent points
			glm::dvec2 p2 = joints[l1->start]->pos + glm::dvec2(cos(theta), sin(theta));
			pos = circleLineIntersection(joints[l2->start]->pos, l2->length, joints[l1->start]->pos, p2);
		}
		else {
			// pin joint
			pos = l1->forwardKinematics(joints[l1->start]->pos);
		}
	}

}