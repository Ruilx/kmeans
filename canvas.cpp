#include "canvas.h"
#include <random>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
	this->setFixedSize(500, 500);
	this->setAutoFillBackground(true);

	QPalette pal;{
		pal.setColor(QPalette::Background, Qt::black);
	}
	this->setPalette(pal);

	this->generator = std::default_random_engine();
	this->distribution = std::uniform_int_distribution<int>(0, 255);
}

