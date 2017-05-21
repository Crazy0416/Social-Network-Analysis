#pragma once

#include <QtWidgets/QMainWindow>
#include <qinputdialog.h>
#include <qgridlayout.h>
#include <qlistwidget.h>
#include <vector>

#include "ui_dblpanalysisapp.h"
#include "GraphItem.h"
#include "subwindow.h"
#include "listInput.h"
#include "SubscribeManageWidget.h"

class dblpAnalysisApp : public QMainWindow
{
	Q_OBJECT

public:
	dblpAnalysisApp(QWidget *parent = 0);
	~dblpAnalysisApp();

	void load_CGI();
	void load_PGI();

private:
	Ui::dblpAnalysisAppClass ui;
	QGraphicsScene *scene;

	const char* COAUTHORSHIP_FILENAME = "dblp-coauthor.txt";
	const char* PAPER_FILENAME = "dblp-paper.txt";

	CoauthorGraphItem* pCGI;
	PaperGraphItem* pPGI;

	QListWidget* subscribeListWidget;		// ������ ����Ʈ ����
	vector<QString> subscribeArray;			// ������ �̸� �迭
	SubscribeManageWidget* subscribemanage;	//	

	public slots :
	// ��Ʈ���� ������ ó��
	void updateCGI(); 
	void updatePGI();

	// �⺻ ���
	void Main_Visualization();
	void Main_TopK();
	void Main_TopKfromA();
	void Main_Chain();
	void Main_AuthorCrawling();

	// �߰� ���
	void showPG();
	void showSubscribe();
	void manageSubscribe();
};
