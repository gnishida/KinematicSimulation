#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>
#include <QMap>

#include "Joint.h"
#include "Link.h"

namespace kinematics {

	class KinematicDiagram {
	public:
		QMap<int, boost::shared_ptr<Joint>> joints;
		QMap<int, boost::shared_ptr<Link>> links;

	public:
		KinematicDiagram();
		~KinematicDiagram();

		void clear();
		void saveState();
		void restoreState();
		void addJoint(boost::shared_ptr<Joint> joint);
		boost::shared_ptr<Link> newLink(bool driver);
		boost::shared_ptr<Link> addLink(bool driver, boost::shared_ptr<Joint> joint1, boost::shared_ptr<Joint> joint2);
		boost::shared_ptr<Link> addLink(bool driver, std::vector<boost::shared_ptr<Joint>> joints);
	};

}