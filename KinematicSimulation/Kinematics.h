#pragma once

#include <QPainter>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/shared_ptr.hpp>
#include <QMap>
#include "Joint.h"
#include "Link.h"

namespace kinematics {
	
	class Body {
	public:
		int pivot1;
		int pivot2;
		std::vector<glm::dvec2> points;

	public:
		Body(int pivot1, int pivot2) : pivot1(pivot1), pivot2(pivot2) {}
	};

	class Kinematics {
	public:
		QMap<int, boost::shared_ptr<Joint>> joints;
		std::vector<boost::shared_ptr<Link>> links;
		std::vector<Body> bodies;
		std::vector<std::vector<glm::vec2>> trace_end_effector;

		bool show_assemblies;
		bool show_links;
		bool show_bodies;

	public:
		Kinematics();

		void load(const QString& filename);
		void save(const QString& filename);
		void forwardKinematics();
		void stepForward(double time_step);
		void stepBackward();
		void draw(QPainter& painter);
		void showAssemblies(bool flag);
		void showLinks(bool flag);
		void showBodies(bool flag);
	};

}
