#pragma once

#include <QGraphicsItem>
#include <QColor>

const int NODE_SIZE = 4;

class NodeItem
	: public QGraphicsItem
{
private:
	int x;
	int y;
	QColor color;
	QString label;

	int weightSum;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public:
	NodeItem(double x, double y, QColor color, QString label);
	NodeItem(double x, double y, QColor color, QString label, int weightSum);

	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void setColor(QColor color);
	int getWeightSum();
	QString getLabel();

	bool operator>(const NodeItem& ni) const { return weightSum > ni.weightSum; }
	bool operator<(const NodeItem& ni) const { return weightSum < ni.weightSum; }
};
