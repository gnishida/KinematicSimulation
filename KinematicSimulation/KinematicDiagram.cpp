#include "KinematicDiagram.h"

namespace kinematics {

	KinematicDiagram::KinematicDiagram() {
	}


	KinematicDiagram::~KinematicDiagram() {
	}

	void KinematicDiagram::clear() {
		joints.clear(); 
		links.clear();
	}

	void KinematicDiagram::saveState() {
		for (auto it = joints.begin(); it != joints.end(); ++it) {
			joints[it.key()]->saveState();
		}
	}

	void KinematicDiagram::restoreState() {
		for (auto it = joints.begin(); it != joints.end(); ++it) {
			joints[it.key()]->restoreState();
		}
	}

	void KinematicDiagram::addJoint(boost::shared_ptr<Joint> joint) {
		int id = joint->id;

		// if id == -1, automatically set the appropriate id
		if (id == -1) {
			id = 0;
			if (!joints.empty()) {
				id = joints.lastKey() + 1;
			}
			joint->id = id;
		}

		joints[id] = joint;
	}

	boost::shared_ptr<Link> KinematicDiagram::newLink(bool driver) {
		int id = 0;
		if (!links.empty()) {
			id = links.lastKey() + 1;
		}

		boost::shared_ptr<Link> link = boost::shared_ptr<Link>(new Link(id, driver));
		links[id] = link;
		return link;
	}

	boost::shared_ptr<Link> KinematicDiagram::addLink(bool driver, boost::shared_ptr<Joint> joint1, boost::shared_ptr<Joint> joint2) {
		int id = 0;
		if (!links.empty()) {
			id = links.lastKey() + 1;
		}

		boost::shared_ptr<Link> link = boost::shared_ptr<Link>(new Link(id, driver));
		links[id] = link;

		link->addJoint(joint1);
		link->addJoint(joint2);
		joint1->links.push_back(link);
		joint2->links.push_back(link);

		return link;
	}

	boost::shared_ptr<Link> KinematicDiagram::addLink(bool driver, std::vector<boost::shared_ptr<Joint>> joints) {
		int id = 0;
		if (!links.empty()) {
			id = links.lastKey() + 1;
		}

		boost::shared_ptr<Link> link = boost::shared_ptr<Link>(new Link(id, driver));
		links[id] = link;

		for (int i = 0; i < joints.size(); ++i) {
			link->addJoint(joints[i]);
			joints[i]->links.push_back(link);
		}

		return link;
	}

}