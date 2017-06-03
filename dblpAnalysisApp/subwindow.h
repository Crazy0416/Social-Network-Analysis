#pragma once

#include <QtWidgets/QWidget>
#include <QGraphicsScene>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topology.hpp>
#include <boost/graph/graph_traits.hpp>

#include "ui_subwindow.h"
#include "GraphItem.h"

using namespace boost;

class subwindow : public QWidget
{
	Q_OBJECT

public:
	subwindow(QWidget *parent = 0);
	~subwindow();

	void setGraph(CoauthorGraphItem* pCGI);
	void setGraph(PaperGraphItem* pPGI);

private:
	void initscene();

	Ui::subwindow ui;
	QGraphicsScene *scene;
};