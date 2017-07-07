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

	origin = QPoint(0, height());
	scale = 1.0;
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

	// draw axes
	painter.save();
	painter.setPen(QPen(QColor(128, 128, 128), 1, Qt::DashLine));
	painter.drawLine(-10000 * scale + origin.x(), origin.y(), 10000 * scale + origin.y(), origin.y());
	painter.drawLine(origin.x(), 10000 * scale + origin.y(), origin.x(), -10000 * scale + origin.y());
	painter.restore();

	kinematics.draw(painter, origin, scale);
}

void Canvas::mousePressEvent(QMouseEvent* e) {
	prev_mouse_pt = e->pos();
}

void Canvas::mouseMoveEvent(QMouseEvent* e) {
	// move the camera
	if (e->buttons() & Qt::RightButton) {
		// translate the Origin
		origin += e->pos() - prev_mouse_pt;
		update();
	}

	prev_mouse_pt = e->pos();
}

void Canvas::mouseReleaseEvent(QMouseEvent* e) {
}

void Canvas::mouseDoubleClickEvent(QMouseEvent* e) {
}

void Canvas::wheelEvent(QWheelEvent* e) {
	scale += e->delta() * 0.001;
	scale = std::min(std::max(0.1, scale), 1000.0);
	update();
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

