#include "qtcreate.h"
#include "ui_qtcreate.h"
#include <qmessagebox.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qtextstream.h>
#include <qdom.h>
#include <stdio.h>
#include <windows.h>
#include <qpainter.h>

//Scheduling Algorithm start here.

int QtCreate::LoadPartitionFile()
{
	QMessageBox msg;
	//Load Partition Data
	QFile file("SchdulePartitionData.xml");
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		ui.ConsoleTextEdit->append(tr("Partition File Xml open fail"));
		//msg.setText("Xml open fail");
		//msg.exec();
	}
	QDomDocument doc;

	QString errStr;
	int errLine, errCol;
	if (!doc.setContent(&file, false, &errStr, &errLine, &errCol))
	{
		ui.ConsoleTextEdit->append(tr("Unable to load content. ") + errStr);
		/*msg.setText("Unable to load content. ");
		msg.exec();*/
	}
	file.close();

	QDomElement root = doc.documentElement();
	//ui.textEdit->append(root.nodeName());

	QDomElement partition = root.firstChildElement();
	int i = 1;
	bool ok;

	ui.ConsoleTextEdit->append(tr("Partition Data Load Complete"));
	/*msg.setText("Partition Data Load Complete");
	msg.exec();*/

	while (!partition.isNull())
	{
		QDomElement par = partition.firstChildElement();
		while (!par.isNull())
		{
			if (par.nodeName() == "PartitionID")
			{
				p[i].id = par.text().toInt(&ok, 10);
				ui.DataTextEdit->append(QString("\nPartition ID: %1").arg(par.text()));
			}
			else if (par.nodeName() == "PartitionName")
			{
				p[i].name = par.text().toStdString();
				ui.DataTextEdit->append(QString("Partition Name: %1").arg(par.text()));
			}
			else if (par.nodeName() == "PartitionPeriod")
			{
				p[i].period = par.text().toInt(&ok, 10);
				ui.DataTextEdit->append(QString("Period: %1").arg(par.text()));
			}
			else if (par.nodeName() == "PartitionDuration")
			{
				p[i].duration = par.text().toInt(&ok, 10);
				ui.DataTextEdit->append(QString("Duration: %1").arg(par.text()));
			}
			else if (par.nodeName() == "PartitionOffset")
			{
				p[i].offset = par.text().toInt(&ok, 10);
				ui.DataTextEdit->append(QString("Offset: %1").arg(par.text()));
			}
			else if (par.nodeName() == "PartitionPriority")
			{
				p[i].priority = par.text().toInt(&ok, 10);
				if (p[i].priority == 1)
				{
					ui.DataTextEdit->append(QString("Priority: Critical"));
				}
				else if (p[i].priority == 2)
				{
					ui.DataTextEdit->append(QString("Priority: Important"));
				}
				else
				{
					ui.DataTextEdit->append(QString("Priority: Considerable"));
				}
			}
			else if (par.nodeName() == "PartitionIntensivePeriod")
			{
				p[i].intensiveperiod = par.text().toInt(&ok, 10);
				if (p[i].intensiveperiod == 0)
				{
					ui.DataTextEdit->append(QString("No Intensive Period"));
				}
				else if (p[i].intensiveperiod == 1)
				{
					ui.DataTextEdit->append(QString("Intensive Period during Preflight Check"));
				}
				else if (p[i].intensiveperiod == 2)
				{
					ui.DataTextEdit->append(QString("Intensive Period during Departure and Arrival"));
				}
				else
				{
					ui.DataTextEdit->append(QString("Intensive Period during Cruise"));
				}
			}
			else if (par.nodeName() == "PartitionDescription")
			{
				p[i].description = par.text().toStdString();
				ui.DataTextEdit->append(QString("Partition Name: %1").arg(par.text()));
			}
			par = par.nextSiblingElement();
		}
		partition = partition.nextSiblingElement();
		i++;
	}
	return i;
}

int QtCreate::LoadTaskFile()
{
	QMessageBox msg;
	//Load Task Data
	QFile file("SchduleTaskData.xml");
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		ui.ConsoleTextEdit->append(tr("Task File Xml open fail"));
		/*msg.setText("Xml open fail");
		msg.exec();*/
	}
	QDomDocument doc;

	QString errStr;
	int errLine, errCol;
	if (!doc.setContent(&file, false, &errStr, &errLine, &errCol))
	{
		ui.ConsoleTextEdit->append(tr("Unable to load content. ") + errStr);
		/*msg.setText("Unable to load content. ");
		msg.exec();*/
	}
	file.close();

	QDomElement root = doc.documentElement();
	ui.ConsoleTextEdit->append("Task Data Load Complete");
	/*msg.setText("Task Data Load Complete");
	msg.exec();*/

	QDomElement task = root.firstChildElement();
	int i = 1;
	bool ok;

	while (!task.isNull())
	{
		QDomElement tas = task.firstChildElement();
		while (!tas.isNull())
		{
			if (tas.nodeName() == "TaskID")
			{
				t[i].id = tas.text().toInt(&ok, 10);
				ui.DataTextEdit->append(QString("\nTask ID: %1").arg(tas.text()));
			}
			else if (tas.nodeName() == "TaskName")
			{
				t[i].name = tas.text().toStdString();
				ui.DataTextEdit->append(QString("Partition Name: %1").arg(tas.text()));
			}
			else if (tas.nodeName() == "TaskPeriod")
			{
				t[i].period = tas.text().toInt(&ok, 10);
				ui.DataTextEdit->append(QString("Period: %1").arg(tas.text()));
			}
			else if (tas.nodeName() == "TaskExectime")
			{
				t[i].exectime = tas.text().toInt(&ok, 10);
				ui.DataTextEdit->append(QString("Execute Time: %1").arg(tas.text()));
			}
			else if (tas.nodeName() == "TaskDeadline")
			{
				t[i].deadline = tas.text().toInt(&ok, 10);
				ui.DataTextEdit->append(QString("Deadline: %1").arg(tas.text()));
			}
			else if (tas.nodeName() == "TaskOffset")
			{
				t[i].offset = tas.text().toInt(&ok, 10);
				ui.DataTextEdit->append(QString("Offset: %1").arg(tas.text()));
			}
			else if (tas.nodeName() == "TaskPartitionID")
			{
				t[i].partitionid = tas.text().toInt(&ok, 10);
			}
			tas = tas.nextSiblingElement();
		}
		task = task.nextSiblingElement();
		i++;
	}
	return i;
}

void QtCreate::OutputtoGant(int tasknum)
{
	QFile data("Output.txt");
	if (data.open(QIODevice::Text | QIODevice::Append))
	{
		QTextStream out(&data);
		out << QString("00") << endl;
		out << QString("EmptyTask") << endl;
		out << QString("0") << endl;
		out << QString("0") << endl;
	}
	for (int i = 1; i <= tasknum; i++)
	{
		QFile data("Output.txt");
		if (data.open(QIODevice::Text | QIODevice::Append))
		{
			QTextStream out(&data);
			out << QString("%1").arg(t[i].id) << endl;
			out << QString("%1").arg(QString::fromStdString(t[i].name)) << endl;
			out << QString("0") << endl;
			out << QString("0") << endl;
		}
	}
	
}


void QtCreate::PartitionScheduler(int partitionnum)
{
	int timeslice = 0;
	bool flag = false;
	
	for (int i = 0; i < MAXPARTITION; i++)
	{
		PartitionCycle[i] = 0;
	}
	slice = 0;
	while (timeslice < MAXTIMESLICE)
	{
		flag = false;
		for (int i = 1; i <= partitionnum; i++)
		{
			if (p[i].offset <= timeslice && p[i].initonce == false)
			{
				StopRunningTask(p[i].id, timeslice, PartitionTask);
				//printf("Partition %d start, duration is %d, timeslice is %d\n", p[i].id, p[i].duration, timeslice);
				//Sleep(100);
				ui.ConsoleTextEdit->append(QString("Partition %1 start, duration is %2, timeslice is %3").arg(p[i].id).arg(p[i].duration).arg(timeslice));
				ui.ConsoleTextEdit->repaint();
				CheckTaskReady(i, timeslice);
				TaskScheduler(timeslice, PartitionTask, p[i].id);
				timeslice += p[i].duration;
				slice = timeslice;
				PartitionCycle[i] = timeslice;
				flag = true;
				p[i].initonce = true;
				i = 0;
				continue;
			}
			if ((timeslice - PartitionCycle[i] >= p[i].period) && CheckPriorityPartition(i, partitionnum, timeslice))
			{
				StopRunningTask(p[i].id, timeslice, PartitionTask);
				//printf("Partition %d start, duration is %d, timeslice is %d\n", p[i].id, p[i].duration, timeslice);
				//Sleep(100);
				ui.ConsoleTextEdit->append(QString("Partition %1 start, duration is %2, timeslice is %3").arg(p[i].id).arg(p[i].duration).arg(timeslice));
				ui.ConsoleTextEdit->repaint();
				TaskScheduler(timeslice, PartitionTask, p[i].id);
				timeslice += p[i].duration;
				slice = timeslice;
				PartitionCycle[i] = timeslice;
				flag = true;
				i = 0;
				continue;
			}
			if (timeslice > MAXTIMESLICE)
			{
				break;
			}
		}
		if (flag == false)
		{
			timeslice++;
			//printf("Empty cycle, timeslice is %d\n", timeslice);
			//Sleep(10);
			ui.ConsoleTextEdit->append(QString("Empty cycle, timeslice is %1").arg(timeslice));
			ui.ConsoleTextEdit->repaint();
		}
	}
}

void QtCreate::TaskScheduler(int timeslice, int tasknum, int partition)
{
	//int timeslice = 0;
	bool isScheduler = true;

	while (timeslice < slice + p[partition].duration)
	{

		isScheduler = StatusUpdate(timeslice, tasknum, partition);
		bool empty = true;
		for (int i = 1; i <= tasknum; i++)
		{
			if (t[i].stat != Finish && t[i].partitionid == partition)
			{
				empty = false;
			}
		}
		if (empty == true)
		{
			//printf("No Task is Running, timeslice is %d\n", timeslice);
			//Sleep(100);
			ui.ConsoleTextEdit->append(QString("No Task is Running, timeslice is %1").arg(timeslice));
			ui.ConsoleTextEdit->repaint();
			//Output to file
			QFile data("Output.txt");
			if (data.open(QIODevice::Text | QIODevice::Append))
			{
				QTextStream out(&data);
				out << QString("00") << endl;
				out << QString("EmptyTask") << endl;
				out << QString("%1").arg(timeslice) << endl;
				out << QString("%1").arg(timeslice+1) << endl;
			}

		}
		timeslice++;
		for (int i = 1; i <= tasknum; i++)
		{
			if (t[i].exectime == t[i].execclock && t[i].respclock <= t[i].deadline && t[i].stat == Running)
			{
				t[i].stat = Finish;
				//printf("Task id%d is Finish, timeslice is %d\n", t[i].id, timeslice);
				//Sleep(100);
				ui.ConsoleTextEdit->append(QString("Task id%1 is Finish, timeslice is %2").arg(t[i].id).arg(timeslice));
				ui.ConsoleTextEdit->repaint();
				ui.ResultTextEdit->append(QString("Task Id %1 is Finish in %2 (timeslice)").arg(t[i].id).arg(timeslice));
				ui.ResultTextEdit->repaint();
				//Output to file
				QFile data("Output.txt");
				if (data.open(QIODevice::Text | QIODevice::Append))
				{
					QTextStream out(&data);
					//out <<QString("%1 Fin %2").arg(t[i].id).arg(timeslice) << endl;
					out << QString("%1").arg(t[i].id);
					//out << QString("%1").arg(timeslice) << endl;
				}
				//Output to Ready file
				QFile dataRea("OutputReady.txt");
				if (dataRea.open(QIODevice::Text | QIODevice::Append))
				{
					QTextStream out(&dataRea);
					out << QString("%1").arg(t[i].id) << endl;
					out << QString("%1").arg(QString::fromStdString(t[i].name)) << endl;
					out << QString("%1").arg(timeslice) << endl;
					out << QString("%1").arg(timeslice + 0.4) << endl;
				}

				t[i].execclock = 0;
				if (t[i].respclock > TaskWT[i])
				{
					TaskWT[i] = t[i].respclock;
				}
				t[i].respclock = 0;

			}
			/*if (t[i].execclock < t[i].exectime && t[i].respclock == t[i].deadline)
			{
				t[i].stat = Error;
				isScheduler = false;
			}*/
		}
	}
}

bool QtCreate::StatusUpdate(int timeslice, int tasknum, int partition)
{
	bool PartObtainSystemTime = true;
	bool flag = false;
	bool flag2 = false;
	for (int i = 1; i <= tasknum; i++)
	{
		if (t[i].stat == Suspend && timeslice >= t[i].offset)
		{
			t[i].stat = Ready;
			//printf("Task id%d is Ready, timeslice is %d\n", t[i].id, timeslice);
			//Sleep(100);
			ui.ConsoleTextEdit->append(QString("Task id%1 is Ready, timeslice is %2").arg(t[i].id).arg(timeslice));
			ui.ConsoleTextEdit->repaint();
			ui.ResultTextEdit->append(QString("Task Id %1 is Ready in %2 (timeslice)").arg(t[i].id).arg(timeslice));
			ui.ResultTextEdit->repaint();
			//Output to file
			QFile dataRea("OutputReady.txt");
			if (dataRea.open(QIODevice::Text | QIODevice::Append))
			{
				QTextStream out(&dataRea);
				out << QString("%1").arg(t[i].id) << endl;
				out << QString("%1").arg(QString::fromStdString(t[i].name)) << endl;
				out << QString("%1").arg(timeslice) << endl;
				out << QString("%1").arg(timeslice + 0.4) << endl;
			}
			TaskCycle[i] = timeslice;
			if (flag == false)
			{
				t[i].respclock++;
				flag = true;
			}
		}
		if (t[i].stat == Finish && timeslice - TaskCycle[i] >= t[i].period)
		{
			t[i].stat = Ready;
			//printf("Task id%d is Ready, timeslice is %d\n", t[i].id, timeslice);
			//Sleep(100);
			ui.ConsoleTextEdit->append(QString("Task id%1 is Ready, timeslice is %2").arg(t[i].id).arg(timeslice));
			ui.ConsoleTextEdit->repaint();
			ui.ResultTextEdit->append(QString("Task Id %1 is Ready in %2 (timeslice)").arg(t[i].id).arg(timeslice));
			ui.ResultTextEdit->repaint();
			//Output to file
			QFile dataRea("OutputReady.txt");
			if (dataRea.open(QIODevice::Text | QIODevice::Append))
			{
				QTextStream out(&dataRea);
				out << QString("%1").arg(t[i].id) << endl;
				out << QString("%1").arg(QString::fromStdString(t[i].name)) << endl;
				out << QString("%1").arg(timeslice) << endl;
				out << QString("%1").arg(timeslice + 0.4) << endl;
			}
			TaskCycle[i] = timeslice;
			if (flag == false)
			{
				t[i].respclock++;
				flag = true;
			}
		}
		if (t[i].stat == Ready)
		{
			#pragma region READYTORUN
			/*if (t[i].respclock == t[i].deadline)
			{
			t[i].stat = Error;
			printf("Task id%d is Error, timeslice is %d\n", t[i].id, timeslice);
			}*/
			if (ScheduleStrategy == 1)
			{
				if (CheckPriorityReaEDF(i, partition, tasknum) == false && CheckRun(i, tasknum) == false && t[i].partitionid == partition)
				{
					t[i].stat = Running;
					//printf("Task id%d is Running, timeslice is %d\n", t[i].id, timeslice);
					//Sleep(100);
					ui.ConsoleTextEdit->append(QString("Task id%1 is Running, timeslice is %2").arg(t[i].id).arg(timeslice));
					ui.ConsoleTextEdit->repaint();
					//Output to file
					QFile data("Output.txt");
					if (data.open(QIODevice::Text | QIODevice::Append))
					{
						QTextStream out(&data);
						//out << QString("%1 Run %2").arg(t[i].id).arg(timeslice) << endl;
						out << QString("%1").arg(t[i].id) << endl;
						out << QString("%1").arg(QString::fromStdString(t[i].name)) << endl;
						out << QString("%1").arg(timeslice) << endl;
					}

				}
				if (flag == false)
				{
					t[i].respclock++;
					flag = true;
				}
			}
			else if (ScheduleStrategy == 2)
			{
				if (CheckPriorityReaRMS(i, partition, tasknum) == false && CheckRun(i, tasknum) == false && t[i].partitionid == partition)
				{
					t[i].stat = Running;
					//printf("Task id%d is Running, timeslice is %d\n", t[i].id, timeslice);
					//Sleep(100);
					ui.ConsoleTextEdit->append(QString("Task id%1 is Running, timeslice is %2").arg(t[i].id).arg(timeslice));
					ui.ConsoleTextEdit->repaint();
					//Output to file
					QFile data("Output.txt");
					if (data.open(QIODevice::Text | QIODevice::Append))
					{
						QTextStream out(&data);
						//out << QString("%1 Run %2").arg(t[i].id).arg(timeslice) << endl;
						out << QString("%1").arg(t[i].id) << endl;
						out << QString("%1").arg(QString::fromStdString(t[i].name)) << endl;
						out << QString("%1").arg(timeslice) << endl;
					}

				}
				if (flag == false)
				{
					t[i].respclock++;
					flag = true;
				}
			}
			else if (ScheduleStrategy == 3)
			{
				if (CheckPriorityReaDMS(i, partition, tasknum) == false && CheckRun(i, tasknum) == false && t[i].partitionid == partition)
				{
					t[i].stat = Running;
					//printf("Task id%d is Running, timeslice is %d\n", t[i].id, timeslice);
					//Sleep(100);
					ui.ConsoleTextEdit->append(QString("Task id%1 is Running, timeslice is %2").arg(t[i].id).arg(timeslice));
					ui.ConsoleTextEdit->repaint();
					//Output to file
					QFile data("Output.txt");
					if (data.open(QIODevice::Text | QIODevice::Append))
					{
						QTextStream out(&data);
						//out << QString("%1 Run %2").arg(t[i].id).arg(timeslice) << endl;
						out << QString("%1").arg(t[i].id) << endl;
						out << QString("%1").arg(QString::fromStdString(t[i].name)) << endl;
						out << QString("%1").arg(timeslice) << endl;
					}
				}
				if (flag == false)
				{
					t[i].respclock++;
					flag = true;
				}
			}
			else if (ScheduleStrategy == 4)
			{
				if (CheckPriorityReaLST(i, partition, tasknum) == false && CheckRun(i, tasknum) == false && t[i].partitionid == partition)
				{
					t[i].stat = Running;
					//printf("Task id%d is Running, timeslice is %d\n", t[i].id, timeslice);
					//Sleep(100);
					ui.ConsoleTextEdit->append(QString("Task id%1 is Running, timeslice is %2").arg(t[i].id).arg(timeslice));
					ui.ConsoleTextEdit->repaint();
					//Output to file
					QFile data("Output.txt");
					if (data.open(QIODevice::Text | QIODevice::Append))
					{
						QTextStream out(&data);
						//out << QString("%1 Run %2").arg(t[i].id).arg(timeslice) << endl;
						out << QString("%1").arg(t[i].id) << endl;
						out << QString("%1").arg(QString::fromStdString(t[i].name)) << endl;
						out << QString("%1").arg(timeslice) << endl;
					}

				}
				if (flag == false)
				{
					t[i].respclock++;
					flag = true;
				}
			}
			#pragma endregion
		}
		if (t[i].stat == Running)
		{
			#pragma region RUNTOREADY
			if (ScheduleStrategy == 1)
			{
				if (CheckPriorityReaEDF(i, partition, tasknum) == true || t[i].partitionid != partition)
				{
					t[i].stat = Ready;
					//printf("Task id%d is Ready, timeslice is %d\n", t[i].id, timeslice);
					//Sleep(100);
					ui.ConsoleTextEdit->append(QString("Task id%1 is Ready, timeslice is %2").arg(t[i].id).arg(timeslice));
					ui.ConsoleTextEdit->repaint();
					ui.ResultTextEdit->append(QString("Task Id %1 is Ready in %2 (timeslice)").arg(t[i].id).arg(timeslice));
					ui.ResultTextEdit->repaint();
					//Output to file
					QFile data("Output.txt");
					if (data.open(QIODevice::Text | QIODevice::Append))
					{
						QTextStream out(&data);
						//out << QString("%1 Rea %2").arg(t[i].id).arg(timeslice) << endl;
						out << QString("%1").arg(timeslice) << endl;
					}
				}
				if (flag == false)
				{
					t[i].respclock++;
					flag = true;
				}
			}
			else if (ScheduleStrategy == 2)
			{
				if (CheckPriorityReaRMS(i, partition, tasknum) == true || t[i].partitionid != partition)
				{
					t[i].stat = Ready;
					//printf("Task id%d is Ready, timeslice is %d\n", t[i].id, timeslice);
					//Sleep(100);
					ui.ConsoleTextEdit->append(QString("Task id%1 is Ready, timeslice is %2").arg(t[i].id).arg(timeslice));
					ui.ConsoleTextEdit->repaint();
					ui.ResultTextEdit->append(QString("Task Id %1 is Ready in %2 (timeslice)").arg(t[i].id).arg(timeslice));
					ui.ResultTextEdit->repaint();
					//Output to file
					QFile data("Output.txt");
					if (data.open(QIODevice::Text | QIODevice::Append))
					{
						QTextStream out(&data);
						//out << QString("%1 Rea %2").arg(t[i].id).arg(timeslice) << endl;
						out << QString("%1").arg(timeslice) << endl;
					}
				}
				if (flag == false)
				{
					t[i].respclock++;
					flag = true;
				}
			}
			else if (ScheduleStrategy == 3)
			{
				if (CheckPriorityReaDMS(i, partition, tasknum) == true || t[i].partitionid != partition)
				{
					t[i].stat = Ready;
					//printf("Task id%d is Ready, timeslice is %d\n", t[i].id, timeslice);
					//Sleep(100);
					ui.ConsoleTextEdit->append(QString("Task id%1 is Ready, timeslice is %2").arg(t[i].id).arg(timeslice));
					ui.ConsoleTextEdit->repaint();
					ui.ResultTextEdit->append(QString("Task Id %1 is Ready in %2 (timeslice)").arg(t[i].id).arg(timeslice));
					ui.ResultTextEdit->repaint();
					//Output to file
					QFile data("Output.txt");
					if (data.open(QIODevice::Text | QIODevice::Append))
					{
						QTextStream out(&data);
						//out << QString("%1 Rea %2").arg(t[i].id).arg(timeslice) << endl;
						out << QString("%1").arg(timeslice) << endl;
					}
				}
				if (flag == false)
				{
					t[i].respclock++;
					flag = true;
				}
			}
			else if (ScheduleStrategy == 4)
			{
				if (CheckPriorityReaLST(i, partition, tasknum) == true || t[i].partitionid != partition)
				{
					t[i].stat = Ready;
					//printf("Task id%d is Ready, timeslice is %d\n", t[i].id, timeslice);
					//Sleep(100);
					ui.ConsoleTextEdit->append(QString("Task id%1 is Ready, timeslice is %2").arg(t[i].id).arg(timeslice));
					ui.ConsoleTextEdit->repaint();
					ui.ResultTextEdit->append(QString("Task Id %1 is Ready in %2 (timeslice)").arg(t[i].id).arg(timeslice));
					ui.ResultTextEdit->repaint();
					//Output to file
					QFile data("Output.txt");
					if (data.open(QIODevice::Text | QIODevice::Append))
					{
						QTextStream out(&data);
						//out << QString("%1 Rea %2").arg(t[i].id).arg(timeslice) << endl;
						out << QString("%1").arg(timeslice) << endl;
					}
				}
				if (flag == false)
				{
					t[i].respclock++;
					flag = true;
				}
			}
			if (flag2 == false)
			{
				t[i].execclock++;
				flag2 = true;
			}
		#pragma endregion
		}
		if (t[i].stat == Error)
		{
			return false;
		}
		flag = false;
		flag2 = false;
	}
	return true;
}

bool QtCreate::CheckPrioritySus(int i)
{
	for (int j = 1; j < i; j++)
	{
		if (t[j].stat == Suspend)
		{
			return true;
		}
	}
	return false;
}

//相对短截止时间优先调度
bool QtCreate::CheckPriorityReaEDF(int i, int partition, int tasknum)
{
	for (int j = 1; j < tasknum; j++)
	{
		if (t[j].stat == Ready && t[j].partitionid == partition && t[j].respclock > t[i].respclock)
		{
			return true;
		}
	}
	return false;
}

//单调速率调度
bool QtCreate::CheckPriorityReaRMS(int i, int partition, int tasknum)
{
	for (int j = 1; j < tasknum; j++)
	{
		if (t[j].stat == Ready && t[j].partitionid == partition && t[j].period < t[i].period)
		{
			return true;
		}
	}
	return false;
}

//短截止时间调度
bool QtCreate::CheckPriorityReaDMS(int i, int partition, int tasknum)
{
	for (int j = 1; j < tasknum; j++)
	{
		if (t[j].stat == Ready && t[j].partitionid == partition && t[j].deadline < t[i].deadline)
		{
			return true;
		}
	}
	return false;
}

//最小松弛时间调度
bool QtCreate::CheckPriorityReaLST(int i, int partition, int tasknum)
{
	for (int j = 1; j < tasknum; j++)
	{
		if (t[j].stat == Ready && t[j].partitionid == partition && t[j].deadline - t[j].exectime < t[i].deadline - t[i].exectime)
		{
			return true;
		}
	}
	return false;
}

bool QtCreate::CheckRun(int i, int tasknum)
{
	for (int j = 1; j <= tasknum; j++)
	{
		if (t[j].stat == Running)
		{
			return true;
		}
	}
	return false;
}

void QtCreate::CheckTaskReady(int partition, int timeslice)
{
	for (int j = 1; j <= MAXTASK; j++)
	{
		if (t[j].partitionid == partition && t[j].stat == Suspend)
		{
			//printf("Task id%d is Suspend, timeslice is %d\n", t[j].id, timeslice);
			//Sleep(100);
			ui.ConsoleTextEdit->append(QString("Task id%1 is Suspend, timeslice is %2").arg(t[j].id).arg(timeslice));
			ui.ConsoleTextEdit->repaint();
		}
	}
}

bool QtCreate::CheckPriorityPartition(int i, int partition, int timeslice)
{
	int temp = timeslice - PartitionCycle[i] - p[i].period;
	for (int j = 1; j <= partition; j++)
	{
		if (timeslice - PartitionCycle[j] - p[j].period > temp)
		{
			return false;
		}
	}
	return true;
}

void QtCreate::StopRunningTask(int i, int timeslice, int tasknum)
{
	for (int j = 1; j <= tasknum; j++)
	{
		if (t[j].partitionid != i && t[j].stat == Running)
		{
			t[j].stat = Ready;
			//printf("Task id%d is Ready, timeslice is %d\n", t[j].id, timeslice);
			//Sleep(100);
			ui.ConsoleTextEdit->append(QString("Task id%1 is Ready, timeslice is %2").arg(t[j].id).arg(timeslice));
			ui.ConsoleTextEdit->repaint();
			//Output to file
			QFile data("Output.txt");
			if (data.open(QIODevice::Text | QIODevice::Append))
			{
				QTextStream out(&data);
				//out << QString("%1 Rea %2").arg(t[j].id).arg(timeslice) << endl;
				out << QString("%1").arg(timeslice) << endl;
			}
			//t[j].respclock++;
		}
	}
}

void QtCreate::initial()
{
	//for (int i = 0; i < MAXPARTITION; i++)
	//{
	//	PartitionTask[i] = 0;
	//}
	for (int i = 0; i < MAXTASK; i++)
	{
		TaskCycle[i] = 0;
		TaskWT[i] = 0;
	}
	PartitionTask = 11;	//11 tasks in all

	for (int i = 1; i < MAXPARTITION; i++)
	{
		p[i].id = 0;
		p[i].duration = 0;
		p[i].offset = 0;
		p[i].period = 0;
		p[i].times = 0;
		p[i].timescount = 0;
		p[i].priority = 0;
		p[i].intensiveperiod = 0;
		p[i].initonce = false;
	}
	for (int j = 1; j < MAXTASK; j++)
	{
		t[j].id = 0;
		t[j].exectime = 0;
		t[j].deadline = 0;
		t[j].execclock = 0;
		t[j].offset = 0;
		t[j].period = 0;
		t[j].respclock = 0;
		t[j].stat = Suspend;
	}
}

void QtCreate::ClearOutputFile()
{
	QFile data("Output.txt");
	data.resize(0);
	QFile dataRea("OutputReady.txt");
	dataRea.resize(0);
}

void QtCreate::ClearGanttGraph()
{
	Times = 0;
	CountTime = 0;
	//~QtCreate::paintEvent();
	
	for (int i = 0; i < Action.size(); i++)
	{
		delete Action[i]->btn;
		
		//Action[i]->btn->close();
		//Action[i]->btn->setVisible(false);
		////Action[i]->btn->deleteLater();
		//delete Action[i];
	}
	Action.clear();
}