#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>
#include <QMap>

#include "Joint.h"
#include "Link.h"
#include "BodyGeometry.h"

namespace kinematics {

	class KinematicDiagram {
	public:
		QMap<int, boost::shared_ptr<Joint>> joints;
		QMap<int, boost::shared_ptr<Link>> links;
		std::vector<boost::shared_ptr<BodyGeometry>> bodies;

	public:
		KinematicDiagram();
		~KinematicDiagram();

		KinematicDiagram clone() const;
		void clear();
		void addJoint(boost::shared_ptr<Joint> joint);
		boost::shared_ptr<Link> newLink(bool driver);
		boost::shared_ptr<Link> addLink(bool driver, boost::shared_ptr<Joint> joint1, boost::shared_ptr<Joint> joint2);
		boost::shared_ptr<Link> addLink(bool driver, std::vector<boost::shared_ptr<Joint>> joints);
		void load(const QString& filename);
		void save(const QString& filename);
		void updateBodyAdjacency();
		bool isCollided() const;
		void draw(QPainter& painter, bool show_bodies, bool show_links) const;
	};

}