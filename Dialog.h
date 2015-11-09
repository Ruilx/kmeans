#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "canvas.h"

class Dialog : public QDialog
{
	Q_OBJECT
	Canvas *canvas;

	QLineEdit *kEdit;
	QLineEdit *RandomEdit;

	QPushButton *tickButton;
	int step;
public:
	Dialog(QWidget *parent = 0);
	~Dialog();
private slots:
	void tickButtonClickSlot();
	void gameover();
};

#endif // DIALOG_H
