#include "listInput.h"
#include <qinputdialog.h>

ListInput::ListInput(QWidget *parent, int widgetCnt)
	: QDialog(parent)
{
	QGridLayout *topLayout = new QGridLayout(this);
	listwidget = new QListWidget(this);
	selectButton = new QPushButton("select",this);
	topLayout->addWidget(listwidget, 100, 1000);
	topLayout->addWidget(selectButton, 200, 100);
	setLayout(topLayout);
	setBaseSize(500, 500);
	this->widgetCnt = widgetCnt;
	authorIndex = -1;

	//connect
	QObject::connect(selectButton, SIGNAL(clicked()), this, SLOT(on_PushSelectButton_Clicked()));
	QObject::connect(this, SIGNAL(throwSecondWidgetIndex(int index)), this, SLOT(getSecondWidgetIndex(int index)));
}


ListInput::~ListInput()
{
}

void ListInput::on_PushSelectButton_Clicked()
{
	QString strData = listwidget->currentItem()->text();			// 최근 아이템 text 반환
	QStringList list = strData.split('.');
	int indexData = list[0].toInt();

	qDebug() << "current index : " + QString::number(indexData);

	if (strData != NULL)		// 빈칸이 아니고 ok 버튼을 눌렀을 경우
	{
		QString strDataName;
		for (int i = 1; i < list.size(); i++)
		{
			strDataName.append(list[i]);
			if(i != list.size() - 1)
				strDataName.append(".");
		}
		qDebug() << strDataName;

		WebDriver firefox = Start(Firefox());

		string dblpURL = "http://dblp.uni-trier.de/search/author?author=";

		dblpURL += strDataName.toStdString();

		firefox.Navigate(dblpURL);
		vector<Element> menu;

		if (widgetCnt == 0 && (firefox.GetUrl().find("dblp.uni-trier.de/search") != -1))		// 입력한 author가 여러 사람이 존재하는 경우
		{
			menu = firefox.FindElements(ById("completesearch-authors"));
			vector<Element> all_author = menu[0].FindElements(ByCss("a[href]"));
			
			int cnt = 0;		// all_author count - 1
			int listIndex = 1;	// span index
			int *authorlistIndex = new int[all_author.size()];	// a[href]를 가지는 Element 배열 중 span Element를 가지는, 즉 author를 가지는 element 선택
			for (int i = 0; i < all_author.size(); i++) authorlistIndex[i] = -1;		// 초기화
			
			QStringList authorList;
			for (Element i : all_author)
			{
				if (i.FindElements(ByTag("span")).size() != 0)
				{
					QString tmp =  QString::number(listIndex) + "." + QString::fromStdString(i.GetText()); // TODO : 나오는 인덱스 기억 후 나중에 리스트뷰에서 고를 때 그 인덱스를 비교해 창을 띄워야함
					qDebug() << tmp;
					authorList << tmp;
					authorlistIndex[cnt] = listIndex;		// authorlistIndex[cnt]에 span의 index 넣는다.
					listIndex++;
				}
				cnt++;
			}
			// 검색한 author와 비슷한 이름을 가진 author 고르는 창
			QString secontAuthor = QInputDialog::getItem(this, "choose author", "Choose author", authorList);
			QStringList secondAuthorSplit = secontAuthor.split(".");
			int secondAuthorIndex = secondAuthorSplit[0].toInt();	

			// index log 찍기
			qDebug() << "index : " << QString::number(secondAuthorIndex);

			for (int i = 0; i < all_author.size(); i++)
			{
				if (authorlistIndex[i] == secondAuthorIndex)
				{
					string url = all_author[i].GetAttribute("href");
					vector<Element> menu2 = firefox.Navigate(url).FindElements(ByClass("entry"));
					
					for (Element i : menu2)
					{

						QString tmp = QString::fromStdString(i.FindElement(ByClass("title")).GetText());
						qDebug() << tmp;
					}
				}
			}
		}
		else if (widgetCnt == 1 && (firefox.GetUrl().find("dblp.uni-trier.de/search") != -1))
		{
			throwSecondWidgetIndex(indexData);
		}
		else																// 입력한 사람이 단 한 사람 존재하는 경우
		{
			menu = firefox.FindElements(ByClass("entry"));
			
			for (Element i : menu)
			{
				
				QString tmp = QString::fromStdString(i.FindElement(ByClass("title")).GetText());
				qDebug() << tmp << endl;
			}
		}
	}
	else
	{
		qDebug() << "error!!!";
	}
	
	this->close();								// 이 위젯 종료
}

void ListInput::getSecondWidgetIndex(int index)
{
	authorIndex = index;
	qDebug() << "ready to crawling!!!";
}