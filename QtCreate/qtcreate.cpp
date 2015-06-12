
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
	fileTool = addToolBar("文件");
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
	//设置QTextEdit文字颜色  
	palette.setBrush(QPalette::Active, QPalette::Text, QBrush(Qt::white));
	//设置QTextEdit背景色  
	palette.setBrush(QPalette::Active, QPalette::Base, QBrush(Qt::black));
	ui.ConsoleTextEdit->setPalette(palette);
	ui.ConsoleTextEdit->setReadOnly(true);
	QPalette pal;
	pal.setBrush(QPalette::Base, QBrush(QColor(255, 0, 0, 0)));
	ui.ResultTextEdit->setPalette(pal);
	ui.ResultTextEdit->setReadOnly(true);
}

void QtCreate::ReadFile()         // 读文件
{
	#pragma region READOUTPUT
	QFile fRead("Output.txt");
	if (fRead.open(QIODevice::ReadOnly | QIODevice::Text))  // 读文件是否成功
	{
		QTextStream  tRead(&fRead);
		ActionAttribute *Temp;					//Initialize

		while (!tRead.atEnd())
		{
			Temp = new ActionAttribute;
			Temp->TaskName = tRead.readLine();          // #动作名
			Temp->BeginTime = tRead.readLine().toDouble();  // #动作开始时刻
			Temp->LastTime = tRead.readLine().toDouble() - Temp->BeginTime;  // #动作的持续时长

			label = new QLabel(this);                     // 标签
			label->setText(Temp->TaskName);

			ShowTime = new QPushButton(this);     // 显示时间推移控件

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

	fRead.close();
	#pragma endregion

	#pragma region READOUTPUTREA
	QFile fReadRea("OutputReady.txt");
	if (fReadRea.open(QIODevice::ReadOnly | QIODevice::Text))  // 读文件是否成功
	{
		QTextStream  tReadRea(&fReadRea);
		ActionAttribute *Temp;					//Initialize

		while (!tReadRea.atEnd())
		{
			Temp = new ActionAttribute;
			Temp->TaskName = tReadRea.readLine();          // #动作名
			Temp->BeginTime = tReadRea.readLine().toDouble();// #动作开始时刻
			Temp->LastTime = tReadRea.readLine().toDouble() - Temp->BeginTime;  // #动作的持续时长

			label = new QLabel(this);                     // 标签
			label->setText(Temp->TaskName);

			ShowTime = new QPushButton(this);     // 显示时间推移控件

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

void QtCreate::paintEvent(QPaintEvent *) // 界面。
{
	int  i = 0;
	int  WindowWidth = width();
	int  MenuWidth = WindowWidth / 15;

	if (Action.size() > 0)
	{
		BeginTime = Action[0]->BeginTime;
		EndTime = Action[0]->BeginTime + Action[0]->LastTime;
		//找到起止时间的最大值，确定坐标轴坐标值
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
		int  StartX = WindowWidth >> 3;
		StartX = 220;
		int  EndX = (WindowWidth >> 6) * 55;
		EndX = 680;
		int  EndSourceX = (WindowWidth >> 3) * 5;
		EndSourceX = 680;
		int  XActionLength = (EndX - StartX) / (EndTime - BeginTime);	//单位时间的X距离
		int  SegmentTime = (EndTime - BeginTime) / SEGMENT;
		int  XLength = SegmentTime * XActionLength;

		//  设置时间精度
		CountTime = 0;
		if (TimeElaped.isEmpty())   // 调整时间倍率后，逝去时间的记录方法。T = t1*last1 + t2*last2...
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

		// 图形化  坐标轴和时态Action图
		QPainter  pa(this);
		//setStyleSheet("color:blue");
		//setFont(QFont("Times", 12, QFont::Bold));

		pa.drawText(StartX, 375, 80, 325, Qt::AlignLeft, QString::number(BeginTime));	//坐标刻度数字坐标

		for (i = 0; i <= SEGMENT; i++)
		{
			pa.drawLine(StartX + i*XLength, 400, StartX + (i + 1)*XLength, 400);	//X轴坐标
			pa.drawLine(StartX + (i + 1)*XLength, 400, StartX + (i + 1)*XLength, 397);
			pa.drawText(StartX + (i + 1)*XLength, 375, XLength, 15, Qt::AlignLeft,
				QString::number(BeginTime + (i + 1)*SegmentTime));
		}
		pa.drawLine(StartX + i*XLength, 400, StartX + (i + 1)*XLength, 400);

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
		//pa.drawPolygon(QPolygon(3, &Htriangle[0][0]));//绘制一个小的倒三角形

		std::map<int, int> m;
		std::map<int, int>::iterator iter;
		int origin = 0;

		for (i = 0; i < Action.size(); i++)            // 绘制
		{
			//pa.drawLine(StartX, 398 + i * 19, StartX, 398 + (i + 1) * 19);	//Y轴的坐标
			//pa.drawLine(StartX, 398 + (i + 1) * 19, StartX - 3, 398 + (i + 1) * 19);

			bool ok;
			iter = m.find((Action[i]->TaskName).toInt(&ok, 10));
			if (iter == m.end())
			{
				#pragma region NOTFIND
				//没有找到
				m.insert(std::pair<int, int>((Action[i]->TaskName).toInt(&ok,10), origin));

				Action[i]->label->setAlignment(Qt::AlignRight);
				Action[i]->label->show();             //  不加show，新增的Action不能显示。
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
				if (origin != 0)
				{
					Action[i]->label->setGeometry(0, 400 + origin * 23, StartX - 10, 330);	//下面的label
				}
				else
				{
					Action[0]->label->setGeometry(0, 400, StartX - 6, 330);	//第一个label
				}
				//画矩形部分
				if (CountTime < Action[i]->BeginTime + Action[i]->LastTime)	//按照正常时间画矩形
				{
					Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 400 + origin * 23,
						XActionLength*(CountTime - Action[i]->BeginTime), 23);

				}
				else
				{
					Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 400 + origin * 23,	//按照快进的时间补上矩形
						XActionLength*Action[i]->LastTime, 23);
				}
				Action[i]->btn->show();   // 不加show，新增的Action不能显示。

				origin++;
				#pragma endregion
			}
			else
			{
				#pragma region FIND
				//找到了
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

				if (CountTime < Action[i]->BeginTime + Action[i]->LastTime)	//按照正常时间画矩形
				{
					Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 400 + iter->second * 23,
						XActionLength*(CountTime - Action[i]->BeginTime), 23);

				}
				else
				{
					Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 400 + iter->second * 23,	//按照快进的时间补上矩形
						XActionLength*Action[i]->LastTime, 23);
				}
				Action[i]->btn->show();   // 不加show，新增的Action不能显示。
				#pragma endregion
			}
			
			
			#pragma region INVALID
			//Action[i]->label->setAlignment(Qt::AlignRight);
			//Action[i]->label->show();             //  不加show，新增的Action不能显示。
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

			//控制矩形的大小部分
			//if (i != 0)
			//{
			//	Action[i]->label->setGeometry(0, 400 + i * 30, StartX - 10, 330);	//下面的label
			//}
			//else
			//{
			//	Action[0]->label->setGeometry(0, 400, StartX - 6, 330);	//第一个label
			//}

			//if (CountTime < Action[i]->BeginTime + Action[i]->LastTime)	//按照正常时间画矩形
			//{
			//	Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 400 + i * 30,
			//		XActionLength*(CountTime - Action[i]->BeginTime), 29);
			//	
			//}
			//else
			//{
			//	Action[i]->btn->setGeometry(StartX + XActionLength*(Action[i]->BeginTime - BeginTime), 400 + i * 30,	//按照快进的时间补上矩形
			//		XActionLength*Action[i]->LastTime, 29);
			//}
			//Action[i]->btn->show();   // 不加show，新增的Action不能显示。
			#pragma endregion 
		}
		for (int i = 0; i < origin; i++)
		{
			pa.drawLine(StartX, 398 + i * 23, StartX, 398 + (i + 1) * 23);	//Y轴的坐标
			pa.drawLine(StartX, 398 + (i + 1) * 23, StartX - 3, 398 + (i + 1) * 23);
		}
		//pa.drawLine(StartX, 288 + i * 30, StartX, 300 + i * 30);

		#pragma region INVALID
		//const int Vtriangle[3][2] =
		//{
		//	{ StartX - 2, 100 + i * 30 },
		//	{ StartX + 2, 100 + i * 30 },
		//	{ StartX, 102 + i * 30 }
		//};

		//pa.drawPolygon(QPolygon(3, &Vtriangle[0][0]));//绘制一个小的倒三角形


		///////////// 绘制资源图 ///////////////////////////////////////////////////////////////
		////    pa.drawRect(0,400,10+CountTime,20);
		//////////////////////////////////////////////////////////////////////////////////////

		//QList <Resource >  SourceArray;
		//Resource  TempSource;

		//int ActionIndex = 0, SourceIndex = 0;
		//// 先把所有不同的资源都加入 SourceArray中. 如果预先就知道要消耗的所有资源，则可以略去这一步。

		//TempSource.SourceName = Action[0]->source[0]->SourceName;  //bug：每个action必须耗费资源。如果action[0]不耗费资源则出现段错误
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

		//// 根据逝去的时间，判断某个action是否执行完了。是，则把耗费的资源加入SourceArray中。
		//QList <int> RecordEndAction;
		//for (ActionIndex = 0; ActionIndex < Action.size(); ActionIndex++)
		//{
		//	if (CountTime > Action[ActionIndex]->BeginTime + Action[ActionIndex]->LastTime)
		//	{
		//		// 过滤掉已经执行完的Action
		//		bool  ifEnd = false;
		//		for (int j = 0; j < RecordEndAction.size(); j++)
		//		{
		//			if (RecordEndAction[j] == ActionIndex)
		//			{
		//				ifEnd = true;
		//				break;
		//			}
		//		}

		//		if (ifEnd)             // 如果为真，即该标志Action的资源消耗已经记录过了，执行下个循环。
		//		{
		//			continue;
		//		}

		//		//  记录消耗的资源。
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

		////        测试加入资源不同的个数。
		////        pa.drawText(400,400,50,20,Qt::AlignCenter,QString::number(SourceArray.size(),10));

		/////// 图形化 消耗的资源 以消耗资源的num作为控件显示长度的标准。     
		//int  XSourceLength = (EndSourceX - StartX) / MAXSOURCENUM;  // 单位num长度
		//int  XSegmentSourceLength = XSourceLength * SEGMENT;        // 段长度

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
		//pa.drawPolygon(QPolygon(3, &HSourceTriangle[0][0]));//绘制一个小的倒三角形

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

		//pa.drawPolygon(QPolygon(3, &VSourceTriangle[0][0]));//绘制一个小的倒三角形

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
		
		//设置时间部分
		pa.drawText(EndSourceX - 90, 560, 120, 30, Qt::AlignLeft, "Current Time:");
		timelabel->setGeometry(EndSourceX + 10, 560, 120, 50);
		//timelabel->setFont(QFont("Times", 20, QFont::Bold));
		timelabel->show();
		SetTimelabel->setGeometry(EndSourceX - 90, 580, 80, 25);           // 设置时间倍率
		SetTimelabel->show();
		SetTimeEdit->setGeometry(EndSourceX - 10, 580, 40, 25);	//编辑框
		SetTimeEdit->show();
		pa.drawText(EndSourceX + 35, 585, 70, 15, Qt::AlignLeft, "s");
		SetTimeBtn->setGeometry(EndSourceX - 40, 610, 70, 25);
		SetTimeBtn->show();
	}

	//ShowText->setGeometry(0, 20, width(), 32);   // Simple Gantt Chart Demo
	//FileOpenBtn->setGeometry(0, 0, MenuWidth, 20);
	//SaveBtn->setGeometry(MenuWidth << 2, 0, MenuWidth, 20);
/*	SaveBtn->show()*/;
}

void QtCreate::SaveAction()
{
	QString FileName("ScheduleResult.txt");
	QFile   fWrite(FileName);
	if (fWrite.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))  // 文件是否成功
	{
		QTextStream  tWrite(&fWrite);

		int len = Action.size();

		//tWrite << "<begin_plan>" << "\n";             // <begin_plan>
		tWrite << "<begin_num_actions>\n";          // <begin_num_actions>
		tWrite << QString::number(len, 10) << endl;   // 记录Action的个数。
		tWrite << "<end_num_actions>" << endl;        // <end_num_actions>

		for (int i = 0; i < len; i++)
		{
			tWrite << "<begin_action>" << endl;
			tWrite << Action[i]->TaskName << endl;
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
	ActionAttribute *temp;                   // 保存文件后释放Action分配的内存。
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
			ChangingTime.start();              // 计时开始。
			this->setFocus();                  // 设置主窗口为焦点。

			timelabel = new QLabel(this);            // 显示时间
			timelabel->setAlignment(Qt::AlignLeft);

			Times = 1;
			SetTimelabel = new QLabel("Set Times:", this);          // 设置时间倍率  1秒*倍率。
			SetTimeEdit = new QLineEdit("1", this);
			SetTimeEdit->setAlignment(Qt::AlignRight);
			SetTimeBtn = new QPushButton("&Set", this);
			connect(SetTimeBtn, SIGNAL(clicked()), this, SLOT(SetTimes()));  //加入时间
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
		if (Times != TempTimes)   // 如果设置的时间倍率与之前不一样
		{
			ElapsedTimeStruct *temp = new ElapsedTimeStruct;
			temp->ElapedTimes = Times;          // 倍率

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
	////修改调度程序
	//ui.ConsoleTextEdit->append("Task Data Load Complete");
	///*QMessageBox msg;
	//msg.setText("Data Load Complete");
	//msg.exec();*/
}

void QtCreate::SaveFile()
{
	SaveAction();
}

QtCreate::~QtCreate()
{

}


