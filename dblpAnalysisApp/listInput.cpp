#include "listInput.h"



ListInput::ListInput(QWidget *parent)
	: QDialog(parent)
{
	QGridLayout *topLayout = new QGridLayout(this);
	listwidget = new QListWidget(this);
	selectButton = new QPushButton("select",this);
	topLayout->addWidget(listwidget, 100, 1000);
	topLayout->addWidget(selectButton, 200, 100);
	setLayout(topLayout);
	setBaseSize(500, 500);

	//connect
	QObject::connect(selectButton, SIGNAL(clicked()), this, SLOT(on_PushSelectButton_Clicked()));
}


ListInput::~ListInput()
{
}

void ListInput::on_PushSelectButton_Clicked()
{
	listwidget->currentItem()->text();			// 최근 아이템 text 반환
	this->close();								// 이 위젯 종료
}
