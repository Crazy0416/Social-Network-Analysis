#pragma once
#include <QtWidgets/QMainWindow>
#include "qdialog.h"
#include <qlistwidget.h>
#include <QGridLayout>
#include <qpushbutton.h>

class ListInput :
	public QDialog
{
	Q_OBJECT

private:
	QListWidget* listwidget;
	QPushButton* selectButton;

public:
	explicit ListInput(QWidget *parent = 0);
	~ListInput();

	void addItem(QString data) { listwidget->addItem(data); }

public slots:
	void on_PushSelectButton_Clicked();
};

