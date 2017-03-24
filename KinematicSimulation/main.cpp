#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <vector>
#include "Utils.h"

int main(int argc, char *argv[])
{
	std::vector<glm::dvec2> pol1;
	std::vector<glm::dvec2> pol2;
	pol1.push_back(glm::dvec2(0, 0));
	pol1.push_back(glm::dvec2(10, 0));
	pol1.push_back(glm::dvec2(10, 4));
	pol1.push_back(glm::dvec2(5, 4));
	pol1.push_back(glm::dvec2(5, 6));
	pol1.push_back(glm::dvec2(10, 6));
	pol1.push_back(glm::dvec2(10, 10));
	pol1.push_back(glm::dvec2(0, 10));

	/*
	pol2.push_back(glm::dvec2(8, 2));
	pol2.push_back(glm::dvec2(12, 2));
	pol2.push_back(glm::dvec2(12, 8));
	pol2.push_back(glm::dvec2(8, 8));
	*/
	pol2.push_back(glm::dvec2(20, 0));
	pol2.push_back(glm::dvec2(30, 0));
	pol2.push_back(glm::dvec2(30, 20));
	pol2.push_back(glm::dvec2(0, 20));

	bool isCollided = kinematics::polygonPolygonIntersection(pol1, pol2);

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
