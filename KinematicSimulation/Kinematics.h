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
	glm::dvec2 circleCircleIntersection(const glm::dvec2& center1, double radius1, const glm::dvec2& center2, double radius);
	
	/*
	class Gear {
	public:
		glm::dvec2 center;
		double radius;
		double phase;
		double speed;

	public:
		Gear() {}
		Gear(const glm::dvec2& center, double radius, double phase, double speed) : center(center), radius(radius), phase(phase), speed(speed) {}

		glm::dvec2 getLinkEndPosition();
		void draw(QPainter& painter);
	};

	class MechanicalAssembly {
	public:
		double phase;
		std::vector<Gear> gears;
		std::pair<int, int> order;
		std::vector<double> link_lengths;
		boost::shared_ptr<Joint> end_effector;

	public:
		MechanicalAssembly() : phase(3.14) {}

		glm::dvec2 getIntermediateJointPosition();
		glm::dvec2 getEndEffectorPosition();
		void forward(double time_step);
		void draw(QPainter& painter);
	};
	*/

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
		//std::vector<boost::shared_ptr<MechanicalAssembly>> assemblies;
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
		void stepForward();
		void stepBackward();
		void draw(QPainter& painter);
		void showAssemblies(bool flag);
		void showLinks(bool flag);
		void showBodies(bool flag);
	};

}
