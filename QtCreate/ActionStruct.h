#ifndef ACTIONSTRUCT_H
#define ACTIONSTRUCT_H
#include <qlist.h>
class QLabel;
class QPushButton;
class QString;

typedef struct  ResourceStruct            // 每个action，消耗多种资源
{
	QString  SourceName;
	int      SourceNum;
} Resource;

typedef struct Action_Attribute           // action属性
{
	QString      TaskName;
	double       BeginTime;
	double       LastTime;
	QLabel       *label;
	QPushButton  *btn;
	QList <Resource *>  source;
}ActionAttribute;

typedef struct StructTimeElaped          // 时间精度
{
	int ElapedTime;
	int ElapedTimes;
}ElapsedTimeStruct;

#endif // ACTIONSTRUCT_H
