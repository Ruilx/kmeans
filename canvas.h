#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QtWidgets>

class Canvas : public QWidget
{
	Q_OBJECT
	QList<QPoint> pointList;
	QList<int>	nearestKPoint; //length as pointList
	QList<QPoint> kList;
	QList<bool> kListSame; //length as kList
	QList<QColor> kListColor; //length as KList

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;

	void paintEvent(QPaintEvent *){
		QPainter painter(this);
		painter.fillRect(50, 50, 400, 400, Qt::SolidPattern);
		// Draw Normal Point
		//painter.setBrush(Qt::white);
		painter.setPen(Qt::white);
		for(int i=0; i<this->pointList.length(); i++){
			//painter.drawPoint(this->pointList.at(i));
			if(this->nearestKPoint.at(i) != -1){
				painter.setBrush(QBrush(this->kListColor.at(this->nearestKPoint.at(i))));
			}
			painter.drawEllipse(this->pointList.at(i), 2, 2);
		}
		// Draw K Point
		painter.setBrush(Qt::black);
		for(int i=0; i<this->kList.length(); i++){
			painter.setPen(QPen(this->kListColor.at(i)));
			//painter.setBrush(QBrush(this->kListColor.at(i)));
			painter.drawEllipse(this->kList.at(i), 2, 2);
		}
		// Draw Line
		for(int i=0; i<this->pointList.length(); i++){
			if(this->nearestKPoint.at(i) != -1){
				painter.setPen(QPen(this->kListColor.at(this->nearestKPoint.at(i))));
				painter.drawLine(this->pointList.at(i), this->kList.at(this->nearestKPoint.at(i)));
			}
		}
	}

public:
	void createRandomPoint(int quantity){
		this->pointList.clear();
		srand((unsigned)QTime::currentTime().msecsSinceStartOfDay());
		for(int i=0; i<quantity; i++){
			this->pointList.append(QPoint(rand() % 400 + 50, rand() % 400 + 50));
			this->nearestKPoint.append(-1);
		}
		this->update();
	}

	void createRandomK(int k){
		this->kList.clear();
		if(k > this->pointList.length()){
			k = this->pointList.length();
		}
		srand((unsigned)QTime::currentTime().msecsSinceStartOfDay());
		for(int i=0; i<k; i++){
			int randomNumber = rand() % this->pointList.length();
			this->kList.append(this->pointList.at(randomNumber));
			//this->pointList.takeAt(randomNumber);
			this->kListSame.append(false);
			this->kListColor.append(this->getAColor());
		}
		this->update();
	}

	void calNearKPoint(){
		for(int i=0; i<this->pointList.length(); i++){
			int index = -1;
			qreal distance = 1000.0;
			for(int j = 0; j<this->kList.length(); j++){
				qreal currentDis = distanceF(pointList.at(i), kList.at(j));
				if(currentDis < distance){
					distance = currentDis;
					index = j;
				}
			}
			this->nearestKPoint[i] = index;
		}
		this->update();
	}

	void calNewKPoint(){
		QList<QSize> kSumList;
		QList<int> kSumTimes;
		for(int i=0; i<this->kList.length(); i++){
			kSumList.append(QSize(0, 0));
			kSumTimes.append(0);
		}
		for(int i=0; i<this->pointList.length(); i++){
			int currentKIndex = this->nearestKPoint.at(i);
			kSumList[currentKIndex].setWidth(kSumList[currentKIndex].width() + this->pointList.at(i).x());
			kSumList[currentKIndex].setHeight(kSumList[currentKIndex].height() + this->pointList.at(i).y());
			kSumTimes[currentKIndex]++;
		}
		for(int i=0; i<this->kList.length(); i++){
			if(this->kListSame.at(i) == true){
				continue;
			}
			QPoint currentKPoint = this->kList.at(i);
			QPoint newKPoint = QPoint(qFloor(kSumList.at(i).width() / kSumTimes.at(i)), qFloor(kSumList.at(i).height() / kSumTimes.at(i)));
			if(qAbs(currentKPoint.x() - newKPoint.x()) < 2 && qAbs(currentKPoint.y() - newKPoint.y()) < 2){
				// K is Same
				this->kListSame[i] = true;
				if(isAllKValuesIsTrue()){
					emit this->stop();
				}
			}
			this->kList[i] = newKPoint;
		}
		this->update();
	}

	qreal distanceF(QPoint p1, QPoint p2){
		int xDis = qAbs(p1.x()-p2.x());
		int yDis = qAbs(p1.y()-p2.y());
		return qSqrt((qreal)xDis * (qreal)xDis + (qreal)yDis * (qreal)yDis);
	}

	bool isAllKValuesIsTrue(){
		for(int i=0; i<this->kListSame.length(); i++){
			if(this->kListSame.at(i) == false){
				return false;
			}
		}
		return true;
	}

	QColor getAColor(){
		return QColor(distribution(generator), distribution(generator), distribution(generator));
	}

	QList<QPoint> getPointList(){
		return this->pointList;
	}

	QList<int> getNearestKPoint(){
		return this->nearestKPoint;
	}

	QList<QPoint> getKList(){
		return this->kList;
	}

	explicit Canvas(QWidget *parent = 0);

signals:
	void stop();
public slots:
};

#endif // CANVAS_H
