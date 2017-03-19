#pragma once

#include "Joint.h"
#include <QDomDocument>

namespace kinematics {

	class SliderHinge : public Joint {
	private:
		double theta;

	public:
		SliderHinge(int id, const glm::dvec2& pos);
		SliderHinge(QDomElement& node);

		void init(const QMap<int, boost::shared_ptr<Joint>>& joints);
		bool forwardKinematics(const QMap<int, boost::shared_ptr<Joint>>& joints, const QMap<int, bool>& updated);
	};

}