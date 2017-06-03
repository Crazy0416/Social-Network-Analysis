#include "dblpanalysisapp.h"
#include <qstatusbar.h>
#include <qaction.h>
#include "qmainwindow.h"

dblpAnalysisApp::dblpAnalysisApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//subscribeListWidget = new QListWidget(this);
	// 배경 화면 설정
	ui.setupUi(this);
	QPixmap bkgnd("bkgnd.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);

	// 창 크기 고정
	this->setFixedSize(600, 400);

	// 파일 로드
	load_CGI();
	load_PGI();
	// 파일 업데이트
	QTimer *pTimer = new QTimer(this);
	QObject::connect(pTimer, SIGNAL(timeout()), SLOT(updateCGI()));
	QObject::connect(pTimer, SIGNAL(timeout()), SLOT(updatePGI()));
	pTimer->start(10000); // 1sec == 1000mils;

	// 메뉴 바 설정
	QMenu *pAppMenu;
	QStatusBar *pStatusBar;

	// 기본 기능 메뉴 설정
	QAction *pSlotVisualize = new QAction(tr("Visualization"), this);
	QObject::connect(pSlotVisualize, SIGNAL(triggered()), this, SLOT(Main_Visualization()));

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
	
	// 추가 기능 메뉴 설정
	QAction *pSlotVisualizeInCircle = new QAction(tr("Visualization In Circle Layer"), this);
	QObject::connect(pSlotVisualizeInCircle, SIGNAL(triggered()), this, SLOT(Main_VisualizationInCircle()));

	QAction *pSlotFiltering = new QAction(tr("Filtering"), this);
	QObject::connect(pSlotFiltering, SIGNAL(triggered()), this, SLOT(Main_Filtering()));

	QAction *pSlotshowSubscribe = new QAction(tr("showSubscribeList"), this);
	QObject::connect(pSlotshowSubscribe, SIGNAL(triggered()), this, SLOT(showSubscribe()));

	QAction *pSlotmanageSubscribe = new QAction(tr("Subscribe Manage"), this);
	QObject::connect(pSlotmanageSubscribe, SIGNAL(triggered()), this, SLOT(manageSubscribe()));

	pAppMenu = menuBar()->addMenu(tr("Additional Menu"));
	pAppMenu->addAction(pSlotshowSubscribe);
	pAppMenu->addAction(pSlotmanageSubscribe);
	pAppMenu->addAction(pSlotVisualizeInCircle);
	pAppMenu->addAction(pSlotFiltering);
}

dblpAnalysisApp::~dblpAnalysisApp()
{

}

//=====================================================================================================
void dblpAnalysisApp::load_CGI()
{
	try {
		ifstream fsIn(COAUTHORSHIP_FILENAME);
		pCGI = new CoauthorGraphItem(fsIn);

		fsIn.close();
	}
	catch (const std::exception& e) {
		qDebug() << "Coauthor File Reading Error: " << e.what();
	}
}
void dblpAnalysisApp::load_PGI()
{
	try {
		ifstream fsIn(PAPER_FILENAME);
		pPGI = new PaperGraphItem(fsIn);

		fsIn.close();
	}
	catch(const std::exception& e) {
		qDebug() << "Paper File Reading Error: " << e.what();
	}
}
//=====================================================================================================
void dblpAnalysisApp::updateCGI()
{
	try {
		ifstream fsIn(COAUTHORSHIP_FILENAME);
		pCGI->updateGraph(fsIn);

		fsIn.close();
	}
	catch (const std::exception& e) {
		qDebug() << "Coauthor File Reading Error: " << e.what();
	}
}
void dblpAnalysisApp::updatePGI()
{
	try {
		ifstream fsIn(PAPER_FILENAME);
		pPGI->updateGraph(fsIn);

		fsIn.close();
	}
	catch (const std::exception& e) {
		qDebug() << "Paper File Reading Error: " << e.what();
	}
}
//=====================================================================================================
void dblpAnalysisApp::Main_Visualization()
{
	subwindow* sw = new subwindow;
	sw->setGraph(pCGI);
	sw->show();
}
void dblpAnalysisApp::Main_TopK()
{
	CoauthorGraphItem* pTempCGI = new CoauthorGraphItem(pCGI->getGraph());

	bool ok;
	QString K = QInputDialog::getText(NULL, "K Size", "K Size", QLineEdit::Normal, "", &ok);
	if (ok && !K.isEmpty())
		;// K 숫자 입력인지 예외 처리

	pTempCGI->TopK(K.toInt());

	subwindow* sw = new subwindow;
	sw->setGraph(pTempCGI);
	sw->show();
}
void dblpAnalysisApp::Main_TopKfromA()
{
	CoauthorGraphItem* pTempCGI = new CoauthorGraphItem(pCGI->getGraph());

	bool ok;
	QString K = QInputDialog::getText(NULL, "K Size", "K Size", QLineEdit::Normal, "", &ok);
	if (ok && !K.isEmpty())
		;// K 숫자 입력인지 예외 처리

	QString author = QInputDialog::getText(NULL, "Author Name", "Author Name", QLineEdit::Normal, "", &ok);
	// author name 없는 경우 예외 처리

	pTempCGI->TopKfromA(K.toInt(),author);

	subwindow* sw = new subwindow;
	sw->setGraph(pTempCGI);
	sw->show();
}
void dblpAnalysisApp::Main_Chain()
{
	CoauthorGraphItem* pTempCGI = new CoauthorGraphItem(pCGI->getGraph());

	bool ok;
	QString author1 = QInputDialog::getText(NULL, "Author1 Name", "Author1 Name", QLineEdit::Normal, "", &ok);
	QString author2 = QInputDialog::getText(NULL, "Author2 Name", "Author2 Name", QLineEdit::Normal, "", &ok);
	// author name 없는 경우 예외 처리

	pTempCGI->chain(author1, author2);

	subwindow* sw = new subwindow;
	sw->setGraph(pTempCGI);
	sw->show();
}

void dblpAnalysisApp::Main_AuthorCrawling()
{
	// 리스트 위젯을 넣을 창 만듦
	ListInput* list = new ListInput();

	// 리스트 창에 author 데이터 넣음
	graph_traits<Graph>::vertex_iterator vi, ve;
	auto Cgraph_vertex_name = get(vertex_name, *pCGI->getGraph());
	int cnt = 1;
	for (tie(vi, ve) = vertices(*pCGI->getGraph()); vi != ve; ++vi) {
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
void dblpAnalysisApp::Main_VisualizationInCircle()
{
	CoauthorGraphItem* pTempCGI = new CoauthorGraphItem(pCGI->getGraph());

	pTempCGI->VisualizationInCircle();

	subwindow* sw = new subwindow;
	sw->setGraph(pTempCGI);
	sw->show();
}

void dblpAnalysisApp::Main_Filtering()
{
	qDebug() << "Hello";
	PaperGraphItem* pTempPGI = new PaperGraphItem(pPGI->getGraph());

	bool ok;
	QString year = QInputDialog::getText(NULL, "Year", "Year", QLineEdit::Normal, "", &ok);
	QString conf = QInputDialog::getText(NULL, "Conference", "Conference", QLineEdit::Normal, "", &ok);

	pTempPGI->Filtering(year, conf);

	subwindow* sw = new subwindow;
	sw->setGraph(pTempPGI);
	sw->show();
}

void dblpAnalysisApp::showSubscribe()
{

	QListWidget* subscribeList = new QListWidget();
	for (int i = 0; i < subscribeArray.size(); i++)
	{
		subscribeList->addItem(subscribeArray[i]);
	}
	subscribeList->show();
}

void dblpAnalysisApp::manageSubscribe()
{
	subscribemanage = new SubscribeManageWidget();
	subscribemanage->show();
}
//=====================================================================================================