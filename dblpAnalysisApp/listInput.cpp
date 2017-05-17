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
	QString strData = listwidget->currentItem()->text();			// �ֱ� ������ text ��ȯ
	QStringList list = strData.split('.');
	int indexData = list[0].toInt();

	qDebug() << "current index : " + QString::number(indexData);

	if (strData != NULL)		// ��ĭ�� �ƴϰ� ok ��ư�� ������ ���
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

		if (widgetCnt == 0 && (firefox.GetUrl().find("dblp.uni-trier.de/search") != -1))		// �Է��� author�� ���� ����� �����ϴ� ���
		{
			menu = firefox.FindElements(ById("completesearch-authors"));
			vector<Element> all_author = menu[0].FindElements(ByCss("a[href]"));
			
			int cnt = 0;		// all_author count - 1
			int listIndex = 1;	// span index
			int *authorlistIndex = new int[all_author.size()];	// a[href]�� ������ Element �迭 �� span Element�� ������, �� author�� ������ element ����
			for (int i = 0; i < all_author.size(); i++) authorlistIndex[i] = -1;		// �ʱ�ȭ
			
			QStringList authorList;
			for (Element i : all_author)
			{
				if (i.FindElements(ByTag("span")).size() != 0)
				{
					QString tmp =  QString::number(listIndex) + "." + QString::fromStdString(i.GetText()); // TODO : ������ �ε��� ��� �� ���߿� ����Ʈ�信�� �� �� �� �ε����� ���� â�� �������
					qDebug() << tmp;
					authorList << tmp;
					authorlistIndex[cnt] = listIndex;		// authorlistIndex[cnt]�� span�� index �ִ´�.
					listIndex++;
				}
				cnt++;
			}
			// �˻��� author�� ����� �̸��� ���� author ���� â
			QString secontAuthor = QInputDialog::getItem(this, "choose author", "Choose author", authorList);
			QStringList secondAuthorSplit = secontAuthor.split(".");
			int secondAuthorIndex = secondAuthorSplit[0].toInt();	

			// index log ���
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
		else																// �Է��� ����� �� �� ��� �����ϴ� ���
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
	
	this->close();								// �� ���� ����
}

void ListInput::getSecondWidgetIndex(int index)
{
	authorIndex = index;
	qDebug() << "ready to crawling!!!";
}