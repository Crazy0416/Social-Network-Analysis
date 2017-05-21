#pragma once
#include <qdialog.h>
#include <qlistwidget.h>
#include<qcoreapplication.h>
#include <qpushbutton.h>
#include <qgridlayout.h>

class SubscribeManageWidget
	: public QDialog
{
	Q_OBJECT
private:
	// ������ ������� ����Ʈ
	QListWidget* subscribeList;
	// ������ ����� �߰��ϴ� Add ��ư
	QPushButton* addButton;
	// ������ ����� �����ϴ� Delete ��ư
	QPushButton* deleteButton;


public:
	explicit SubscribeManageWidget(QWidget *parent = 0);
	~SubscribeManageWidget();
};

