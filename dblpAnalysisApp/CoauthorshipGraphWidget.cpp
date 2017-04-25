#include "CoauthorshipGraphWidget.h"
#include "NodeItem.h"

#include <qdebug.h>
#include <string>
#include <Queue>
using namespace std;

#define K 5 // Top-K

void ReheapUp(int arr[], int root, int last)
{

	int parent = (last - 1) / 2;

	if (last > root)
	{
		if (arr[parent] > arr[last])
		{
			swap(arr[parent], arr[last]);
			ReheapUp(arr, root, parent);
		}
	}
}
void ReheapDown(int arr[], int root, int last)
{

	int minChild;
	int rightChild = root * 2 + 2;
	int leftChild = root * 2 + 1;

	if (leftChild <= last)
	{
		if (leftChild == last)
			minChild = leftChild;
		else
		{
			if (arr[leftChild] > arr[rightChild])
				minChild = rightChild;
			else
				minChild = leftChild;
		}

		if (arr[root] > arr[minChild])
		{
			swap(arr[root], arr[minChild]);
			ReheapDown(arr, minChild, last);
		}
	}
}

CoauthorshipGraphWidget::CoauthorshipGraphWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initscene();

	view = new View("temp view");
	view->view()->setScene(scene);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(view);
	setLayout(layout);

	setWindowTitle(tr("dblp coauthor graph visualization"));
}

void CoauthorshipGraphWidget::print_graph(const CGraph & graph)
{
	//print graph
	typedef square_topology<> Topology;
	typedef typename Topology::point_type Point;
	const int rect_sz = 4;
	auto position = get(vertex_position, graph);
	auto label = get(vertex_name, graph);



	//print edges
	typename graph_traits<CGraph>::edge_iterator ei, ei_end;
	typedef boost::graph_traits<CGraph>::vertex_descriptor VertexDescriptor;
	VertexDescriptor u, v;
	for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
		u = source(*ei, graph);
		v = target(*ei, graph);

		Point p1 = position[u];
		Point p2 = position[v];

		/*line = scene->addLine(
		p1[0], p1[1],
		p2[0], p2[1],
		QPen(Qt::black)
		);*/
		//QGraphicsItem *edge =
		//	new EdgeItem(p1[0], p1[1], p2[0], p2[1]);
		//edge->setPos(QPointF(p1[0], p1[1]));
		//scene->addItem(edge);

		//scene->addLine(p1[0], p1[1], p2[0], p2[1], QPen(Qt::black, 0));
		QGraphicsItem *edge;
		edge = new EdgeItem(p1[0], p1[1], p2[0], p2[1], QColor(Qt::black), 0);
		scene->addItem(edge);
	}

	//print nodes
	typename graph_traits<CGraph>::vertex_iterator vi, vi_end;
	for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
		//Point p = position[*vi];
		//rectangle = scene->addRect(
		//	p[0], p[1], rect_sz, rect_sz,
		//	QPen(Qt::black),
		//	QBrush(Qt::green));
		Point p = position[*vi];
		std::string name = label[*vi];
		QGraphicsItem *node = new NodeItem(p[0], p[1], QString(name.c_str()));
		node->setPos(QPointF(p[0], p[1]));
		scene->addItem(node);
	}
	view->show();
}

void CoauthorshipGraphWidget::TopK(const CGraph& graph)
{
	//print graph
	typedef square_topology<> Topology;
	typedef typename Topology::point_type Point;
	const int rect_sz = 4;
	auto index = get(vertex_index, graph);
	auto position = get(vertex_position, graph);
	auto label = get(vertex_name, graph);

	// vertex 정보(참여도) 초기화 부분
	vector<int> vInfo;
	typename graph_traits<CGraph>::vertex_iterator vi, vi_end;
	for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi)
		vInfo.push_back(0);

	// edges로부터 vertex 정보 set & print edges
	typename graph_traits<CGraph>::edge_iterator ei, ei_end;
	typedef boost::graph_traits<CGraph>::vertex_descriptor VertexDescriptor;
	VertexDescriptor u, v; int i;
	for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
		// 정보 set
		i = index[ei->m_source];
		vInfo[i]++;
		i = index[ei->m_target];
		vInfo[i]++;

		//
		u = source(*ei, graph);
		v = target(*ei, graph);

		Point p1 = position[u];
		Point p2 = position[v];

		/*line = scene->addLine(
		p1[0], p1[1],
		p2[0], p2[1],
		QPen(Qt::black)
		);*/
		//QGraphicsItem *edge =
		//	new EdgeItem(p1[0], p1[1], p2[0], p2[1]);
		//edge->setPos(QPointF(p1[0], p1[1]));
		//scene->addItem(edge);

		scene->addLine(p1[0], p1[1], p2[0], p2[1], QPen(Qt::black, 0));
	}

	int kCtn[K]; // Top-K vertex의 index를 남는 컨테이너
	for (int j = 0; j < vInfo.size(); j++) {
		if (j < K) // K개의 최소 힙 생성
		{
			kCtn[j] = j;
			ReheapUp(kCtn, 0, j);
		}
		else // 최소 힙 루트노드(최소값)과 데이터 비교
		{
			if (vInfo[j] > vInfo[kCtn[0]])
			{
				kCtn[0] = j;
				ReheapDown(kCtn, 0, K - 1);
			}
		}
	}

	// print nodes
	for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
		//Point p = position[*vi];
		//rectangle = scene->addRect(
		//	p[0], p[1], rect_sz, rect_sz,
		//	QPen(Qt::black),
		//	QBrush(Qt::green));

		i = index[*vi];
		Point p = position[*vi];
		std::string name = label[*vi];

		NodeItem *node = new NodeItem(p[0], p[1], QString(name.c_str()));

		for (int j = 0; j < K; j++) // Coloring : 알고리즘 개선 필요!
		{
			if (kCtn[j] == i)
			{
				node->setColor(QColor(Qt::red));
			}
		}
		node->setPos(QPointF(p[0], p[1]));
		scene->addItem(node);
	}
}
void CoauthorshipGraphWidget::TopKfromA(const CGraph& graph, QString author)
{
	string src = author.toUtf8().constData();
	qDebug() << "input : " << author;

	//print graph
	typedef square_topology<> Topology;
	typedef typename Topology::point_type Point;
	const int rect_sz = 4;
	auto index = get(vertex_index, graph);
	auto position = get(vertex_position, graph);
	auto label = get(vertex_name, graph);

	// vertex 정보(참여도) 초기화 부분
	vector<int> vInfo;
	typename graph_traits<CGraph>::vertex_iterator vi, vi_end;
	for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi)
		vInfo.push_back(0);

	vector<int> adjV; // 소스로부터 인접한 Vertex의 index를 담는 컨테이너
	// edges로부터 vertex 정보 set & print edges & adjV 컨테이너 담기
	typename graph_traits<CGraph>::edge_iterator ei, ei_end;
	typedef boost::graph_traits<CGraph>::vertex_descriptor VertexDescriptor;
	VertexDescriptor u, v; int i;
	for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
		// 정보 set
		i = index[ei->m_source];
		vInfo[i]++;
		if (label[ei->m_target] == src)
		{
			qDebug() << index[ei->m_target] << "---->" << i;
			adjV.push_back(i);
		}

		i = index[ei->m_target];
		vInfo[i]++;
		if (label[ei->m_source] == src)
		{
			qDebug() << index[ei->m_source] << "---->" << i;
			adjV.push_back(i);
		}

		//
		u = source(*ei, graph);
		v = target(*ei, graph);

		Point p1 = position[u];
		Point p2 = position[v];

		/*line = scene->addLine(
		p1[0], p1[1],
		p2[0], p2[1],
		QPen(Qt::black)
		);*/
		//QGraphicsItem *edge =
		//	new EdgeItem(p1[0], p1[1], p2[0], p2[1]);
		//edge->setPos(QPointF(p1[0], p1[1]));
		//scene->addItem(edge);

		scene->addLine(p1[0], p1[1], p2[0], p2[1], QPen(Qt::black, 0));
	}

	int kCtn[K]; // Top-K vertex의 index를 남는 컨테이너
	int size = K < adjV.size() ? K : adjV.size();

	for (int j = 0; j < adjV.size(); j++) {
		
		qDebug() << adjV[j] << "'s edge number : " << vInfo[adjV[j]];

		if (j < size) // 최소 힙 생성
		{
			kCtn[j] = adjV[j];
			ReheapUp(kCtn, 0, j);
		}
		else // 최소 힙 루트노드(최소값)과 데이터 비교
		{
			if (vInfo[adjV[j]] > vInfo[kCtn[0]])
			{
				kCtn[0] = adjV[j];
				ReheapDown(kCtn, 0, K - 1);
			}
		}
	}

	// print nodes
	for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
		//Point p = position[*vi];
		//rectangle = scene->addRect(
		//	p[0], p[1], rect_sz, rect_sz,
		//	QPen(Qt::black),
		//	QBrush(Qt::green));

		i = index[*vi];
		Point p = position[*vi];
		std::string name = label[*vi];

		NodeItem *node = new NodeItem(p[0], p[1], QString(name.c_str()));

		if (label[*vi] == src)
			node->setColor(QColor(Qt::blue));
		else
		{
			node->setColor(QColor::fromRgb(200, 255, 200, 255));

			for (int j = 0; j < size; j++) // Coloring : 알고리즘 개선 필요!
			{
				if (kCtn[j] == i)
				{
					qDebug() << i << "was colored.";
					node->setColor(QColor(Qt::red));
				}
			}
		}

		node->setPos(QPointF(p[0], p[1]));
		scene->addItem(node);
	}
}
void CoauthorshipGraphWidget::bfs(int start, int end, const CGraph &cgraph, int cgraph_cnt)
{
	queue<int> q;
	queue<queue<int>> all_path;
	bool* visited = new bool[cgraph_cnt];
	int **link = new int*[cgraph_cnt];
	for (int i = 0; i < cgraph_cnt; i++)
	{
		link[i] = new int[cgraph_cnt];
		for (int j = 0; j < cgraph_cnt; j++)
			link[i][j] = 0;
	}
	for (int cnt = 0; cnt < cgraph_cnt; cnt++)
		visited[cnt] = false;
	CGraph test = cgraph;
	typedef property_map<CGraph, vertex_index_t>::type vertex_index_map;
	vertex_index_map v_indexMap = get(vertex_index, test);
	graph_traits<CGraph>::edge_iterator ei, ee;

	for (tie(ei, ee) = edges(cgraph); ei != ee; ++ei) {
		graph_traits<CGraph>::edge_descriptor e = *ei;
		//auto a = get(edge_index, *ei,cgraph)
		graph_traits<CGraph>::vertex_descriptor u = source(e, cgraph), v = target(e, cgraph);
		link[v_indexMap[u]][v_indexMap[v]] = 1;		// link[출발지][목적지] = 1;
		link[v_indexMap[v]][v_indexMap[u]] = 1;		// link[목적지][출발지] = 1;  because undirect graph
	}

	q.push(start);
	queue<int> tmp;
	tmp.push(start);
	all_path.push(tmp);
	visited[start] = true;

	int f, i;

	while (!q.empty())
	{
		f = q.front();
		q.pop();

		//qDebug() << f;

		for (i = 0; i < cgraph_cnt; i++)
		{
			if (visited[i] == 0 && link[f][i] == 1)
			{
				queue<int> tmp = all_path.front();
				tmp.push(i);
				q.push(i);
				visited[i] = 1;
				all_path.push(tmp);
				if (i == end)				// 목표지점에 도착했다면
				{
					int *arr = new int[tmp.size()];		// 최단거리 index 배열
					int i = 0;
					while (!tmp.empty())
					{
						qDebug() << tmp.front();
						arr[i] = tmp.front();
						tmp.pop();
						i++;
					}
					print_shortestPath(arr, cgraph);				// 최단거리 path 그리기
					return;
				}
			}
		}
		all_path.pop();
	}
}

void CoauthorshipGraphWidget::print_shortestPath(int *arr, const CGraph & cgraph)
{
	typedef property_map<CGraph, vertex_index_t>::type vertex_index_map;
	typedef square_topology<> Topology;
	typedef typename Topology::point_type Point;
	auto position = get(vertex_position, cgraph);
	auto verIndex = get(vertex_index, cgraph);

	int arr_cnt = 0;
	bool exist_path = false;

	//print edges
	typename graph_traits<CGraph>::edge_iterator ei, ei_end;
	typedef boost::graph_traits<CGraph>::vertex_descriptor VertexDescriptor;
	VertexDescriptor u, v;
	CGraph tmp_graph = cgraph;
	vertex_index_map v_indexMap = get(boost::vertex_index, tmp_graph);
	int Repetition = 0;								// iterator가 증가하면서 같이 증가;
here:
	for (boost::tie(ei, ei_end) = edges(cgraph); ei != ei_end; ++ei) {

		u = source(*ei, cgraph);
		v = target(*ei, cgraph);
		Repetition++;
		qDebug() << v_indexMap[u] << "--->" << v_indexMap[v];
		if (v_indexMap[u] == arr[arr_cnt] && v_indexMap[v] == arr[arr_cnt + 1] || v_indexMap[v] == arr[arr_cnt] && v_indexMap[u] == arr[arr_cnt + 1])
		{
			qDebug() << "printed edge";
			qDebug() << arr[arr_cnt] << "---->" << arr[arr_cnt + 1];

			Point p1 = position[u];
			Point p2 = position[v];

			scene->addLine(p1[0], p1[1], p2[0], p2[1], QPen(Qt::blue, 2));
			arr_cnt++;
			Repetition = 0;
			exist_path = true;		// 길이 하나라도 있다면 true;
			goto here;
		}
	}
	if (!exist_path)
		qDebug() << "There's no way to find it.";

}
void CoauthorshipGraphWidget::initscene()
{
	scene = new QGraphicsScene(this);

	//int x = 0, y;
	//for (int i=-11000; i<11000; i+=110) {
	//	++x;
	//	y = 0;
	//	for (int j=-7000; j<7000; j+=70) {
	//		++y;
	//		QGraphicsItem *item = new NodeItem(x, y);
	//		item->setPos(QPointF(i, j));
	//		scene->addItem(item);
	//	}
	//}
}
