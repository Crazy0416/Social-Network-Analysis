#include "dblpanalysisapp.h"
#include <qstatusbar.h>
#include <qaction.h>
#include "qmainwindow.h"

dblpAnalysisApp::dblpAnalysisApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	scene = new QGraphicsScene(this);
	cgraph_cnt = 0;

	// ��� ȭ�� ����
	ui.setupUi(this);
	QPixmap bkgnd("bkgnd.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);

	// â ũ�� ����
	this->setFixedSize(600, 400);

	{
	// �޴� �� ����
	QMenu *pAppMenu;
	QStatusBar *pStatusBar;

	
		// �⺻ ��� ���� �޴� ����
		QAction *pSlotVisualize = new QAction(tr("Visualization"), this);
		QObject::connect(pSlotVisualize, SIGNAL(triggered()), this, SLOT(Main_SlotVisualize()));

		QAction *pSlotTopK = new QAction(tr("Top-k Coloring"), this);
		QObject::connect(pSlotTopK, SIGNAL(triggered()), this, SLOT(Main_TopK()));

		QAction *pSlotTopKfromA = new QAction(tr("Top-K from A Coloring"), this);
		QObject::connect(pSlotTopKfromA, SIGNAL(triggered()), this, SLOT(Main_TopKfromA()));

		QAction *pSlotChain = new QAction(tr("Chain from A to B"), this);
		QObject::connect(pSlotChain, SIGNAL(triggered()), this, SLOT(Main_Chain()));

		QAction *pSlotAuthorCrawling = new QAction(tr("Author Crawling"), this);
		QObject::connect(pSlotAuthorCrawling, SIGNAL(triggered()), this, SLOT(Main_AuthorCrawling()));

		pAppMenu = menuBar()->addMenu(tr("Basic Menu"));
		pAppMenu->addAction(pSlotVisualize);
		pAppMenu->addAction(pSlotTopK);
		pAppMenu->addAction(pSlotTopKfromA);
		pAppMenu->addAction(pSlotChain);
		pAppMenu->addAction(pSlotAuthorCrawling);

		// �߰� ��� ���� �޴� ����
	/* �̱��� */


		pAppMenu = menuBar()->addMenu(tr("Additional Menu"));
		// ���� �� ����
		pStatusBar = statusBar();
	}
	// Co-authorgraph ���� �б�
	load_COAU_FILE();
}

dblpAnalysisApp::~dblpAnalysisApp()
{

}

//=====================================================================================================

void dblpAnalysisApp::Main_SlotVisualize() // Co-authorship graph �ð�ȭ
{
	pCGW = new CoauthorshipGraphWidget;
	pCGW->print_graph(cgraph);
	pCGW->show();
}
void dblpAnalysisApp::Main_TopK() // Top-K ��� Coloring
{
	pCGW = new CoauthorshipGraphWidget;
	pCGW->TopK(cgraph);
	pCGW->show();
}
void dblpAnalysisApp::Main_TopKfromA() // Ư�� ���κ��� ������ Top-K ��� Coloring
{
	pCGW = new CoauthorshipGraphWidget;
	pCGW->print_graph(cgraph);
	pCGW->show();

	bool ok;

	QString author = QInputDialog::getText(NULL, "Input Author", "Input Author", QLineEdit::Normal, "", &ok);

	int author_index = -1;

	if (ok && !author.isEmpty())
	{
		qDebug() << author;
	}
	graph_traits<CGraph>::vertex_iterator vi, ve;
	auto Cgraph_vertex_name = get(vertex_name, cgraph);
	auto Cgraph_vertex_index = get(vertex_index, cgraph);
	for (tie(vi, ve) = vertices(cgraph); vi != ve; ++vi) {
		//qDebug() << Cgraph_vertex_name[*vi].c_str();
		//qDebug() << Cgraph_vertex_index[*vi];
		if (author.toStdString() == Cgraph_vertex_name[*vi])
			author_index = Cgraph_vertex_index[*vi];
	}
	if (author_index == -1)			// ã�� �̸��� �׷����� ���ٸ�
	{
		// ����
		qDebug() << "No one is looking for it";
		return;
	}
	pCGW->TopKfromA(cgraph, author);
}
void dblpAnalysisApp::Main_Chain() // Ư�� ���κ��� �ٸ� �� ���� ���� Shortest Path
{
	pCGW = new CoauthorshipGraphWidget;
	pCGW->print_graph(cgraph);
	pCGW->show();

	bool ok1;
	bool ok2;

	// ã�� ���� ��� �Է� ����
	QString author1 = QInputDialog::getText(NULL, "Input start Author", "Input start Author", QLineEdit::Normal, "", &ok1);
	QString author2 = QInputDialog::getText(NULL, "Input end Author", "Input end Author", QLineEdit::Normal, "", &ok2);

	int author1_index = -1;		// ã�� ��� �ε���
	int author2_index = -1;

	if (ok1 && !author1.isEmpty())
	{
		qDebug() << author1;
	}
	if (ok2 && !author2.isEmpty())
	{
		qDebug() << author2;
	}

	//typedef property_map<CGraph, vertex_name_t>::type vertex_name_map;
	//typedef property_map<CGraph, vertex_index_t>::type vertex_index_map;
	graph_traits<CGraph>::vertex_iterator vi, ve;
	auto Cgraph_vertex_name = get(vertex_name, cgraph);
	auto Cgraph_vertex_index = get(vertex_index, cgraph);
	for (tie(vi, ve) = vertices(cgraph); vi != ve; ++vi) {
		//qDebug() << Cgraph_vertex_name[*vi].c_str();
		//qDebug() << Cgraph_vertex_index[*vi];
		if (author1.toStdString() == Cgraph_vertex_name[*vi])
			author1_index = Cgraph_vertex_index[*vi];
		if (author2.toStdString() == Cgraph_vertex_name[*vi])
			author2_index = Cgraph_vertex_index[*vi];
	}
	if (author1_index == -1 || author2_index == -1)			// ã�� �̸��� �׷����� ���ٸ�
	{
		// ����
		qDebug() << "No one is looking for it";
		return;
	}
	pCGW->bfs(author1_index, author2_index, cgraph, cgraph_cnt);
}

void dblpAnalysisApp::Main_AuthorCrawling()
{
	// ����Ʈ ������ ���� â ����
	ListInput* list = new ListInput();

	// ����Ʈ â�� author ������ ����
	graph_traits<CGraph>::vertex_iterator vi, ve;
	auto Cgraph_vertex_name = get(vertex_name, cgraph);
	int cnt = 1;
	for (tie(vi, ve) = vertices(cgraph); vi != ve; ++vi) {
		//qDebug() << Cgraph_vertex_name[*vi].c_str();
		//qDebug() << Cgraph_vertex_index[*vi];
		QString tmp = QString::number(cnt);
		tmp.append(".");
		tmp.append(Cgraph_vertex_name[*vi].c_str());
		list->addItem(tmp);
		cnt++;
	}
	
	list->show();
}

//=====================================================================================================

CGraph dblpAnalysisApp::read_cgraph(ifstream& in)
{
	/**
	*	Parse Coauthor dataset
	*	- author1, author2 publish_year
	*	Column Delimiter:		||
	*/
	std::string line;
	vector<std::string> tokens;
	//vector<std::string> authors;
	vector<pair<string, string>> edges;

	//String <--> int ����� ��ȯ�� ���� bidirectional map ���
	//map<string, int> -> <vertex label, vertex index>
	typedef boost::bimap<string, int> bm_type;
	bm_type node_ids;
	vector<simple_edge> edges_indexes;	//int�� ��ȯ�� edge

	int node_cnt = 0;
	qDebug() << "* graph reading start";

	//�� �پ� �о Parse
	while (std::getline(in, line) && !line.empty()) {
		//boost::split �̿��� ���ڿ� �и�
		//tokens[0]: Author1
		//tokens[1]: Author2
		//tokens[2]: Published year.
		boost::split(tokens, line, boost::is_any_of("||"), boost::token_compress_on);

		const string& author1 = tokens[0];		// ��� �̸�
		const string& author2 = tokens[1];		// ������ �̸�
		if (node_ids.left.find(author1) == node_ids.left.end()) {		// ��� �̸��� ���� �� ���ٸ�
			node_ids.insert(bm_type::value_type(author1, node_cnt++));	// �߰�
		}

		if (node_ids.left.find(author2) == node_ids.left.end()) {		// ������ �̸��� ���� �� ���ٸ�
			node_ids.insert(bm_type::value_type(author2, node_cnt++));	// �߰�
		}

		edges.push_back(pair<string, string>(author1, author2));

		//debug
		if (node_cnt > NODE_LIMIT) break;
	}
	for (auto i = node_ids.begin(); i != node_ids.end(); i++, qDebug() << " ")
	{
		string num = to_string(i->right);
		qDebug() << num.c_str() << " : " << i->left.c_str();
	}
	cgraph_cnt = node_cnt;
	qDebug() << "* graph reading complete";
	qDebug() << "* # of nodes: " << node_cnt;
	qDebug() << "* # of edges: " << edges.size();

	//edge conversion
	//<string, string> to <int, int>
	//using boost::bimap (bidirectional map)
	for (auto edge : edges) {
		edges_indexes.push_back({
			node_ids.left.find(edge.first)->get_right(),
			node_ids.left.find(edge.second)->get_right()
		});
	}
	//Graph --> defined in "CoauthorshipGraphWidget.h"
	CGraph graph(edges_indexes.begin(), edges_indexes.end(), node_ids.size());
	qDebug() << "edges_indexes : " << edges_indexes.size() << "node_ids : " << node_ids.size();
	//set index property
	qDebug() << "* set vertex property start";
	typedef typename graph_traits<CGraph>::edge_iterator edge_iterator;
	typedef typename graph_traits<CGraph>::vertex_iterator vertex_iterator;
	vertex_iterator vi, vi_end;
	int i = 0;
	for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
		//Vertex Property ����
		//index: 0 ~ ...
		//name : map�� value(i) �������� ã�� Key
		//		map --> map<string, int> (boost bidirectional map)
		boost::put(vertex_index, graph, *vi, i);
		boost::put(vertex_name, graph, *vi,
			node_ids.right.find(i)->get_left());

		++i;
	}
	qDebug() << "* set vertex property end";

	for (auto i = edges.begin(); i != edges.end(); i++)
		qDebug() << i->first.c_str() << "-----" << i->second.c_str() << endl;
	//graph layout calculation
	//using boost::random_graph_layout and boost::kamada_kawai_spring_layout
	//vertex���� ���� ��ǥ�� property�� ����
	//���� �ڵ�: http://www.boost.org/doc/libs/1_63_0/libs/graph/test/layout_test.cpp
	//(-> �ܼ� ���)
	qDebug() << "* make graph layout start";
	typedef square_topology<> Topology;
	minstd_rand gen;
	Topology topology(gen, (double)SCREEN_SIZE);
	Topology::point_type origin;
	origin[0] = origin[1] = (double)SCREEN_SIZE;
	Topology::point_difference_type extent;
	extent[0] = extent[1] = (double)SCREEN_SIZE;
	rectangle_topology<> rect_top(gen,
		-SCREEN_SIZE / 2, -SCREEN_SIZE / 2,
		SCREEN_SIZE / 2, SCREEN_SIZE / 2);

	switch (LAYOUT_MODE) {
	case GRAPH_LAYOUT::RANDOM_LAYOUT:
		random_graph_layout(graph, get(vertex_position, graph), rect_top);
		break;

	case GRAPH_LAYOUT::CIRCLE_LAYOUT:
		circle_graph_layout(graph, get(vertex_position, graph), SCREEN_SIZE / 2);
		break;

		//case GRAPH_LAYOUT::KAMADA_KAWAI_LAYOUT:
		//	kamada_kawai_spring_layout(graph,
		//		get(vertex_position, graph),
		//		get(edge_weight, graph),
		//		topology,
		//		side_length((double)SCREEN_SIZE)
		//	);
		//	break;

	case GRAPH_LAYOUT::FRUCHTERMAN_REINGOLD_LAYOUT:
		fruchterman_reingold_force_directed_layout(graph,
			get(vertex_position, graph),
			topology,
			attractive_force(square_distance_attractive_force())
			.cooling(linear_cooling<double>(50))
		);
		break;
	}
	qDebug() << "* make graph layout end";

	return graph;
}

//=====================================================================================================

int dblpAnalysisApp::load_COAU_FILE()
{
	try {
		ifstream fin(COAU_FILENAME);
		cgraph = read_cgraph(fin);
		fin.close();
	}
	catch (const std::exception& e) {
		qDebug() << "Error: " << e.what();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}