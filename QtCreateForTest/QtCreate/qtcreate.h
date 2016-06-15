#ifndef QTCREATE_H
#define QTCREATE_H

#include <QtWidgets/QMainWindow>
#include "ui_qtcreate.h"
#include "showWidget.h"
#include "qtcreate.h"
#include "ActionStruct.h"
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
#include <qtimer.h>
#include <qmouseeventtransition.h>
#include <QMouseEvent>
#include <stdlib.h>
#include <string.h>


#define MAXPARTITION 10
#define MAXTASK 20
#define MAXTIMESLICE 600

////////////////////////////// ����������
#define SEGMENT  60          // ʱ���Ϊ 10��
#define MAXSOURCENUM  100    // ������Դ�������


class QtCreate : public QMainWindow
{
	Q_OBJECT

public:
	QtCreate(QWidget *parent = 0);
	~QtCreate();

	Ui::QtCreateClass ui;

	void createActions();
	void createMenus();
	void createToolBars();
	void createGantGraph();
	void changeTextEditStyle();

	enum status { Suspend = 1, Ready, Running, Finish, Error };

	struct partition
	{
		int id;
		int period;
		int duration;
		int offset;
		int times;
		int timescount;
		std::string name;
		std::string description;
		int priority;
		int intensiveperiod;
		bool initonce;
	};

	struct task
	{
		int id;
		int exectime;
		int period;
		int deadline;
		int offset;
		int execclock;
		int respclock;
		status stat;
		int partitionid;
		std::string name;
		//partition part;
	};

	struct partition p[MAXPARTITION];
	struct task t[MAXTASK];
	int PartitionCycle[MAXPARTITION];
	int TaskCycle[MAXTASK];
	int TaskWT[MAXTASK];
	int PartitionTask;
	int ScheduleStrategy;
	QList  <ActionAttribute *>   Action;
	bool   LoadActionFlag;
	int FinishTime;
	int slice;	//��¼�ϴ�Partition��ɵ�ʱ��

	//QPainter *paint;
	//QPainter  pa;
	QTextCodec *codec;
	bool CheckPrioritySus(int i);
	bool CheckPriorityReaEDF(int i, int partition, int tasknum);
	bool CheckPriorityReaRMS(int i, int partition, int tasknum);
	bool CheckPriorityReaDMS(int i, int partition, int tasknum);
	bool CheckPriorityReaLST(int i, int partition, int tasknum);
	bool CheckRun(int i, int tasknum);
	bool CheckPriorityPartition(int i, int partition, int timeslice);
	bool StatusUpdate(int timeslice, int tasknum, int partition);
	void TaskScheduler(int timeslice, int tasknum, int partition);
	void CheckTaskReady(int partition, int timeslice);
	void StopRunningTask(int i, int timeslice, int tasknum);
	//����
	void PartitionScheduler(int partitionnum);
	void OutputtoGant(int tasknum);
	void initial();
	//MFPS
	void MFPSPartitionScheduler(int partitionnum);
	int MFPSTaskScheduler(int timeslice, int tasknum, int partition);
	bool MFPSStatusUpdate(int timeslice, int tasknum, int partition);

	void BroadcastVideo();

	private slots:

	void EDFBtn_Click();
	void RMSBtn_Click();
	void DMSBtn_Click();
	void LSTBtn_Click();
	void MFPSBtn_Click();
	void Departure_Click();
	void Preflight_Click();
	void Cruise_Click();
	void Arrival_Click();
	void ClearOutputFile();
	void ClearGanttGraph();
	void DrawGantPartition();

	protected slots:

	void LoadFile();
	void SaveFile();

	//���ȳ���
	int LoadPartitionFile();
	int LoadTaskFile();
	int MFPSLoadPartitionFile();
	int MFPSLoadTaskFile();

private:
	
	QString fileName;

	QMenu *fileMenu;

	QAction *loadFileAction;
	QAction *saveFileAction;
	QAction *exitAction;

	QToolBar *fileTool;

	//From Solving.h
	int           CountTime;
	int           ActionNum;
	int           BeginTime;
	int           EndTime;
	int           Times;

	int           CountMouseClicked;
	int           LastY;
	int           LastX;

	/*QPushButton   *FileOpenBtn;
	QPushButton   *SaveBtn;*/

	QList <Resource >  SourceArray;

	QLabel        *timelabel;
	QLabel        *SetTimelabel;
	QLineEdit     *SetTimeEdit;
	QPushButton   *SetTimeBtn;
	QTime         ChangingTime;
	QLabel        *label;
	//QLabel        *ShowText;
	QPushButton   *ShowTime;
	QList          <ElapsedTimeStruct *> TimeElaped;
	QLabel  *lab0;
	QLabel	*lab1;
	QLabel	*lab2;
	QLabel	*lab3;
	QLabel	*lab4;
	QLabel	*lab5;
	QLabel	*lab6;
	QLabel	*lab7;

private:
	void  ReadFile();         // ��ȡ÷�����滮�õ��ļ���
	void  paintEvent(QPaintEvent *);
	bool  eventFilter(QObject*, QEvent*);

	private slots:

	void  LoadAction();
	void  SetTimes();                //����ʱ�䱶�ʡ�
	void  SaveAction();              // �����޸ĺ���ļ�����Ϊ���滮�ļ�������÷������֤�ý��Ƿ����

};

#endif // QTCREATE_H
