#include "subwindow.h"
#include "GraphicsView.h"

#include <QTimer>

subwindow::subwindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initscene();

	View* view = new View("temp view");
	view->view()->setScene(scene);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(view);
	setLayout(layout);

	setWindowTitle(tr("sub window"));
}

subwindow::~subwindow()
{

}
//=====================================================================================================
void subwindow::setGraph(CoauthorGraphItem* pCGI)
{
	QGraphicsItem* graph_item = pCGI;
	graph_item->setPos(0, 0);
	scene->addItem(graph_item);
}
//=====================================================================================================
void subwindow::initscene()
{
	scene = new QGraphicsScene(this);
}