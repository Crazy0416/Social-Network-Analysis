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
	int widgetCnt;					// ��������� �Ҹ� �� â�� ���°�� ���ȴ��� �˷���
	int authorIndex;				// ���õ� author�� index

public:
	explicit ListInput(QWidget *parent = 0, int widgetCnt = 0);
	~ListInput();

	void addItem(QString data) { listwidget->addItem(data); }

signals:
	void throwSecondWidgetIndex(int index);

public slots:
	void getSecondWidgetIndex(int index);
	void on_PushSelectButton_Clicked();		// ��ư�� ������ ũ�Ѹ� ����
};

