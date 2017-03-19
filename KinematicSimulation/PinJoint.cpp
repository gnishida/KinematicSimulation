#include "PinJoint.h"

namespace kinematics {

	PinJoint::PinJoint(int id, const glm::dvec2& pos) {
		this->id = id;
		this->pos = pos;
	}

	PinJoint::PinJoint(QDomElement& node) {
		id = node.attribute("id").toInt();
		pos.x = node.attribute("x").toFloat();
		pos.y = node.attribute("y").toFloat();
	}

}