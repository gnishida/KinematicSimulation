#pragma once

#include "Joint.h"
#include <QDomDocument>

namespace kinematics {

	class Gear : public Joint {
	private:
		glm::dvec2 center;
		double radius;
		double speed;
		double phase;

	public:
		Gear(int id, const glm::dvec2& pos, double radius, double speed, double phase);
		Gear(QDomElement& node);

		void init(const QMap<int, boost::shared_ptr<Joint>>& joints);
		void draw(QPainter& painter);
		void stepForward(double step_size);
		bool forwardKinematics(const QMap<int, boost::shared_ptr<Joint>>& joints, const QMap<int, bool>& updated);
	};

}