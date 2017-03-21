#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <QMap>
#include <QPainter>
#include <iostream>

namespace kinematics {

	class Link;

	class Joint {
	public:
		static enum { TYPE_PIN = 0, TYPE_SLIDER, TYPE_SLIDER_HINGE, TYPE_GEAR };
	public:
		int id;
		int type;
		glm::dvec2 pos;
		std::vector<boost::shared_ptr<Link>> out_links;
		std::vector<boost::shared_ptr<Link>> in_links;

	public:
		virtual void init(const QMap<int, boost::shared_ptr<Joint>>& joints) = 0;
		virtual void draw(QPainter& painter) = 0;
		virtual void stepForward(double step_size) = 0;
		virtual bool forwardKinematics(const QMap<int, boost::shared_ptr<Joint>>& joints, const QMap<int, bool>& updated) = 0;
	};

}