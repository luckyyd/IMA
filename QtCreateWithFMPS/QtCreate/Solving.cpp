#include "Solving.h"
#include "qtcreate.h"
#include <QFile>
#include <QTextStream>
#include <QtWidgets/QMessageBox>
#include <QList>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QPainter>
#include <QTime>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QLineEdit>
#include <QRegExpValidator>
#include <QRegExp>
#include <QValidator>

QList  <ActionAttribute *>   Action;
bool   LoadActionFlag;

MyTimeSolveProject::MyTimeSolveProject(QWidget *parent)
: QMainWindow(parent)
{
	//QLabel qlabel = new QLabel();
	/*QPushButton *BushButton;
	BushButton = new QPushButton(GantFrame);*/

	CountMouseClicked = 0;
	LastY = -1;

	//resize(800, 550);
	CreateModifActionMenu();           // �������ӣ��޸ģ�ɾ������

	ShowText = new QLabel("Simple Gantt Chart", this);
	ShowText->setAlignment(Qt::AlignCenter);
	LoadActionFlag = false;
	this->setUpdatesEnabled(true);
}

void MyTimeSolveProject::ReadFile()         // ���ļ�
{
	QFile   fRead("solved.txt");
	if (fRead.open(QIODevice::ReadOnly | QIODevice::Text))  // ���ļ��Ƿ�ɹ�
	{
		QTextStream  tRead(&fRead);
		ActionAttribute *Temp;

		tRead.readLine();                      // <begin_plan>
		tRead.readLine();                      // <begin_num_actions>
		ActionNum = tRead.readLine().toInt();  // ��¼Action�ĸ�����
		tRead.readLine();                      // <end_num_actions>

		while (!tRead.atEnd())
		{
			tRead.readLine();                   // <begin_action>
			Temp = new ActionAttribute;
			Temp->ActionName = tRead.readLine();          // #������
			Temp->BeginTime = tRead.readLine().toInt();  // #������ʼʱ��
			Temp->LastTime = tRead.readLine().toInt();  // #�����ĳ���ʱ��

			label = new QLabel(this);                     // ��ǩ
			label->setText(Temp->ActionName);

			ShowTime = new QPushButton(this);     // ��ʾʱ�����ƿؼ�

			Temp->btn = ShowTime;
			Temp->label = label;

			// ��ȡ��Դ�����
			tRead.readLine();          //  <resource_num>
			int RecondSourceNum = tRead.readLine().toInt();          //  num
			tRead.readLine();          //  <end_resource_num>

			Resource *tmp_source;

			for (int i = 0; i < RecondSourceNum; i++)
			{
				tmp_source = new Resource;
				tmp_source->SourceName = tRead.readLine();
				tmp_source->SourceNum = tRead.readLine().toInt();
				Temp->source.push_back(tmp_source);
			}
			tRead.readLine();         // <all_resource>

			if (!tRead.atEnd())
			{
				Action.push_back(Temp);
			}
			tRead.readLine();                  // <end_action>
		}
	}
	else
	{
		QMessageBox::warning(NULL, "Open File Fail!",
			tr("Open File %1 Fail! \n%2").arg(fRead.fileName()).arg(fRead.errorString()));
	}

	fRead.close();
}

void MyTimeSolveProject::CreateModifActionMenu()
{
	FileOpenBtn = new QPushButton(tr("&Load File"), this);
	SaveBtn = new QPushButton("&FileSave", this);

	connect(FileOpenBtn, SIGNAL(clicked()), this, SLOT(LoadAction()));
	connect(SaveBtn, SIGNAL(clicked()), this, SLOT(SaveAction()));
}

void MyTimeSolveProject::SaveAction()
{
	QString FileName("ToBeSolving.txt");
	QFile   fWrite(FileName);
	if (fWrite.open(QIODevice::WriteOnly | QIODevice::Text))  // �ļ��Ƿ�ɹ�
	{
		QTextStream  tWrite(&fWrite);

		int len = Action.size();

		tWrite << "<begin_plan>" << "\n";             // <begin_plan>
		tWrite << "<begin_num_actions>\n";          // <begin_num_actions>
		tWrite << QString::number(len, 10) << endl;   // ��¼Action�ĸ�����
		tWrite << "<end_num_actions>" << endl;        // <end_num_actions>

		for (int i = 0; i < len; i++)
		{
			tWrite << "<begin_action>" << endl;
			tWrite << Action[i]->ActionName << endl;
			tWrite << QString::number(Action[i]->BeginTime) << endl;
			tWrite << QString::number(Action[i]->LastTime) << endl;

			tWrite << "resource_num>" << endl;
			tWrite << QString::number(Action[i]->source.size()) << endl;
			tWrite << "<end_resource_num>" << endl;

			for (int index = 0; index < Action[i]->source.size(); index++)
			{
				tWrite << Action[i]->source[index]->SourceName << endl;
				tWrite << QString::number(Action[i]->source[index]->SourceNum) << endl;
			}
			tWrite << "<all_resource>" << endl;
			tWrite << "<end_action>" << endl;
		}

		tWrite << "<end_plan>";

		fWrite.close();
		QMessageBox message(QMessageBox::NoIcon, "Save File Box",
			tr("Save File in \"%1\" successfully! \n Do you want to exit?").arg(FileName),
			QMessageBox::Yes | QMessageBox::No, NULL);

		if (message.exec() == QMessageBox::Yes)
		{
			this->close();
		}

	}
	ActionAttribute *temp;                   // �����ļ����ͷ�Action������ڴ档
	for (int i = 0; i < Action.size(); i++)
	{
		temp = Action[i];
		delete temp;
	}
}

void MyTimeSolveProject::paintEvent(QPaintEvent *) // ���档
{
	int  i = 0;
	int  WindowWidth = width();
	int  MenuWidth = WindowWidth / 5;

	if (Action.size() > 0)
	{
		BeginTime = Action[0]->BeginTime;
		EndTime = Action[0]->BeginTime + Action[0]->LastTime;

		for (i = 1; i < Action.size(); i++)
		{
			int endtime = Action[i]->BeginTime + Action[i]->LastTime;
			if (BeginTime > Action[i]->BeginTime)
			{
				BeginTime = Action[i]->BeginTime;
			}

			if (EndTime < endtime)
			{
				EndTime = endtime;
			}

		}

		int  TimeElapedSize = TimeElaped.size() - 1;
		int  StartX = WindowWidth >> 3;
		int  EndX = (WindowWidth >> 6) * 55;
		int  EndSourceX = (WindowWidth >> 3) * 5;
		int  XActionLength = (EndX - StartX) / (EndTime - BeginTime);
		int  SegmentTime = (EndTime - BeginTime) / SEGMENT;
		int  XLength = SegmentTime * XActionLength;

		//  ����ʱ�侫��
		CountTime = 0;
		if (TimeElaped.isEmpty())   // ����ʱ�䱶�ʺ���ȥʱ��ļ�¼������T = t1*last1 + t2*last2...
		{
			CountTime = ChangingTime.elapsed() / 1000 + BeginTime;
		}
		else
		{
			for (i = 0; i < TimeElapedSize; i++)
			{
				if (i == 0)
				{
					CountTime += TimeElaped[i]->ElapedTime*TimeElaped[i]->ElapedTimes;
				}
				else
				{
					CountTime += (TimeElaped[i]->ElapedTime - TimeElaped[i - 1]->ElapedTime)*TimeElaped[i]->ElapedTimes;
				}
			}

			CountTime += (ChangingTime.elapsed() / 1000 - TimeElaped[i - 1]->ElapedTime)*TimeElaped[i]->ElapedTimes + BeginTime;
		}

		timelabel->setText(QString::number(CountTime, 10) += " s");

		// ͼ�λ�  �������ʱ̬Actionͼ
		QPainter  pa(this);
		setStyleSheet("color:blue");
		setFont(QFont("Times", 12, QFont::Bold));

		pa.drawText(StartX, 65, 80, 15, Qt::AlignLeft, QString::number(BeginTime));

		for (i = 0; i <= SEGMENT; i++)
		{
			pa.drawLine(StartX + i*XLength, 88, StartX + (i + 1)*XLength, 88);
			pa.drawLine(StartX + (i + 1)*XLength, 88, StartX + (i + 1)*XLength, 85);
			pa.drawText(StartX + (i + 1)*XLength, 65, XLength, 15, Qt::AlignLeft,
				QString::number(BeginTime + (i + 1)*SegmentTime));
		}
		pa.drawLine(StartX + i*XLength, 88, StartX + (i + 1)*XLength, 88);

		const int Htriangle[3][2] =
		{
			{ StartX + (i + 1)*XLength, 90 },
			{ StartX + (i + 1)*XLength, 86 },
			{ StartX + (i + 1)*XLength + 2, 88 }
		};
		QPen thickPen(palette().foreground(), 1.5);
		QPen thinPen(palette().foreground(), 0.5);
		pa.setPen(thinPen);
		pa.setBrush(palette().foreground());
		pa.drawPolygon(QPolygon(3, &Htriangle[0][0]));//����һ��С�ĵ�������

		for (i = 0; i < Action.size(); i++)            // ����
		{
			pa.drawLine(StartX, 88 + i * 30, StartX, 88 + (i + 1) * 30);
			pa.drawLine(StartX, 88 + (i + 1) * 30, StartX - 3, 88 + (i + 1) * 30);
			Action[i]->label->setFont(QFont("Times", 12, QFont::Bold));
			Action[i]->label->setAlignment(Qt::AlignRight);
			Action[i]->label->show();             //  ����show��������Action������ʾ��
			Action[i]->btn->setFocusPolicy(Qt::NoFocus);

			switch (i % 3)
			{
			case 0:
				Action[i]->label->setStyleSheet("color:red");
				Action[i]->btn->setStyleSheet("background-color:red");
				break;

			case 1:
				Action[i]->label->setStyleSheet("color:green");
				Action[i]->btn->setStyleSheet("background-color:green");
				break;

			case 2:
				Action[i]->label->setStyleSheet("color:blue");
				Action[i]->btn->setStyleSheet("background-color:blue");
				break;
			}

			if (i != 0)
			{
				Action[i]->label->setGeometry(0, 90 + i * 30, StartX - 10, 20);
			}
			else
			{
				Action[0]->label->setGeometry(0, 90, StartX - 6, 20);
			}

			if (CountTime < Action[i]->BeginTime + Action[i]->LastTime)
			{
				Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 90 + i * 30,
					XActionLength*(CountTime - Action[i]->BeginTime), 29);
			}
			else
			{
				Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 90 + i * 30,
					XActionLength*Action[i]->LastTime, 29);
			}
			Action[i]->btn->show();   // ����show��������Action������ʾ��
		}
		pa.drawLine(StartX, 88 + i * 30, StartX, 100 + i * 30);

		const int Vtriangle[3][2] =
		{
			{ StartX - 2, 100 + i * 30 },
			{ StartX + 2, 100 + i * 30 },
			{ StartX, 102 + i * 30 }
		};

		pa.drawPolygon(QPolygon(3, &Vtriangle[0][0]));//����һ��С�ĵ�������


		/////////// ������Դͼ ///////////////////////////////////////////////////////////////
		//    pa.drawRect(0,400,10+CountTime,20);
		////////////////////////////////////////////////////////////////////////////////////

		QList <Resource >  SourceArray;
		Resource  TempSource;

		int ActionIndex = 0, SourceIndex = 0;
		// �Ȱ����в�ͬ����Դ������ SourceArray��. ���Ԥ�Ⱦ�֪��Ҫ���ĵ�������Դ���������ȥ��һ����

		TempSource.SourceName = Action[0]->source[0]->SourceName;  //bug��ÿ��action����ķ���Դ�����action[0]���ķ���Դ����ֶδ���
		TempSource.SourceNum = 0;

		SourceArray.push_back(TempSource);

		for (ActionIndex = 0; ActionIndex < Action.size(); ActionIndex++)
		{
			for (SourceIndex = 0; SourceIndex < Action[ActionIndex]->source.size(); SourceIndex++)
			{
				bool IfInArray = false;
				for (int j = 0; j < SourceArray.size(); j++)
				{
					if (SourceArray[j].SourceName == Action[ActionIndex]->source[SourceIndex]->SourceName)
					{
						IfInArray = true;
						break;
					}
				}

				if (!IfInArray)
				{
					TempSource.SourceName = Action[ActionIndex]->source[SourceIndex]->SourceName;
					TempSource.SourceNum = 0;
					SourceArray.push_back(TempSource);
				}
			}
		}

		// ������ȥ��ʱ�䣬�ж�ĳ��action�Ƿ�ִ�����ˡ��ǣ���Ѻķѵ���Դ����SourceArray�С�
		QList <int> RecordEndAction;
		for (ActionIndex = 0; ActionIndex < Action.size(); ActionIndex++)
		{
			if (CountTime > Action[ActionIndex]->BeginTime + Action[ActionIndex]->LastTime)
			{
				// ���˵��Ѿ�ִ�����Action
				bool  ifEnd = false;
				for (int j = 0; j < RecordEndAction.size(); j++)
				{
					if (RecordEndAction[j] == ActionIndex)
					{
						ifEnd = true;
						break;
					}
				}

				if (ifEnd)             // ���Ϊ�棬���ñ�־Action����Դ�����Ѿ���¼���ˣ�ִ���¸�ѭ����
				{
					continue;
				}

				//  ��¼���ĵ���Դ��
				for (SourceIndex = 0; SourceIndex < Action[ActionIndex]->source.size(); SourceIndex++)
				{
					for (int k = 0; k < SourceArray.size(); k++)
					{
						if (SourceArray[k].SourceName == Action[ActionIndex]->source[SourceIndex]->SourceName)
						{
							SourceArray[k].SourceNum += Action[ActionIndex]->source[SourceIndex]->SourceNum;
							RecordEndAction.push_back(ActionIndex);
						}
					}
				}
			}
		}

		//        ���Լ�����Դ��ͬ�ĸ�����
		//        pa.drawText(400,400,50,20,Qt::AlignCenter,QString::number(SourceArray.size(),10));

		///// ͼ�λ� ���ĵ���Դ ��������Դ��num��Ϊ�ؼ���ʾ���ȵı�׼��     
		int  XSourceLength = (EndSourceX - StartX) / MAXSOURCENUM;  // ��λnum����
		int  XSegmentSourceLength = XSourceLength * SEGMENT;        // �γ���

		int j = 0;         // index
		for (j = 0; j < SEGMENT; j++)
		{
			pa.drawLine(StartX + XSegmentSourceLength * j, 148 + (i + 1) * 30, StartX + XSegmentSourceLength * (j + 1), 148 + (i + 1) * 30);
			pa.drawLine(StartX + XSegmentSourceLength * (j + 1), 148 + (i + 1) * 30, StartX + XSegmentSourceLength * (j + 1), 146 + (i + 1) * 30);
			pa.drawText(StartX + XSegmentSourceLength * j, 126 + (i + 1) * 30, XSegmentSourceLength, 15, Qt::AlignLeft, QString::number(j*SEGMENT));
		}
		pa.drawText(StartX + XSegmentSourceLength * j, 126 + (i + 1) * 30, XSegmentSourceLength, 15, Qt::AlignLeft, QString::number(j*SEGMENT));

		const int HSourceTriangle[3][2] =
		{
			{ StartX + XSegmentSourceLength * j, 150 + (i + 1) * 30 },
			{ StartX + XSegmentSourceLength * j, 146 + (i + 1) * 30 },
			{ StartX + XSegmentSourceLength * j + 2, 148 + (i + 1) * 30 }
		};
		pa.drawPolygon(QPolygon(3, &HSourceTriangle[0][0]));//����һ��С�ĵ�������

		for (j = 0; j < SourceArray.size(); j++)
		{
			pa.drawLine(StartX, 148 + (i + 1) * 30 + j * 30, StartX, 148 + (i + 1) * 30 + (j + 1) * 30);
			pa.drawLine(StartX, 148 + (i + 1) * 30 + (j + 1) * 30, StartX - 3, 148 + (i + 1) * 30 + (j + 1) * 30);
		}
		pa.drawLine(StartX, 148 + (i + 1) * 30 + j * 30, StartX, 160 + (i + 1) * 30 + j * 30);

		const int VSourceTriangle[3][2] =
		{
			{ StartX - 2, 160 + (i + 1) * 30 + j * 30 },
			{ StartX + 2, 160 + (i + 1) * 30 + j * 30 },
			{ StartX, 162 + (i + 1) * 30 + j * 30 }
		};

		pa.drawPolygon(QPolygon(3, &VSourceTriangle[0][0]));//����һ��С�ĵ�������

		for (j = 0; j < SourceArray.size(); j++)
		{
			switch (j % 3)
			{
			case 0:
				pa.setBrush(Qt::red);
				break;
			case 1:
				pa.setBrush(Qt::blue);
				break;
			case 2:
				pa.setBrush(Qt::green);
				break;
			}

			pa.drawRect(StartX, 148 + (i + 1) * 30 + j * 30, SourceArray[j].SourceNum* XSourceLength, 30);

			switch (j % 3)
			{
			case 0:
				pa.setPen(Qt::red);
				break;
			case 1:
				pa.setPen(Qt::blue);
				break;
			case 2:pa.setPen(Qt::green);
				break;
			}

			pa.drawText(0, 148 + (i + 1) * 30 + j * 30, StartX - 6, 30, Qt::AlignRight, SourceArray[j].SourceName);
			pa.setPen(Qt::blue);
		}

		pa.drawText(EndSourceX + 70, 340, 120, 30, Qt::AlignLeft, "Current Time:");
		timelabel->setGeometry(EndSourceX + 182, 330, 120, 50);
		timelabel->setFont(QFont("Times", 20, QFont::Bold));
		timelabel->show();

		SetTimelabel->setGeometry(EndSourceX + 70, 382, 80, 25);           // ����ʱ�䱶��
		SetTimelabel->show();
		SetTimeEdit->setGeometry(EndSourceX + 150, 378, 40, 25);
		SetTimeEdit->show();
		pa.drawText(EndSourceX + 190, 382, 70, 15, Qt::AlignLeft, "s");
		SetTimeBtn->setGeometry(EndSourceX + 210, 378, 70, 25);
		SetTimeBtn->show();
	}

	ShowText->setGeometry(0, 20, width(), 32);   // Simple Gantt Chart Demo
	FileOpenBtn->setGeometry(0, 0, MenuWidth, 20);
	SaveBtn->setGeometry(MenuWidth << 2, 0, MenuWidth, 20);
	SaveBtn->show();

}


void MyTimeSolveProject::LoadAction()
{
	if (!LoadActionFlag)
	{
		ReadFile();

		if (Action.empty())
		{
			QMessageBox::question(NULL, "Remind: ", "There is no action!");
		}
		else
		{
			ChangingTime.start();              // ��ʱ��ʼ��
			this->setFocus();                  // ����������Ϊ���㡣

			timelabel = new QLabel(this);            // ��ʾʱ��
			timelabel->setAlignment(Qt::AlignLeft);

			Times = 1;
			SetTimelabel = new QLabel("Set Times:", this);          // ����ʱ�䱶��  1��*���ʡ�
			SetTimeEdit = new QLineEdit("1", this);
			SetTimeEdit->setAlignment(Qt::AlignRight);
			SetTimeBtn = new QPushButton("&Set", this);
			connect(SetTimeBtn, SIGNAL(clicked()), this, SLOT(SetTimes()));  //����ʱ��
			QRegExpValidator  *regexpvalidator = new QRegExpValidator(QRegExp("[0-9]{0,4}"), this);
			SetTimeEdit->setValidator(regexpvalidator);
			SetTimelabel->setFont(QFont("Times", 12, QFont::Bold));
			SetTimeEdit->setFont(QFont("Times", 12, QFont::Bold));
			SetTimeBtn->setFont(QFont("Times", 12, QFont::Bold));
		}

		LoadActionFlag = true;
	}
	this->setFocus();
	this->update();
}

void MyTimeSolveProject::SetTimes()
{
	if (!SetTimeEdit->text().isEmpty())
	{
		int TempTimes = SetTimeEdit->text().toInt();
		if (Times != TempTimes)   // ������õ�ʱ�䱶����֮ǰ��һ��
		{
			ElapsedTimeStruct *temp = new ElapsedTimeStruct;
			temp->ElapedTimes = Times;          // ����

			temp->ElapedTime = ChangingTime.elapsed() / 1000;

			TimeElaped.push_back(temp);

			Times = TempTimes;
			temp = new ElapsedTimeStruct;
			temp->ElapedTimes = Times;
			TimeElaped.push_back(temp);

			SetTimeEdit->setText(QString::number(Times, 10));
		}
	}
}


