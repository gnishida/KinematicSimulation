#include "Utils.h"

namespace kinematics {

	glm::dvec2 circleCircleIntersection(const glm::dvec2& center1, double radius1, const glm::dvec2& center2, double radius2) {
		glm::dvec2 dir = center2 - center1;
		double d = glm::length(dir);
		if (d > radius1 + radius2 || d < abs(radius1 - radius2)) {
			throw "No intersection";
		}

		double a = (radius1 * radius1 - radius2 * radius2 + d * d) / d / 2.0;
		double h = sqrt(radius1 * radius1 - a * a);

		glm::dvec2 perp(dir.y, -dir.x);
		perp /= glm::length(perp);

		return center1 + dir * a / d + perp * h;
	}

	/**
	 * Find the intersection that is further from p1
	 */
	glm::dvec2 circleLineIntersection(const glm::dvec2& center, double radius, const glm::dvec2& p1, const glm::dvec2& p2) {
		glm::dvec2 dir = p2 - p1;
		dir /= glm::length(dir);

		glm::dvec2 n(-dir.y, dir.x);

		double d = glm::dot(p1 - center, n);
		double h = sqrt(radius * radius - d * d);

		if (abs(d) > radius) {
			throw "No intersection";
		}

		return center + n * d - dir * h;
	}

}