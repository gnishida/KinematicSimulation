#include "BodyGeometry.h"
#include "Joint.h"
#include "Utils.h"

namespace kinematics {

	/**
	 * Get the actual coordinates of the body geometry.
	 * Note that "points" store the original coordinates in the model coordinate system.
	 */
	std::vector<glm::dvec2> BodyGeometry::getActualPoints() {
		std::vector<glm::dvec2> actual_points;

		glm::dvec2 dir = pivot2->pos - pivot1->pos;
		double angle = atan2(dir.y, dir.x);
		//glm::dvec2 p1 = (bodies[i].pivot1->pos + bodies[i].pivot2->pos) * 0.5;
		glm::dvec2 p1 = pivot1->pos;

		glm::dmat3x2 mat;
		mat[0][0] = cos(angle);
		mat[1][0] = -sin(angle);
		mat[2][0] = p1.x;
		mat[0][1] = sin(angle);
		mat[1][1] = cos(angle);
		mat[2][1] = p1.y;

		for (int k = 0; k < points.size(); ++k) {
			glm::dvec2 actual_point = mat * glm::dvec3(points[k], 1);
			actual_points.push_back(actual_point);
		}

		return actual_points;
	}

	void BodyGeometry::draw(QPainter& painter) {
		painter.save();

		painter.setPen(QPen(QColor(0, 0, 0), 1));
		painter.setBrush(QBrush(QColor(0, 255, 0, 60)));
		std::vector<glm::dvec2> actual_points = getActualPoints();
		std::vector<QPointF> pts;
		for (int k = 0; k < actual_points.size(); ++k) {
			pts.push_back(QPointF(actual_points[k].x, 800 - actual_points[k].y));
		}
		painter.drawPolygon(pts.data(), pts.size());

		painter.restore();

	}

}