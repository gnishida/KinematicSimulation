#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Canvas.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	Ui::MainWindowClass ui;
	Canvas canvas;

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);

public slots:
	void onOpen();
	void onSave();
	void onSimulationStart();
	void onSimulationStop();
	void onSpeedUp();
	void onSpeedDown();
	void onInvertSpeed();
	void onStepForward();
	void onStepBackward();
	void onCollisionCheck();
};

#endif // MAINWINDOW_H
