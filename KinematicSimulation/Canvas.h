#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QKeyEvent>
#include <glm/glm.hpp>
#include <boost/shared_ptr.hpp>
#include <Kinematics.h>
#include <QTimer>

class Canvas : public QWidget {
Q_OBJECT

public:
	bool ctrlPressed;
	bool shiftPressed;

	kinematics::Kinematics kinematics;
	QTimer* animation_timer;
	bool collision_check;
	QPoint prev_mouse_pt;
	QPoint origin;
	double scale;

public:
	Canvas(QWidget *parent = NULL);
    ~Canvas();

	void open(const QString& filename);
	void save(const QString& filename);
	void run();
	void stop();
	void speedUp();
	void speedDown();
	void invertSpeed();
	void stepForward();
	void stepBackward();
	void showAssemblies(bool flag);
	void showLinks(bool flag);
	void showBodies(bool flag);

public slots:
	void animation_update();

protected:
	void paintEvent(QPaintEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void mouseDoubleClickEvent(QMouseEvent* e);
	void wheelEvent(QWheelEvent* e);
	void resizeEvent(QResizeEvent *e);

public:
	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);
};

#endif // CANVAS_H
