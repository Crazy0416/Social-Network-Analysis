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
	// 구독한 사람들의 리스트
	QListWidget* subscribeList;
	// 구독할 사람을 추가하는 Add 버튼
	QPushButton* addButton;
	// 구독할 사람을 제거하는 Delete 버튼
	QPushButton* deleteButton;


public:
	explicit SubscribeManageWidget(QWidget *parent = 0);
	~SubscribeManageWidget();
};

