#include "Gear.h"
#include "Link.h"
#include "Utils.h"

namespace kinematics {

	Gear::Gear(int id, const glm::dvec2& center, double radius, double speed, double phase) {
		this->id = id;
		this->type = TYPE_GEAR;
		this->center = center;
		this->radius = radius;
		this->speed = speed;
		this->phase = phase;
		this->pos = center + glm::dvec2(cos(phase), sin(phase)) * radius;
	}

	Gear::Gear(QDomElement& node) {
		id = node.attribute("id").toInt();
		type = TYPE_GEAR;
		center.x = node.attribute("x").toDouble();
		center.y = node.attribute("y").toDouble();
		radius = node.attribute("radius").toDouble();
		speed = node.attribute("speed").toDouble();
		phase = node.attribute("phase").toDouble();
		pos = center + glm::dvec2(cos(phase), sin(phase)) * radius;
	}

	void Gear::init(const QMap<int, boost::shared_ptr<Joint>>& joints) {
	}

	void Gear::draw(QPainter& painter) {
		painter.save();
		painter.setPen(QPen(QColor(0, 0, 0), 1));
		painter.setBrush(QBrush(QColor(255, 255, 255)));
		painter.drawEllipse(QPoint(pos.x, 800 - pos.y), 5, 5);
		painter.restore();
	}

	void Gear::stepForward(double step_size) {
		phase += speed * step_size;
	}

	/**
	* Update the position of this joint.
	* Return true if the position is updated.
	* Return false if one of the positions of the parent nodes has not been updated yet.
	*/
	bool Gear::forwardKinematics(const QMap<int, boost::shared_ptr<Joint>>& joints, const QMap<int, bool>& updated) {
		pos = center + glm::dvec2(cos(phase), sin(phase)) * radius;
		return true;
	}

}