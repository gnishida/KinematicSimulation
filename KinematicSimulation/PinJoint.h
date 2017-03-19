#pragma once

#include "Joint.h"
#include <QDomDocument>

namespace kinematics {

	class PinJoint : public Joint {
	private:
		double theta;

	public:
		PinJoint(int id, const glm::dvec2& pos);
		PinJoint(QDomElement& node);
	};

}
