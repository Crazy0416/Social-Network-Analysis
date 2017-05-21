#include "SubscribeManageWidget.h"

/*
*/
SubscribeManageWidget::SubscribeManageWidget(QWidget *parent)
	: QDialog(parent)
{
	QGridLayout *topLayout = new QGridLayout(this);
	subscribeList = new QListWidget(this);
	addButton = new QPushButton("Add subscribe", this);
	deleteButton = new QPushButton("Delete subscribe", this);

	topLayout->addWidget(subscribeList, 100, 1000);
	topLayout->addWidget(addButton, 200, 100);
	topLayout->addWidget(deleteButton, 400, 100);

	setLayout(topLayout);
	setBaseSize(500, 1000);

}

SubscribeManageWidget::~SubscribeManageWidget()
{
}
