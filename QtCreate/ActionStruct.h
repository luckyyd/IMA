#ifndef ACTIONSTRUCT_H
#define ACTIONSTRUCT_H
#include <qlist.h>
class QLabel;
class QPushButton;
class QString;

typedef struct  ResourceStruct            // ÿ��action�����Ķ�����Դ
{
	QString  SourceName;
	int      SourceNum;
} Resource;

typedef struct Action_Attribute           // action����
{
	QString      TaskName;
	double       BeginTime;
	double       LastTime;
	QLabel       *label;
	QPushButton  *btn;
	QList <Resource *>  source;
}ActionAttribute;

typedef struct StructTimeElaped          // ʱ�侫��
{
	int ElapedTime;
	int ElapedTimes;
}ElapsedTimeStruct;

#endif // ACTIONSTRUCT_H
