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

		void init(const QMap<int, boost::shared_ptr<Joint>>& joints);
		void draw(QPainter& painter);
		bool forwardKinematics(const QMap<int, boost::shared_ptr<Joint>>& joints, const QMap<int, bool>& updated);
	};

}
