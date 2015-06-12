#ifndef SOLVING_H
#define SOLVING_H

#include <qdialog.h>
#include <qtimer.h>
#include <qmouseeventtransition.h>

#include  <QTime>
#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include "ActionStruct.h"

class   QLabel;
class   QPushButton;
class   QMenu;
class   QMenuBar;
class   QLineEdit;
////////////////////////////// 绘制坐标轴
#define SEGMENT  10          // 时间分为 10段
#define MAXSOURCENUM  100    // 定义资源最多消耗

class MyTimeSolveProject : public QMainWindow
{
	Q_OBJECT

public:
	MyTimeSolveProject(QWidget *parent = 0);

private:
	int           CountTime;
	int           ActionNum;
	int           BeginTime;
	int           EndTime;
	int           Times;

	int           CountMouseClicked;
	int           LastY;
	int           LastX;

	QPushButton   *FileOpenBtn;
	QPushButton   *SaveBtn;

	QList <Resource >  SourceArray;

	QLabel        *timelabel;
	QLabel        *SetTimelabel;
	QLineEdit     *SetTimeEdit;
	QPushButton   *SetTimeBtn;
	QTime         ChangingTime;
	QLabel        *label;
	QLabel        *ShowText;
	QPushButton   *ShowTime;
	QList          <ElapsedTimeStruct *> TimeElaped;

private:
	void  CreateModifActionMenu();
	void  ReadFile();         // 读取梅超亮规划好的文件。
	void  paintEvent(QPaintEvent *);


	private
	slots:
	void  LoadAction();
	void  SetTimes();                //设置时间倍率。
	void  SaveAction();              // 保存修改后的文件，作为待规划文件，交给梅超亮验证该解是否合理。
};

#endif // SOLVING_H
