#pragma once

#include <QtWidgets/QMainWindow>
#include <qinputdialog.h>
#include "ui_dblpanalysisapp.h"

#include "CoauthorshipGraphWidget.h"
#include "listInput.h"

#include <QtWidgets/QApplication>
#include <qlistwidget.h>
#include <QDebug>
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <map>
#include <vector>

#include <boost/graph/fruchterman_reingold.hpp>
//#include <boost/graph/kamada_kawai_spring_layout.hpp>
#include <boost/graph/random_layout.hpp>
#include <boost/graph/circle_layout.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/algorithm/string.hpp>	//boost::split
#include <boost/bimap.hpp>

using namespace std;

enum GRAPH_LAYOUT {
	RANDOM_LAYOUT,
	CIRCLE_LAYOUT,
	//KAMADA_KAWAI_LAYOUT,
	FRUCHTERMAN_REINGOLD_LAYOUT	//slow
};
const int LAYOUT_MODE = GRAPH_LAYOUT::RANDOM_LAYOUT;
const int SCREEN_SIZE = 500;
const int NODE_LIMIT = 50;

class dblpAnalysisApp : public QMainWindow
{
	Q_OBJECT

public:
	dblpAnalysisApp(QWidget *parent = 0);
	~dblpAnalysisApp();

	int load_COAU_FILE();
	CGraph read_cgraph(ifstream& in);

private:
	Ui::dblpAnalysisAppClass ui;
	QGraphicsScene *scene;

	CGraph cgraph;
	int cgraph_cnt;
	CoauthorshipGraphWidget* pCGW;

	const char* COAU_FILENAME = "dblp-coauthor.txt";

	public slots :
	void Main_SlotVisualize();
	void Main_TopK();
	void Main_TopKfromA();
	void Main_Chain();
	void Main_AuthorCrawling();
};
