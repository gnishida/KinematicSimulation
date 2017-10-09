#include "MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	
	setCentralWidget(&canvas);

	ui.actionCollisionCheck->setChecked(canvas.collision_check);

	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(onOpen()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(onSave()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionSimulationStart, SIGNAL(triggered()), this, SLOT(onSimulationStart()));
	connect(ui.actionSimulationStop, SIGNAL(triggered()), this, SLOT(onSimulationStop()));
	connect(ui.actionSpeedUp, SIGNAL(triggered()), this, SLOT(onSpeedUp()));
	connect(ui.actionSpeedDown, SIGNAL(triggered()), this, SLOT(onSpeedDown()));
	connect(ui.actionInvertSpeed, SIGNAL(triggered()), this, SLOT(onInvertSpeed()));
	connect(ui.actionStepForward, SIGNAL(triggered()), this, SLOT(onStepForward()));
	connect(ui.actionStepBackward, SIGNAL(triggered()), this, SLOT(onStepBackward()));
	connect(ui.actionCollisionCheck, SIGNAL(triggered()), this, SLOT(onCollisionCheck()));
}

MainWindow::~MainWindow() {
}

void MainWindow::onOpen() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Design file..."), "", tr("Design Files (*.xml)"));
	if (filename.isEmpty()) return;

	this->setWindowTitle("Kinematic Simulation - " + filename);

	try {
		canvas.open(filename);
	}
	catch (char* ex) {
		QMessageBox::warning(this, "Error message", ex);
	}
}

void MainWindow::onSave() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Design file..."), "", tr("Design Files (*.xml)"));
	if (filename.isEmpty()) return;

	canvas.save(filename);
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
	canvas.keyPressEvent(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent* e) {
	canvas.keyReleaseEvent(e);
}

void MainWindow::onSimulationStart() {
	canvas.run();
}

void MainWindow::onSimulationStop() {
	canvas.stop();
}

void MainWindow::onSpeedUp() {
	canvas.speedUp();
}

void MainWindow::onSpeedDown() {
	canvas.speedDown();
}

void MainWindow::onInvertSpeed() {
	canvas.invertSpeed();
}

void MainWindow::onStepForward() {
	canvas.stepForward();
}

void MainWindow::onStepBackward() {
	canvas.stepBackward();
}

void MainWindow::onCollisionCheck() {
	canvas.collision_check = ui.actionCollisionCheck->isChecked();
}