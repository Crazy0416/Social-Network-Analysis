#pragma once
#include <QColor>
#include <qgraphicsitem.h>
#include <qdebug.h>


class EdgeItem
	: public QGraphicsLineItem
{
private:
	double x1, y1, x2, y2;
	int width;
	QColor color;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public:
	EdgeItem(double x1, double y1, double x2, double y2, QColor color, int width);

	void setColor(QColor color);
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};