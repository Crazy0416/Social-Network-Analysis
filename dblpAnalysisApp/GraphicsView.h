#pragma once

#include <QFrame>
#include <QGraphicsView>
#include <QGridLayout>

//pre-declare
class View;

class GraphicsView
	: public QGraphicsView
{
	Q_OBJECT
private:
	View* view;

protected:
#ifndef QT_NO_WHEELEVENT
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
#endif
	void scaleView(qreal scaleFactor);

public:
	GraphicsView(View *v) : QGraphicsView(), view(v) {};
};


class View
	: public QFrame
{
	Q_OBJECT
private:
	GraphicsView *graphicsView;

public:
	explicit View(const QString& name, QWidget *parent = 0);
	QGraphicsView *view() const;

	public slots:
	/*void zoomIn(int level = 1);
	void zoomOut(int level = 1);*/
	void setupMatrix();
};
