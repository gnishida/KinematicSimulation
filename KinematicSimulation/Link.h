#pragma once

#include <glm/glm.hpp>
#include <boost/shared_ptr.hpp>

namespace kinematics {

	class Joint;

	class Link {
	public:
		int start;
		int end;
		double length;
		bool driver;
		double theta;

	public:
		Link() {}
		Link(boost::shared_ptr<Joint> start_point, boost::shared_ptr<Joint> end_point, bool driver);
		void stepForward(double step_size);
		glm::dvec2 forwardKinematics(glm::dvec2& start_pos);
	};

}