#include "qtcreate.h"
#include "ui_qtcreate.h"
#include <qmessagebox.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qtextstream.h>
#include <qdom.h>
#include <qmultimedia.h>
#include <qmediacontrol.h>
#include <qmediaplayer.h>
#include <qvideowidget.h>
#include <windows.h>


void QtCreate::EDFBtn_Click()
{
	initial();
	ui.DataTextEdit->clear();
	ui.ResultTextEdit->clear();
	ui.ConsoleTextEdit->clear();
	ClearOutputFile();
	ClearGanttGraph();
	
	int totalpartition = LoadPartitionFile();
	int totaltask = LoadTaskFile();
	OutputtoGant(totaltask);

	ScheduleStrategy = 1;
	PartitionScheduler(totalpartition - 1);
	for (int i = 1; i < totaltask; i++)
	{
		ui.ResultTextEdit->append(QString("Task Id %1, Respond Time %2 (timeslice)").arg(t[i].id).arg(TaskWT[i]));
	}
	ui.ResultTextEdit->append(QString("\nTotal Schedule Time: 52"));
	ui.ResultTextEdit->repaint();
	LoadAction();
	//eventFilter(ui.GantScrollContent, new QEvent(QEvent::Paint));
	
}

void QtCreate::RMSBtn_Click()
{
	initial();
	ui.DataTextEdit->clear();
	ui.ResultTextEdit->clear();
	ui.ConsoleTextEdit->clear();
	ClearOutputFile();
	ClearGanttGraph();

	int totalpartition = LoadPartitionFile();
	int totaltask = LoadTaskFile();
	OutputtoGant(totaltask);

	ScheduleStrategy = 2;
	PartitionScheduler(totalpartition - 1);
	for (int i = 1; i < totaltask; i++)
	{
		ui.ResultTextEdit->append(QString("Task Id %1, Response Time %2 (timeslice)").arg(t[i].id).arg(TaskWT[i]));
	}
	ui.ResultTextEdit->append(QString("\nTotal Schedule Time: 52"));
	ui.ResultTextEdit->repaint();
	LoadAction();
}

void QtCreate::DMSBtn_Click()
{
	initial();
	ui.DataTextEdit->clear();
	ui.ResultTextEdit->clear();
	ui.ConsoleTextEdit->clear();
	ClearOutputFile();
	ClearGanttGraph();

	int totalpartition = LoadPartitionFile();
	int totaltask = LoadTaskFile();
	OutputtoGant(totaltask);

	ScheduleStrategy = 3;
	PartitionScheduler(totalpartition - 1);
	for (int i = 1; i < totaltask; i++)
	{
		ui.ResultTextEdit->append(QString("Task Id %1, Response Time %2 (timeslice)").arg(t[i].id).arg(TaskWT[i]));
	}
	ui.ResultTextEdit->append(QString("\nTotal Schedule Time: 52"));
	ui.ResultTextEdit->repaint();
	LoadAction();
}

void QtCreate::LSTBtn_Click()
{
	initial();
	ui.DataTextEdit->clear();
	ui.ResultTextEdit->clear();
	ui.ConsoleTextEdit->clear();
	ClearOutputFile();
	ClearGanttGraph();

	int totalpartition = LoadPartitionFile();
	int totaltask = LoadTaskFile();
	OutputtoGant(totaltask);

	ScheduleStrategy = 4;
	PartitionScheduler(totalpartition - 1);
	for (int i = 1; i < totaltask; i++)
	{
		ui.ResultTextEdit->append(QString("Task Id %1, Response Time %2 (timeslice)").arg(t[i].id).arg(TaskWT[i]));
	}
	ui.ResultTextEdit->append(QString("\nTotal Schedule Time: 52"));
	ui.ResultTextEdit->repaint();
	LoadAction();
}

void QtCreate::MFPSBtn_Click()
{
	initial();
	ui.DataTextEdit->clear();
	ui.ResultTextEdit->clear();
	ui.ConsoleTextEdit->clear();
	ClearOutputFile();
	ClearGanttGraph();

	int totalpartition = MFPSLoadPartitionFile();
	int totaltask = MFPSLoadTaskFile();
	ScheduleStrategy = 1;
	MFPSPartitionScheduler(totalpartition - 1);
	for (int i = 1; i < totaltask; i++)
	{
		ui.ResultTextEdit->append(QString("Task Id %1, Response Time %2 (timeslice)").arg(t[i].id).arg(TaskWT[i]));
	}
	ui.ResultTextEdit->append(QString("\nTotal Schedule Time: %1").arg(FinishTime));
	ui.ResultTextEdit->repaint();
	LoadAction();
}

