#include "Canvas.h"
#include <QPainter>
#include <iostream>
#include <QFileInfoList>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QDomDocument>
#include <QResizeEvent>
#include <QtWidgets/QApplication>

Canvas::Canvas(QWidget *parent) : QWidget(parent) {
	ctrlPressed = false;
	shiftPressed = false;

	animation_timer = NULL;
	simulation_speed = 0.01;
}

Canvas::~Canvas() {
}

void Canvas::open(const QString& filename) {
	kinematics.load(filename);

	// Since the direction of the speed might be inverted due to the dead zone,
	// we need to recover the original speed when a new object is loaded.
	simulation_speed = 0.01;

	update();
}

void Canvas::save(const QString& filename) {
	kinematics.save(filename); 
}

void Canvas::run() {
	if (animation_timer == NULL) {
		animation_timer = new QTimer(this);
		connect(animation_timer, SIGNAL(timeout()), this, SLOT(animation_update()));
		animation_timer->start(10);
	}
}

void Canvas::stop() {
	if (animation_timer != NULL) {
		animation_timer->stop();
		delete animation_timer;
		animation_timer = NULL;
	}
}

void Canvas::speedUp() {
	simulation_speed *= 2;
}

void Canvas::speedDown() {
	simulation_speed *= 0.5;
}

void Canvas::invertSpeed() {
	simulation_speed = -simulation_speed;
}

void Canvas::stepForward() {
	if (animation_timer == NULL) {
		try {
			kinematics.stepForward(simulation_speed);
		}
		catch (char* ex) {
			simulation_speed = -simulation_speed;
			std::cerr << "Animation is stopped by error:" << std::endl;
			std::cerr << ex << std::endl;
		}
		update();
	}
}

void Canvas::stepBackward() {
	if (animation_timer == NULL) {
		try {
			kinematics.stepForward(-simulation_speed);
		}
		catch (char* ex) {
			simulation_speed = -simulation_speed;
			std::cerr << "Animation is stopped by error:" << std::endl;
			std::cerr << ex << std::endl;
		}
		update();
	}
}

void Canvas::showAssemblies(bool flag) {
	kinematics.showAssemblies(flag);
	update();
}

void Canvas::showLinks(bool flag) {
	kinematics.showLinks(flag);
	update();
}

void Canvas::showBodies(bool flag) {
	kinematics.showBodies(flag);
	update();
}

void Canvas::animation_update() {
	try {
		kinematics.stepForward(simulation_speed);
	}
	catch (char* ex) {
		simulation_speed = -simulation_speed;
		//stop();
		std::cerr << "Animation is stopped by error:" << std::endl;
		std::cerr << ex << std::endl;
	}

	update();
}

void Canvas::paintEvent(QPaintEvent *e) {
	QPainter painter(this);

	kinematics.draw(painter);
}

void Canvas::mousePressEvent(QMouseEvent* e) {
	/*
	// hit test against gears
	for (int i = 0; i < kinematics.assemblies.size(); ++i) {
		for (int j = 0; j < kinematics.assemblies[i]->gears.size(); ++j) {
			double dist = glm::length(kinematics.assemblies[i]->gears[j].center - glm::dvec2(e->x(), e->y()));
			if (dist <= kinematics.assemblies[i]->gears[j].radius) {
				// select this gear
				selected_gear = &kinematics.assemblies[i]->gears[j];
				prev_mouse_pt = glm::vec2(e->x(), e->y());
				break;
			}
		}
	}
	*/
}

void Canvas::mouseMoveEvent(QMouseEvent* e) {
	/*
	if (selected_gear != NULL) {
		// move this gear
		selected_gear->center += glm::vec2(e->x(), e->y()) - prev_mouse_pt;
		prev_mouse_pt = glm::vec2(e->x(), e->y());
		update();
	}
	*/
}

void Canvas::mouseReleaseEvent(QMouseEvent* e) {
	//selected_gear = NULL;
}

void Canvas::mouseDoubleClickEvent(QMouseEvent* e) {
}

void Canvas::resizeEvent(QResizeEvent *e) {
}

void Canvas::keyPressEvent(QKeyEvent* e) {
	ctrlPressed = false;
	shiftPressed = false;

	if (e->modifiers() & Qt::ControlModifier) {
		ctrlPressed = true;
	}
	if (e->modifiers() & Qt::ShiftModifier) {
		shiftPressed = true;
	}

	switch (e->key()) {
	case Qt::Key_Escape:
		break;
	case Qt::Key_Space:
		break;
	case Qt::Key_Delete:
		break;
	}

	update();
}

void Canvas::keyReleaseEvent(QKeyEvent* e) {
	switch (e->key()) {
	case Qt::Key_Control:
		ctrlPressed = false;
		break;
	case Qt::Key_Shift:
		shiftPressed = false;
		break;
	default:
		break;
	}
}

