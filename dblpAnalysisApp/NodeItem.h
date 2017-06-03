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
	int x;						// x��ǥ
	int y;						// y��ǥ
	QColor color;				// ��ĥ�� ����
	QString label;				// author �̸�
	int weightSum;				// ��忡 ����� ������ ��
	std::vector<std::string> coauthorList;// ���� ����� coauthor���� �̸�

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
