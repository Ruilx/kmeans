#include "Dialog.h"

Dialog::Dialog(QWidget *parent)
	: QDialog(parent)
{
	this->canvas = new Canvas(this);
	this->step = 0;

	QGridLayout *mainLay = new QGridLayout;
	this->setLayout(mainLay);
	mainLay->addWidget(canvas, 0, 0, 1, 2);

	this->kEdit = new QLineEdit("5", this);
	this->RandomEdit = new QLineEdit("100", this);

	mainLay->addWidget(new QLabel("K = ", this), 1, 0, 1, 1, Qt::AlignRight);
	mainLay->addWidget(new QLabel("Random:", this), 2, 0, 1, 1, Qt::AlignRight);
	mainLay->addWidget(this->kEdit, 1, 1, 1, 1);
	mainLay->addWidget(this->RandomEdit, 2, 1, 1, 1);

	this->tickButton = new QPushButton("Tick", this);
	mainLay->addWidget(this->tickButton, 3, 1, 1 ,1);

	connect(this->tickButton, SIGNAL(clicked(bool)), this, SLOT(tickButtonClickSlot()));
	connect(this->canvas, SIGNAL(stop()), this, SLOT(gameover()));

//	this->canvas->createRandomPoint(100);
//	this->canvas->createRandomK(3);
//	this->canvas->calNearKPoint();
//	this->canvas->calNewKPoint();
}

Dialog::~Dialog()
{

}

void Dialog::tickButtonClickSlot(){
	this->tickButton->setEnabled(false);
	if(this->kEdit->isEnabled() || this->RandomEdit->isEnabled()){
		//if not started
		this->kEdit->setEnabled(false);
		this->RandomEdit->setEnabled(false);
		bool ok = false;
		this->canvas->createRandomPoint(this->RandomEdit->text().toInt(&ok));
		if(!ok){
			qDebug() << "Error while createRandomPoint: RandomEdit's text is NaN.";
			this->kEdit->setEnabled(true);
			this->RandomEdit->setEnabled(true);
			return;
		}
		ok = false;
		this->canvas->createRandomK(this->kEdit->text().toInt(&ok));
		if(!ok){
			qDebug() << "Error while createRandomK: KEdit's text is NaN.";
			this->kEdit->setEnabled(true);
			this->RandomEdit->setEnabled(true);
			return;
		}
		this->step = 0;
		this->canvas->calNearKPoint();
	}else{
		//if Started
		this->canvas->calNewKPoint();
		this->canvas->calNearKPoint();
		this->step++;
	}
	this->tickButton->setEnabled(true);
}

void Dialog::gameover(){
	QMessageBox::information(this, "Game Over", "K-value is keeping, steps:" + QString::number(this->step) +", game over.", QMessageBox::Ok);
	this->kEdit->setEnabled(true);
	this->RandomEdit->setEnabled(true);
}
