#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace kinematics {

	class Link;

	class Joint {
	public:
		int id;
		glm::dvec2 pos;
		std::vector<boost::shared_ptr<Link>> out_links;
		std::vector<boost::shared_ptr<Link>> in_links;
	};

}