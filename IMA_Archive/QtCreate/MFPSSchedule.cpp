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

int QtCreate::MFPSLoadPartitionFile()
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
			else if (par.nodeName() == "PartitionTimes")
			{
				p[i].times = par.text().toInt(&ok, 10);
				ui.DataTextEdit->append(QString("Times: %1").arg(par.text()));
			}
			par = par.nextSiblingElement();
		}
		partition = partition.nextSiblingElement();
		i++;
	}
	return i;
}

int QtCreate::MFPSLoadTaskFile()
{
	QMessageBox msg;
	//Load Task Data
	QFile file("SchduleTaskDataForMFPS.xml");
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

void QtCreate::MFPSPartitionScheduler(int partitionnum)
{
	int timeslice = 0;
	bool flag = false;
	bool flagFinish = false;
	for (int i = 0; i < MAXPARTITION; i++)
	{
		PartitionCycle[i] = 0;
	}
	while (timeslice < MAXTIMESLICE)
	{
		flag = false;
		for (int i = 1; i <= partitionnum; i++)
		{
			if (p[i].offset == timeslice && p[i].timescount < p[i].times)
			{
				PartitionCycle[i] = timeslice;
				StopRunningTask(p[i].id, timeslice, PartitionTask);
				p[i].timescount++;
				//printf("Partition %d start, duration is %d, timeslice is %d\n", p[i].id, p[i].duration, timeslice);
				Sleep(100);
				ui.ConsoleTextEdit->append(QString("Partition %1 start, duration is %2, timeslice is %3").arg(p[i].id).arg(p[i].duration).arg(timeslice));
				ui.ConsoleTextEdit->repaint();
				CheckTaskReady(i, timeslice);
				int time = MFPSTaskScheduler(timeslice, PartitionTask, p[i].id);
				if (time == timeslice + p[i].duration)
				{
					timeslice += p[i].duration;
				}
				else
				{
					//Schedule other partition
					//printf("Schedule other partition\n");
					Sleep(100);
					ui.ConsoleTextEdit->append(QString("Schedule other partition"));
					ui.ConsoleTextEdit->repaint();
					timeslice = time;
					for (int j = 1; j <= partitionnum; j++)
					{
						if (j != i)
						{
							p[j].offset = time;
							//Change the offset of Task in p[j]
							for (int k = 1; k <= PartitionTask; k++)
							{
								if (t[k].partitionid == j)
								{
									t[k].offset = time;
								}
							}
							break;
						}
					}
				}
				flag = true;
				continue;
			}
			//if (timeslice - PartitionCycle[i] == p[i].period && p[i].timescount < p[i].times)
			if (p[i].timescount < p[i].times)
			{
				PartitionCycle[i] = timeslice;
				StopRunningTask(p[i].id, timeslice, PartitionTask);
				p[i].timescount++;
				//printf("Partition %d start, duration is %d, timeslice is %d\n", p[i].id, p[i].duration, timeslice);
				Sleep(100);
				ui.ConsoleTextEdit->append(QString("Partition %1 start, duration is %2, timeslice is %3").arg(p[i].id).arg(p[i].duration).arg(timeslice));
				ui.ConsoleTextEdit->repaint();
				int time = MFPSTaskScheduler(timeslice, PartitionTask, p[i].id);
				if (time == timeslice + p[i].duration)
				{
					timeslice += p[i].duration;
				}
				else
				{
					//Schedule other partition
					//printf("Schedule other partition\n");
					Sleep(100);
					ui.ConsoleTextEdit->append(QString("Schedule other partition"));
					ui.ConsoleTextEdit->repaint();
					for (int j = 1; j <= partitionnum; j++)
					{
						if (j != i)
						{
							p[j].period = time - PartitionCycle[i];
							timeslice = time;
							break;
						}
					}
				}

				flag = true;
				continue;
			}
		}
		if (flag == false)
		{
			if (flagFinish == false)
			{
				FinishTime = timeslice;
				flagFinish = true;
			}
			timeslice++;
			//printf("Empty cycle, timeslice is %d\n", timeslice);
			Sleep(10);
			ui.ConsoleTextEdit->append(QString("Empty cycle, timeslice is %1").arg(timeslice));
			ui.ConsoleTextEdit->repaint();
			//Handle empty cycle from here//
		}
	}
}

int QtCreate::MFPSTaskScheduler(int timeslice, int tasknum, int partition)
{
	//int timeslice = 0;
	bool isScheduler = true;

	while (timeslice < PartitionCycle[partition] + p[partition].duration)
	{
		isScheduler = MFPSStatusUpdate(timeslice, tasknum, partition);
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
			//Handle empty timeslice from here//
			Sleep(100);
			ui.ConsoleTextEdit->append(QString("No Task is Running, timeslice is %1").arg(timeslice));
			ui.ConsoleTextEdit->repaint();
			//Output to file
			QFile data("Output.txt");
			if (data.open(QIODevice::Text | QIODevice::Append))
			{
				QTextStream out(&data);
				out << QString("00") << endl;
				out << QString("%2").arg(timeslice) << endl;
				out << QString("%2").arg(timeslice) << endl;
			}

			return timeslice;
		}
		timeslice++;
		for (int i = 1; i <= tasknum; i++)
		{
			if (t[i].exectime == t[i].execclock && t[i].respclock <= t[i].deadline && t[i].stat == Running)
			{
				t[i].stat = Finish;
				//printf("Task id%d is Finish, timeslice is %d\n", t[i].id, timeslice);
				Sleep(100);
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
					out << QString("%2").arg(timeslice) << endl;
				}
				//Output to Ready file
				QFile dataRea("OutputReady.txt");
				if (dataRea.open(QIODevice::Text | QIODevice::Append))
				{
					QTextStream out(&dataRea);
					out << QString("%1").arg(t[i].id) << endl;
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
			if (t[i].execclock < t[i].exectime && t[i].respclock == t[i].deadline)
			{
				t[i].stat = Error;
				isScheduler = false;
			}
		}
	}
	return timeslice;
}

bool QtCreate::MFPSStatusUpdate(int timeslice, int tasknum, int partition)
{
	bool PartObtainSystemTime = true;
	bool flag = false;
	bool flag2 = false;
	for (int i = 1; i <= tasknum; i++)
	{
		//if (t[i].stat == Suspend && timeslice == t[i].offset)
		if (t[i].stat == Suspend && t[i].partitionid == partition)
		{
			t[i].stat = Ready;
			//printf("Task id%d is Ready, timeslice is %d\n", t[i].id, timeslice);
			Sleep(100);
			ui.ConsoleTextEdit->append(QString("Task id%1 is Ready, timeslice is %2").arg(t[i].id).arg(timeslice));
			ui.ConsoleTextEdit->repaint();
			ui.ResultTextEdit->append(QString("Task Id %1 is Ready in %2 (timeslice)").arg(t[i].id).arg(timeslice));
			ui.ResultTextEdit->repaint();
			//Output to Ready file
			QFile dataRea("OutputReady.txt");
			if (dataRea.open(QIODevice::Text | QIODevice::Append))
			{
				QTextStream out(&dataRea);
				out << QString("%1").arg(t[i].id) << endl;
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
			Sleep(100);
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
					Sleep(100);
					ui.ConsoleTextEdit->append(QString("Task id%1 is Running, timeslice is %2").arg(t[i].id).arg(timeslice));
					ui.ConsoleTextEdit->repaint();
					//Output to file
					QFile data("Output.txt");
					if (data.open(QIODevice::Text | QIODevice::Append))
					{
						QTextStream out(&data);
						//out << QString("%1 Run %2").arg(t[i].id).arg(timeslice) << endl;
						out << QString("%1").arg(t[i].id) << endl;
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
					Sleep(100);
					ui.ConsoleTextEdit->append(QString("Task id%1 is Running, timeslice is %2").arg(t[i].id).arg(timeslice));
					ui.ConsoleTextEdit->repaint();
					//Output to file
					QFile data("Output.txt");
					if (data.open(QIODevice::Text | QIODevice::Append))
					{
						QTextStream out(&data);
						//out << QString("%1 Run %2").arg(t[i].id).arg(timeslice) << endl;
						out << QString("%1").arg(t[i].id) << endl;
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
					Sleep(100);
					ui.ConsoleTextEdit->append(QString("Task id%1 is Running, timeslice is %2").arg(t[i].id).arg(timeslice));
					ui.ConsoleTextEdit->repaint();
					//Output to file
					QFile data("Output.txt");
					if (data.open(QIODevice::Text | QIODevice::Append))
					{
						QTextStream out(&data);
						//out << QString("%1 Run %2").arg(t[i].id).arg(timeslice) << endl;
						out << QString("%1").arg(t[i].id) << endl;
						out << QString("%1").arg(timeslice) << endl;
					}

				}
				if (flag == false)
				{
					t[i].respclock++;
					flag = true;
				}
			}

		}
		if (t[i].stat == Running)
		{
			if (ScheduleStrategy == 1)
			{
				if (CheckPriorityReaEDF(i, partition, tasknum) == true || t[i].partitionid != partition)
				{
					t[i].stat = Ready;
					//printf("Task id%d is Ready, timeslice is %d\n", t[i].id, timeslice);
					Sleep(100);
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
					Sleep(100);
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
					Sleep(100);
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