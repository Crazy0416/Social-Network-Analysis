#ifndef COAUTHORSHIPGRAPHWIDGET_H
#define COAUTHORSHIPGRAPHWIDGET_H

#include <QtWidgets/QWidget>
#include <QGraphicsScene>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topology.hpp>
#include <boost/graph/graph_traits.hpp>


#include "ui_CoauthorshipGraphWidget.h"
#include "EdgeItem.h"
#include "GraphicsView.h"


using namespace boost;


enum vertex_position_t { vertex_position };
namespace boost {
	BOOST_INSTALL_PROPERTY(vertex, position);
}
typedef square_topology<>::point_type point;
// 노드의 인덱스로 엣지를 표현
struct simple_edge {
	int first, second;
};
typedef boost::property<vertex_index_t, int,
	boost::property<vertex_name_t, std::string,
	boost::property<vertex_position_t, point>>
	> VertexProperties;
// 그래프 데이터
typedef adjacency_list<
	listS,	//outEdgeList
	listS,	//VertexList
	undirectedS,
	//vertex properties
	VertexProperties,
	//edge properties
	boost::property<edge_weight_t, double>
> CGraph;

/*
*
*/
class CoauthorshipGraphWidget : public QWidget
{
	Q_OBJECT

public:
	CoauthorshipGraphWidget(QWidget *parent = 0);

	void print_graph(const CGraph& graph);
	void TopK(const CGraph& graph);
	void TopKfromA(const CGraph& graph, QString author);
	void print_shortestPath(int *arr, const CGraph & cgraph);
	void bfs(int start, int end, const CGraph& cgraph, int cgraph_cnt);

private:
	void initscene();

	Ui::CoauthorshipGraphWidgetClass ui;
	QGraphicsScene *scene;
	View *view;
};

#endif // COAUTHORSHIPGRAPHWIDGET_H
