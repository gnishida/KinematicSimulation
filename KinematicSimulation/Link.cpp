#include "Link.h"
#include "Joint.h"

namespace kinematics {

	Link::Link(boost::shared_ptr<Joint> start, boost::shared_ptr<Joint> end, bool driver) {
		this->start = start->id;
		this->end = end->id;
		this->length = glm::length(start->pos - end->pos);
		this->driver = driver;
		this->theta = atan2(end->pos.y - start->pos.y, end->pos.x - start->pos.x);
	}

	void Link::stepForward(double step_size) {
		theta += step_size;
	}

	glm::dvec2 Link::forwardKinematics(glm::dvec2& start_pos) {
		return start_pos + glm::dvec2(cos(theta), sin(theta)) * length;
	}

}