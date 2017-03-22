/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionExit;
    QAction *actionSimulationStart;
    QAction *actionSimulationStop;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionStepForward;
    QAction *actionStepBackward;
    QAction *actionSpeedUp;
    QAction *actionSpeedDown;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSimulation;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(800, 800);
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSimulationStart = new QAction(MainWindowClass);
        actionSimulationStart->setObjectName(QStringLiteral("actionSimulationStart"));
        actionSimulationStop = new QAction(MainWindowClass);
        actionSimulationStop->setObjectName(QStringLiteral("actionSimulationStop"));
        actionNew = new QAction(MainWindowClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindowClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionStepForward = new QAction(MainWindowClass);
        actionStepForward->setObjectName(QStringLiteral("actionStepForward"));
        actionStepBackward = new QAction(MainWindowClass);
        actionStepBackward->setObjectName(QStringLiteral("actionStepBackward"));
        actionSpeedUp = new QAction(MainWindowClass);
        actionSpeedUp->setObjectName(QStringLiteral("actionSpeedUp"));
        actionSpeedDown = new QAction(MainWindowClass);
        actionSpeedDown->setObjectName(QStringLiteral("actionSpeedDown"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSimulation = new QMenu(menuBar);
        menuSimulation->setObjectName(QStringLiteral("menuSimulation"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSimulation->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuSimulation->addAction(actionSimulationStart);
        menuSimulation->addAction(actionSimulationStop);
        menuSimulation->addAction(actionSpeedUp);
        menuSimulation->addAction(actionSpeedDown);
        menuSimulation->addSeparator();
        menuSimulation->addAction(actionStepForward);
        menuSimulation->addAction(actionStepBackward);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Kinematic Simulation", 0));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", 0));
        actionSimulationStart->setText(QApplication::translate("MainWindowClass", "Start", 0));
        actionSimulationStop->setText(QApplication::translate("MainWindowClass", "Stop", 0));
        actionNew->setText(QApplication::translate("MainWindowClass", "New", 0));
        actionOpen->setText(QApplication::translate("MainWindowClass", "Open", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindowClass", "Save", 0));
        actionSave->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+S", 0));
        actionStepForward->setText(QApplication::translate("MainWindowClass", "Step Forward", 0));
        actionStepForward->setShortcut(QApplication::translate("MainWindowClass", "Right", 0));
        actionStepBackward->setText(QApplication::translate("MainWindowClass", "Step Backward", 0));
        actionStepBackward->setShortcut(QApplication::translate("MainWindowClass", "Left", 0));
        actionSpeedUp->setText(QApplication::translate("MainWindowClass", "Speed Up", 0));
        actionSpeedUp->setShortcut(QApplication::translate("MainWindowClass", "Up", 0));
        actionSpeedDown->setText(QApplication::translate("MainWindowClass", "Speed Down", 0));
        actionSpeedDown->setShortcut(QApplication::translate("MainWindowClass", "Down", 0));
        menuFile->setTitle(QApplication::translate("MainWindowClass", "File", 0));
        menuSimulation->setTitle(QApplication::translate("MainWindowClass", "Simulation", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
