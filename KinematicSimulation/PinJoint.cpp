#include "PinJoint.h"
#include "Link.h"
#include "Utils.h"

namespace kinematics {

	PinJoint::PinJoint(int id, const glm::dvec2& pos) {
		this->id = id;
		this->type = TYPE_PIN;
		this->pos = pos;
	}

	PinJoint::PinJoint(QDomElement& node) {
		id = node.attribute("id").toInt();
		this->type = TYPE_PIN;
		pos.x = node.attribute("x").toDouble();
		pos.y = node.attribute("y").toDouble();
	}

	void PinJoint::init(const QMap<int, boost::shared_ptr<Joint>>& joints) {
	}

	void PinJoint::draw(QPainter& painter) {
		painter.save();
		painter.setPen(QPen(QColor(0, 0, 0), 1));
		painter.setBrush(QBrush(QColor(255, 255, 255)));
		painter.drawEllipse(QPoint(pos.x, 800 - pos.y), 5, 5);
		painter.restore();
	}

	void PinJoint::stepForward(double step_size) {
	}

	/**
	 * Update the position of this joint.
	 * Return true if the position is updated.
	 * Return false if one of the positions of the parent nodes has not been updated yet.
	 */
	bool PinJoint::forwardKinematics(const QMap<int, boost::shared_ptr<Joint>>& joints, const QMap<int, bool>& updated) {
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
			pos = circleCircleIntersection(joints[l1->start]->pos, l1->length, joints[l2->start]->pos, l2->length);
		}
		else {
			// pin joint
			pos = l1->forwardKinematics(joints[l1->start]->pos);
		}
	}

}