#ifndef EDGEITEM_H
#pragma once

#include <QColor>
#include <QGraphicsItem>


class EdgeItem
	: public QGraphicsItem
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

	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // EDGEITEM_H