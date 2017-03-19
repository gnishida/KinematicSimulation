#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <QMap>
#include <QPainter>

namespace kinematics {

	class Link;

	class Joint {
	public:
		int id;
		glm::dvec2 pos;
		std::vector<boost::shared_ptr<Link>> out_links;
		std::vector<boost::shared_ptr<Link>> in_links;

	public:
		virtual void init(const QMap<int, boost::shared_ptr<Joint>>& joints) = 0;
		virtual void draw(QPainter& painter) = 0;
		virtual bool forwardKinematics(const QMap<int, boost::shared_ptr<Joint>>& joints, const QMap<int, bool>& updated) = 0;
	};

}