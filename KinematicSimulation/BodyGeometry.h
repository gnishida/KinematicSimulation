#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>
#include <glm/glm.hpp>

namespace kinematics {

	class Joint;

	class BodyGeometry {
	public:
		boost::shared_ptr<Joint> pivot1;
		boost::shared_ptr<Joint> pivot2;
		std::vector<glm::dvec2> points;

	public:
		BodyGeometry(boost::shared_ptr<Joint> pivot1, boost::shared_ptr<Joint> pivot2) : pivot1(pivot1), pivot2(pivot2) {}
	};

}