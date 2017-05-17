#pragma once
#include <QtWidgets/QMainWindow>
#include "qdialog.h"
#include <iostream>
#include <qdebug.h>

#include<qcoreapplication.h>
#include <qthread.h>

#include <qlistwidget.h>
#include <QGridLayout>
#include <qpushbutton.h>

#include <webdriverxx.h>

using namespace webdriverxx;
using namespace std;

class ListInput :
	public QDialog
{
	Q_OBJECT

private:
	QListWidget* listwidget;
	QPushButton* selectButton;
	int widgetCnt;					// 재귀적으로 불릴 때 창이 몇번째로 열렸는지 알려줌
	int authorIndex;				// 선택된 author의 index

public:
	explicit ListInput(QWidget *parent = 0, int widgetCnt = 0);
	~ListInput();

	void addItem(QString data) { listwidget->addItem(data); }

signals:
	void throwSecondWidgetIndex(int index);

public slots:
	void getSecondWidgetIndex(int index);
	void on_PushSelectButton_Clicked();		// 버튼을 누르면 크롤링 시작
};

