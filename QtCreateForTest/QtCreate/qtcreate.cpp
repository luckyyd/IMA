
#include "qtcreate.h"
#include "ui_qtcreate.h"
#include <qmessagebox.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qtextstream.h>
#include <qdom.h>
#include <map>


QtCreate::QtCreate(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	createActions();
	createMenus();
	createToolBars();
	createGantGraph();
	changeTextEditStyle();
	ui.GantScrollContent->installEventFilter(this);
}

void QtCreate::createActions()
{
	loadFileAction = new QAction(QIcon("Load.png"), tr("Load File"), this);
	loadFileAction->setShortcut(tr("Ctrl+L"));
	loadFileAction->setStatusTip("Load File");
	//connect(loadFileAction, SIGNAL(triggered()), this, SLOT(LoadFile()));
	connect(loadFileAction, SIGNAL(triggered()), this, SLOT(LoadPartitionFile()));
	connect(loadFileAction, SIGNAL(triggered()), this, SLOT(LoadTaskFile()));

	saveFileAction = new QAction(QIcon("Save.png"),tr("Save"),this);
	saveFileAction->setShortcut(tr("Ctrl+S"));
	saveFileAction->setStatusTip(tr("Save File"));
	connect(saveFileAction, SIGNAL(triggered()), this, SLOT(SaveFile()));


	exitAction = new QAction(QIcon("Exit.png"),tr("Exit"), this);
	saveFileAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip(tr("Exit"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void QtCreate::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("File"));
	fileMenu->addAction(loadFileAction);
	fileMenu->addAction(saveFileAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
}

void QtCreate::createToolBars()
{
	fileTool = addToolBar("�ļ�");
	fileTool->addAction(loadFileAction);
	fileTool->addAction(saveFileAction);
	fileTool->addAction(exitAction);
}

void QtCreate::createGantGraph()
{
	CountMouseClicked = 0;
	LastY = -1;

	//resize(400, 550);

	//ShowText = new QLabel("Simple Gantt Chart", this);
	//ShowText->setAlignment(Qt::AlignCenter);
	LoadActionFlag = false;
	this->setUpdatesEnabled(true);

}

void QtCreate::changeTextEditStyle()
{
	ui.ConsoleTextEdit->setAutoFillBackground(true);
	QPalette palette;
	//����QTextEdit������ɫ  
	palette.setBrush(QPalette::Active, QPalette::Text, QBrush(Qt::white));
	//����QTextEdit����ɫ  
	palette.setBrush(QPalette::Active, QPalette::Base, QBrush(Qt::black));
	ui.ConsoleTextEdit->setPalette(palette);
	ui.ConsoleTextEdit->setReadOnly(true);
	QPalette pal;
	pal.setBrush(QPalette::Base, QBrush(QColor(255, 0, 0, 0)));
	ui.ResultTextEdit->setPalette(pal);
	ui.ResultTextEdit->setReadOnly(true);
}

void QtCreate::ReadFile()         // ���ļ�
{
	#pragma region READOUTPUT
	QFile fRead("Output.txt");	//��ready̬�����ݶ���
	if (fRead.open(QIODevice::ReadOnly | QIODevice::Text))  // ���ļ��Ƿ�ɹ�
	{
		QTextStream  tRead(&fRead);
		ActionAttribute *Temp;					//Initialize
		while (!tRead.atEnd())
		{
			Temp = new ActionAttribute;
			Temp->TaskId = tRead.readLine();          // Task ������ ���ļ�����
			Temp->TaskName = tRead.readLine();
			Temp->BeginTime = tRead.readLine().toDouble();  // #������ʼʱ��
			Temp->LastTime = tRead.readLine().toDouble() - Temp->BeginTime;  // #�����ĳ���ʱ��

			label = new QLabel(this);                     // ��ǩ
			label->setText(Temp->TaskName);

			ShowTime = new QPushButton(this);     // ��ʾʱ�����ƿؼ�

			Temp->btn = ShowTime;
			Temp->label = label;

			Action.push_back(Temp);
		}
	}
	else
	{
		QMessageBox::warning(NULL, "Open File Fail!",
			tr("Open File %1 Fail! \n%2").arg(fRead.fileName()).arg(fRead.errorString()));
	}
	#pragma region Partition Label Init

	QLabel *lab0 = new QLabel(this);
	lab0->setParent(ui.GantScrollContent);
	lab0->setText("EmptyPartition");
	lab0->setGeometry(5, 15, 150, 20);	//��һ��label
	lab0->show();

	QLabel *lab1 = new QLabel(this);
	lab1->setParent(ui.GantScrollContent);
	lab1->setText("ACARSMaintInterfaceApp");
	lab1->setGeometry(5, 35, 150, 20);	//�ڶ���label
	lab1->show();

	QLabel *lab2 = new QLabel(this);
	lab2->setParent(ui.GantScrollContent);
	lab2->setText("APP_AIRPORTSURFACEMAP");
	lab2->setGeometry(5, 55, 150, 20);	//������label
	lab2->show();

	QLabel *lab3 = new QLabel(this);
	lab3->setParent(ui.GantScrollContent);
	lab3->setText("APP_FMS_CORE");
	lab3->setGeometry(5, 75, 150, 20);	//���ĸ�label
	lab3->show();

	QLabel *lab4 = new QLabel(this);
	lab4->setParent(ui.GantScrollContent);
	lab4->setText("APP_FMS_NAV");
	lab4->setGeometry(5, 95, 150, 20);	//�����label
	lab4->show();

	QLabel *lab5 = new QLabel(this);
	lab5->setParent(ui.GantScrollContent);
	lab5->setText("APP_HEALTH_MANAGER");
	lab5->setGeometry(5, 155, 150, 20);	//������label
	lab5->show();

	QLabel *lab6 = new QLabel(this);
	lab6->setParent(ui.GantScrollContent);
	lab6->setText("OMSCockpitDisplayApp");
	lab6->setGeometry(5, 195, 150, 20);	//���߸�label
	lab6->show();

	QLabel *lab7 = new QLabel(this);
	lab7->setParent(ui.GantScrollContent);
	lab7->setText("VIRTUALCONTROLAPP");
	lab7->setGeometry(5, 215, 150, 20);	//�ڰ˸�label
	lab7->show();

	#pragma endregion

	fRead.close();
	#pragma endregion

	#pragma region READOUTPUTREA
	QFile fReadRea("OutputReady.txt");	//Ready̬�������ɴ˶���
	if (fReadRea.open(QIODevice::ReadOnly | QIODevice::Text))  // ���ļ��Ƿ�ɹ�
	{
		QTextStream  tReadRea(&fReadRea);
		ActionAttribute *Temp;					//Initialize

		while (!tReadRea.atEnd())
		{
			Temp = new ActionAttribute;
			Temp->TaskId = tReadRea.readLine();          // #������
			Temp->TaskName = tReadRea.readLine();
			Temp->BeginTime = tReadRea.readLine().toDouble();// #������ʼʱ��
			Temp->LastTime = tReadRea.readLine().toDouble() - Temp->BeginTime;  // #�����ĳ���ʱ��

			label = new QLabel(this);                     // ��ǩ
			label->setText(Temp->TaskName);

			ShowTime = new QPushButton(this);     // ��ʾʱ�����ƿؼ�

			Temp->btn = ShowTime;
			Temp->label = label;

			Action.push_back(Temp);
		}
	}
	else
	{
		QMessageBox::warning(NULL, "Open File Fail!",
			tr("Open File %1 Fail! \n%2").arg(fReadRea.fileName()).arg(fReadRea.errorString()));
	}

	fReadRea.close();
	#pragma endregion
}

void QtCreate::paintEvent(QPaintEvent *) // ���档
{
	eventFilter(ui.GantScrollContent, new QEvent(QEvent::Paint));
}


bool QtCreate::eventFilter(QObject* wateched, QEvent* event)
{
	if (wateched == ui.GantScrollContent && event->type() == QEvent::Paint)
	{
		#pragma region PaintEvent
		/*QPainter painter;
		painter.begin(ui.GantScrollContent);
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
		painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
		painter.drawEllipse(50, 50, 100, 100);
		painter.end();*/

		
		int  i = 0;
		int  WindowWidth = width();
		int  MenuWidth = WindowWidth / 15;

		if (Action.size() > 0)
		{
			
			BeginTime = Action[0]->BeginTime;
			EndTime = Action[0]->BeginTime + Action[0]->LastTime;
			//�ҵ���ֹʱ������ֵ��ȷ������������ֵ
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
			EndTime += 5;

			int  TimeElapedSize = TimeElaped.size() - 1;
			int span = 20;
			int  StartX = 270;
			//StartX = 15;
			int  EndX = (WindowWidth >> 6) * 55;
			EndX = 3500;
			int  EndSourceX = (WindowWidth >> 3) * 5;
			EndSourceX = 3500;
			int  XActionLength = (EndX - StartX) / (EndTime - BeginTime);	//��λʱ���X����
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
			QPainter  pa;
			pa.begin(ui.GantScrollContent);


			//pa.drawText(StartX, 375, 80, 325, Qt::AlignLeft, QString::number(BeginTime));	//����̶���������
			pa.drawText(StartX, 5, 80, 325, Qt::AlignLeft, QString::number(BeginTime));	//����̶���������

			for (i = 0; i <= SEGMENT; i++)
			{
				pa.drawLine(StartX + i*XLength, 20, StartX + (i + 1)*XLength, 20);	//X������
				pa.drawLine(StartX + (i + 1)*XLength, 20, StartX + (i + 1)*XLength, 17);
				pa.drawText(StartX + (i + 1)*XLength, 5, XLength, 15, Qt::AlignLeft,
					QString::number(BeginTime + (i + 1)*SegmentTime));
			}
			//pa.drawLine(StartX + i*XLength, 20, StartX + (i + 1)*XLength, 20);	//�ӳ���
			
			#pragma region INVALID CODE
			//pa.end();
			/*const int Htriangle[3][2] =
			{
			{ StartX + (i + 1)*XLength, 290 },
			{ StartX + (i + 1)*XLength, 286 },
			{ StartX + (i + 1)*XLength + 2, 288 }
			};*/
			/*QPen thickPen(palette().foreground(), 1.5);
			QPen thinPen(palette().foreground(), 0.5);
			pa.setPen(thinPen);
			pa.setBrush(palette().foreground());*/
			//pa.drawPolygon(QPolygon(3, &Htriangle[0][0]));//����һ��С�ĵ�������
			#pragma endregion

			std::map<int, int> m;
			std::map<int, int>::iterator iter;
			int origin = 0;

			for (i = 0; i < Action.size(); i++)            // ����
			{
				//Action[i]->btn->parentWidget(ui.GantScrollContent);
				bool ok;
				iter = m.find((Action[i]->TaskId).toInt(&ok, 10));
				Action[i]->label->setParent(ui.GantScrollContent);
				Action[i]->btn->setParent(ui.GantScrollContent);
				if (iter == m.end())
				{
					#pragma region NOTFIND
					//û���ҵ�
					m.insert(std::pair<int, int>((Action[i]->TaskId).toInt(&ok, 10), origin));

					Action[i]->label->setAlignment(Qt::AlignRight);
					Action[i]->label->show();             //  ����show��������Action������ʾ��
					Action[i]->btn->setFocusPolicy(Qt::NoFocus);

					switch (origin % 4)
					{
					case 0:
						Action[i]->btn->setStyleSheet("background-color:rgb(255,225,146); border-style: solid; border-width: 1px; border-color: grey;");
						break;
					case 1:
						Action[i]->btn->setStyleSheet("background-color:rgb(114,205,224);  border-style: solid; border-width: 1px; border-color: grey;");
						break;
					case 2:
						Action[i]->btn->setStyleSheet("background-color:rgb(127,159,210);  border-style: solid; border-width: 1px; border-color: grey;");
						break;
					case 3:
						Action[i]->btn->setStyleSheet("background-color:rgb(244,152,177);  border-style: solid; border-width: 1px; border-color: grey;");
						break;
					}

					if ((Action[i]->LastTime - 0.4 < 0.001) && (Action[i]->LastTime - 0.4 > -0.001))
					{
						Action[i]->btn->setStyleSheet("background-color:rgb(0,0,0);  border-style: solid; border-width: 1px; border-color: black;");
					}
					DrawGantPartition();
					//��������е�ͼʾ
					if (origin != 0)
					{
						Action[i]->label->setGeometry(5, 20 + origin * span, StartX - 10, 20);	//�����label
					}
					else
					{
						Action[0]->label->setGeometry(5, 20, StartX - 10, 20);	//��һ��label
					}
					
					//�����β���
					if (CountTime < Action[i]->BeginTime + Action[i]->LastTime)	//��������ʱ�仭����
					{
						Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 20 + origin * span,
							XActionLength*(CountTime - Action[i]->BeginTime), span);

					}
					else
					{
						Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 20 + origin * span,	//���տ����ʱ�䲹�Ͼ���
							XActionLength*Action[i]->LastTime, span);
					}
					Action[i]->btn->show();   // ����show��������Action������ʾ��
					
					
					origin++;
					#pragma endregion
				}
				else
				{
					#pragma region FIND
					//�ҵ���
					switch (iter->second % 4)
					{
					case 0:
						Action[i]->btn->setStyleSheet("background-color:rgb(255,225,146); border-style: solid; border-width: 1px; border-color: grey;");
						break;
					case 1:
						Action[i]->btn->setStyleSheet("background-color:rgb(114,205,224);  border-style: solid; border-width: 1px; border-color: grey;");
						break;
					case 2:
						Action[i]->btn->setStyleSheet("background-color:rgb(127,159,210);  border-style: solid; border-width: 1px; border-color: grey;");
						break;
					case 3:
						Action[i]->btn->setStyleSheet("background-color:rgb(244,152,177);  border-style: solid; border-width: 1px; border-color: grey;");
						break;
					}
					if ((Action[i]->LastTime - 0.4 < 0.001) && (Action[i]->LastTime - 0.4 > -0.001))
					{
						Action[i]->btn->setStyleSheet("background-color:rgb(0,0,0);  border-style: solid; border-width: 1px; border-color: black;");
					}

					if (CountTime < Action[i]->BeginTime + Action[i]->LastTime)	//��������ʱ�仭����
					{
						Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 20 + iter->second * span,
							XActionLength*(CountTime - Action[i]->BeginTime), span);

					}
					else
					{
						Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 20 + iter->second * span,	//���տ����ʱ�䲹�Ͼ���
							XActionLength*Action[i]->LastTime, span);
					}
					Action[i]->btn->show();   // ����show��������Action������ʾ��
					#pragma endregion
				}


				#pragma region INVALID CODE
				//Action[i]->label->setAlignment(Qt::AlignRight);
				//Action[i]->label->show();             //  ����show��������Action������ʾ��
				//Action[i]->btn->setFocusPolicy(Qt::NoFocus);

				//switch (i % 3)
				//{
				//case 0:
				//	//Action[i]->label->setStyleSheet("color:red");
				//	Action[i]->btn->setStyleSheet("background-color:red");
				//	break;

				//case 1:
				//	//Action[i]->label->setStyleSheet("color:green");
				//	Action[i]->btn->setStyleSheet("background-color:green");
				//	break;

				//case 2:
				//	//Action[i]->label->setStyleSheet("color:blue");
				//	Action[i]->btn->setStyleSheet("background-color:blue");
				//	break;
				//}

				//���ƾ��εĴ�С����
				//if (i != 0)
				//{
				//	Action[i]->label->setGeometry(0, 400 + i * 30, StartX - 10, 330);	//�����label
				//}
				//else
				//{
				//	Action[0]->label->setGeometry(0, 400, StartX - 6, 330);	//��һ��label
				//}

				//if (CountTime < Action[i]->BeginTime + Action[i]->LastTime)	//��������ʱ�仭����
				//{
				//	Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 400 + i * 30,
				//		XActionLength*(CountTime - Action[i]->BeginTime), 29);
				//	
				//}
				//else
				//{
				//	Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 400 + i * 30,	//���տ����ʱ�䲹�Ͼ���
				//		XActionLength*Action[i]->LastTime, 29);
				//}
				//Action[i]->btn->show();   // ����show��������Action������ʾ��
				#pragma endregion 
			}
			for (int i = 0; i < origin; i++)
			{
				//pa.begin(ui.GantScrollContent);
				pa.drawLine(StartX, 18 + i * span, StartX, 18 + (i + 1) * span);	//Y�������
				pa.drawLine(StartX, 18 + (i + 1) * span, StartX - 3, 18 + (i + 1) * span);
			}
			//pa.drawLine(StartX, 288 + i * 30, StartX, 300 + i * 30);

			#pragma region PartitionTaskLine
			//PartitionTask�ֽ���

			//Partition0
			pa.drawLine(140, 20, 140, 32);
			pa.drawLine(140, 20, 140 + 3, 20);
			pa.drawLine(140, 32, 140 + 3, 32);

			//Partition1
			pa.drawLine(140, 40, 140, 52);
			pa.drawLine(140, 40, 140 + 3, 40);
			pa.drawLine(140, 52, 140 + 3, 52);

			//Partition2
			pa.drawLine(140, 60, 140, 72);
			pa.drawLine(140, 60, 140 + 3, 60);
			pa.drawLine(140, 72, 140 + 3, 72);

			//Partition3
			pa.drawLine(140, 80, 140, 92);
			pa.drawLine(140, 80, 140 + 3, 80);
			pa.drawLine(140, 92, 140 + 3, 92);

			//Partition4
			pa.drawLine(140, 100, 140, 152);
			pa.drawLine(140, 100, 140 + 3, 100);
			pa.drawLine(140, 152, 140 + 3, 152);

			//Partition5
			pa.drawLine(140, 160, 140, 192);
			pa.drawLine(140, 160, 140 + 3, 160);
			pa.drawLine(140, 192, 140 + 3, 192);

			//Partition6
			pa.drawLine(140, 200, 140, 212);
			pa.drawLine(140, 200, 140 + 3, 200);
			pa.drawLine(140, 212, 140 + 3, 212);

			//Partition7
			pa.drawLine(140, 220, 140, 252);
			pa.drawLine(140, 220, 140 + 3, 220);
			pa.drawLine(140, 252, 140 + 3, 252);
			#pragma endregion

			#pragma region INVALID CODE
			//const int Vtriangle[3][2] =
			//{
			//	{ StartX - 2, 100 + i * 30 },
			//	{ StartX + 2, 100 + i * 30 },
			//	{ StartX, 102 + i * 30 }
			//};

			//pa.drawPolygon(QPolygon(3, &Vtriangle[0][0]));//����һ��С�ĵ�������


			///////////// ������Դͼ ///////////////////////////////////////////////////////////////
			////    pa.drawRect(0,400,10+CountTime,20);
			//////////////////////////////////////////////////////////////////////////////////////

			//QList <Resource >  SourceArray;
			//Resource  TempSource;

			//int ActionIndex = 0, SourceIndex = 0;
			//// �Ȱ����в�ͬ����Դ������ SourceArray��. ���Ԥ�Ⱦ�֪��Ҫ���ĵ�������Դ���������ȥ��һ����

			//TempSource.SourceName = Action[0]->source[0]->SourceName;  //bug��ÿ��action����ķ���Դ�����action[0]���ķ���Դ����ֶδ���
			//TempSource.SourceNum = 0;

			//SourceArray.push_back(TempSource);

			//for (ActionIndex = 0; ActionIndex < Action.size(); ActionIndex++)
			//{
			//	for (SourceIndex = 0; SourceIndex < Action[ActionIndex]->source.size(); SourceIndex++)
			//	{
			//		bool IfInArray = false;
			//		for (int j = 0; j < SourceArray.size(); j++)
			//		{
			//			if (SourceArray[j].SourceName == Action[ActionIndex]->source[SourceIndex]->SourceName)
			//			{
			//				IfInArray = true;
			//				break;
			//			}
			//		}

			//		if (!IfInArray)
			//		{
			//			TempSource.SourceName = Action[ActionIndex]->source[SourceIndex]->SourceName;
			//			TempSource.SourceNum = 0;
			//			SourceArray.push_back(TempSource);
			//		}
			//	}
			//}

			//// ������ȥ��ʱ�䣬�ж�ĳ��action�Ƿ�ִ�����ˡ��ǣ���Ѻķѵ���Դ����SourceArray�С�
			//QList <int> RecordEndAction;
			//for (ActionIndex = 0; ActionIndex < Action.size(); ActionIndex++)
			//{
			//	if (CountTime > Action[ActionIndex]->BeginTime + Action[ActionIndex]->LastTime)
			//	{
			//		// ���˵��Ѿ�ִ�����Action
			//		bool  ifEnd = false;
			//		for (int j = 0; j < RecordEndAction.size(); j++)
			//		{
			//			if (RecordEndAction[j] == ActionIndex)
			//			{
			//				ifEnd = true;
			//				break;
			//			}
			//		}

			//		if (ifEnd)             // ���Ϊ�棬���ñ�־Action����Դ�����Ѿ���¼���ˣ�ִ���¸�ѭ����
			//		{
			//			continue;
			//		}

			//		//  ��¼���ĵ���Դ��
			//		for (SourceIndex = 0; SourceIndex < Action[ActionIndex]->source.size(); SourceIndex++)
			//		{
			//			for (int k = 0; k < SourceArray.size(); k++)
			//			{
			//				if (SourceArray[k].SourceName == Action[ActionIndex]->source[SourceIndex]->SourceName)
			//				{
			//					SourceArray[k].SourceNum += Action[ActionIndex]->source[SourceIndex]->SourceNum;
			//					RecordEndAction.push_back(ActionIndex);
			//				}
			//			}
			//		}
			//	}
			//}

			////        ���Լ�����Դ��ͬ�ĸ�����
			////        pa.drawText(400,400,50,20,Qt::AlignCenter,QString::number(SourceArray.size(),10));

			/////// ͼ�λ� ���ĵ���Դ ��������Դ��num��Ϊ�ؼ���ʾ���ȵı�׼��     
			//int  XSourceLength = (EndSourceX - StartX) / MAXSOURCENUM;  // ��λnum����
			//int  XSegmentSourceLength = XSourceLength * SEGMENT;        // �γ���

			//int j = 0;         // index
			//for (j = 0; j < SEGMENT; j++)
			//{
			//	pa.drawLine(StartX + XSegmentSourceLength * j, 348 + (i + 1) * 30, StartX + XSegmentSourceLength * (j + 1), 148 + (i + 1) * 30);
			//	pa.drawLine(StartX + XSegmentSourceLength * (j + 1), 348 + (i + 1) * 30, StartX + XSegmentSourceLength * (j + 1), 146 + (i + 1) * 30);
			//	pa.drawText(StartX + XSegmentSourceLength * j, 326 + (i + 1) * 30, XSegmentSourceLength, 15, Qt::AlignLeft, QString::number(j*SEGMENT));
			//}
			//pa.drawText(StartX + XSegmentSourceLength * j, 326 + (i + 1) * 30, XSegmentSourceLength, 15, Qt::AlignLeft, QString::number(j*SEGMENT));

			//const int HSourceTriangle[3][2] =
			//{
			//	{ StartX + XSegmentSourceLength * j, 350 + (i + 1) * 30 },
			//	{ StartX + XSegmentSourceLength * j, 346 + (i + 1) * 30 },
			//	{ StartX + XSegmentSourceLength * j + 2, 348 + (i + 1) * 30 }
			//};
			//pa.drawPolygon(QPolygon(3, &HSourceTriangle[0][0]));//����һ��С�ĵ�������

			//for (j = 0; j < SourceArray.size(); j++)
			//{
			//	pa.drawLine(StartX, 348 + (i + 1) * 30 + j * 30, StartX, 148 + (i + 1) * 30 + (j + 1) * 30);
			//	pa.drawLine(StartX, 348 + (i + 1) * 30 + (j + 1) * 30, StartX - 3, 148 + (i + 1) * 30 + (j + 1) * 30);
			//}
			//pa.drawLine(StartX, 348 + (i + 1) * 30 + j * 30, StartX, 160 + (i + 1) * 30 + j * 30);

			//const int VSourceTriangle[3][2] =
			//{
			//	{ StartX - 2, 360 + (i + 1) * 30 + j * 30 },
			//	{ StartX + 2, 360 + (i + 1) * 30 + j * 30 },
			//	{ StartX, 362 + (i + 1) * 30 + j * 30 }
			//};

			//pa.drawPolygon(QPolygon(3, &VSourceTriangle[0][0]));//����һ��С�ĵ�������

			/*for (j = 0; j < SourceArray.size(); j++)
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

			pa.drawRect(StartX, 48 + (i + 1) * 30 + j * 30, SourceArray[j].SourceNum* XSourceLength, 30);

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

			pa.drawText(0, 348 + (i + 1) * 30 + j * 30, StartX - 6, 30, Qt::AlignRight, SourceArray[j].SourceName);
			pa.setPen(Qt::blue);
			}*/
			#pragma endregion

			//����ʱ�䲿��
			pa.drawText(1110, 560, 120, 30, Qt::AlignLeft, "Current Time:");
			//timelabel->setParent(ui.GantScrollContent);
			timelabel->setGeometry(1210, 560, 120, 50);
			//timelabel->setFont(QFont("Times", 20, QFont::Bold));
			timelabel->show();
			//SetTimelabel->setParent(ui.GantScrollContent);
			SetTimelabel->setGeometry(1110, 580, 80, 25);           // ����ʱ�䱶��
			SetTimelabel->show();
			SetTimeEdit->setGeometry(1190, 580, 40, 25);	//�༭��
			SetTimeEdit->show();
			pa.drawText(1235, 585, 70, 15, Qt::AlignLeft, "s");
			//SetTimeBtn->setParent(ui.GantScrollContent);
			SetTimeBtn->setGeometry(1160, 610, 70, 25);
			SetTimeBtn->show();
			pa.end();
		}
		#pragma endregion
		return true;
	}


	//ShowText->setGeometry(0, 20, width(), 32);   // Simple Gantt Chart Demo
	//FileOpenBtn->setGeometry(0, 0, MenuWidth, 20);
	//SaveBtn->setGeometry(MenuWidth << 2, 0, MenuWidth, 20);
}

void QtCreate::DrawGantPartition()
{
		
}

void QtCreate::SaveAction()
{
	QString FileName("ScheduleResult.txt");
	QFile   fWrite(FileName);
	if (fWrite.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))  // �ļ��Ƿ�ɹ�
	{
		QTextStream  tWrite(&fWrite);

		int len = Action.size();

		//tWrite << "<begin_plan>" << "\n";             // <begin_plan>
		tWrite << "<begin_num_actions>\n";          // <begin_num_actions>
		tWrite << QString::number(len, 10) << endl;   // ��¼Action�ĸ�����
		tWrite << "<end_num_actions>" << endl;        // <end_num_actions>

		for (int i = 0; i < len; i++)
		{
			tWrite << "<begin_action>" << endl;
			tWrite << Action[i]->TaskId << endl;
			tWrite << QString::number(Action[i]->BeginTime) << endl;
			tWrite << QString::number(Action[i]->LastTime) << endl;
			tWrite << "<end_action>" << endl;
		}
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

void QtCreate::LoadAction()
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
		}

		LoadActionFlag = true;
	}
	this->setFocus();
	this->update();
}

void QtCreate::SetTimes()
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

void QtCreate::LoadFile()
{
	#pragma region INVALID CODE
	//QFile file("SchdulePartitionData.xml");
	//if (!file.open(QFile::ReadOnly | QFile::Text))
	//{
	//	ui.DataTextEdit->append(tr("Xml open fail"));
	//}
	//QDomDocument doc;

	//QString errStr;
	//int errLine, errCol;
	//if (!doc.setContent(&file, false, &errStr, &errLine, &errCol))
	//{
	//	ui.DataTextEdit->append(tr("Unable to load content. ") + errStr);
	//}
	//file.close();

	//QDomElement root = doc.documentElement();
	//ui.DataTextEdit->append(root.nodeName());

	//QDomElement partition = root.firstChildElement();

	//QDomElement par = partition.firstChildElement();
	//while (!par.isNull())
	//{
	//	//ui.DataTextEdit->append(par.nodeName());
	//	//ui.DataTextEdit->append(par.text());
	//	par = par.nextSiblingElement();
	//}
	////�޸ĵ��ȳ���
	//ui.ConsoleTextEdit->append("Task Data Load Complete");
	///*QMessageBox msg;
	//msg.setText("Data Load Complete");
	//msg.exec();*/
	#pragma endregion
}

void QtCreate::SaveFile()
{
	SaveAction();
}

QtCreate::~QtCreate()
{

}


