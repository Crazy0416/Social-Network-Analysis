#pragma once

#include <QGraphicsItem>
#include <QColor>
#include <vector>
#include <string>

const int NODE_SIZE = 4;

class NodeItem
	: public QGraphicsItem
{
private:
	int x;						// x좌표
	int y;						// y좌표
	QColor color;				// 색칠될 색상
	QString label;				// author 이름
	int weightSum;				// 노드에 연결된 엣지의 합
	std::vector<std::string> coauthorList;// 노드와 연결된 coauthor들의 이름

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public:
	NodeItem(double x, double y, QColor color, QString label);
	NodeItem(double x, double y, QColor color, QString label, int weightSum);
	NodeItem(double x, double y, QColor color, QString label, int weightSum, std::vector<std::string> coauthorList);

	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void setColor(QColor color);
	int getWeightSum();
	QString getLabel();
	void setcoauthorList(std::vector<std::string> data) { coauthorList.swap(data); }
	void coauthorPush_back(std::string coauthor) { coauthorList.push_back(coauthor); }

	bool operator>(const NodeItem& ni) const { return weightSum > ni.weightSum; }
	bool operator<(const NodeItem& ni) const { return weightSum < ni.weightSum; }
};
