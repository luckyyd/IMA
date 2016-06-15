#pragma execution_character_set("utf-8")  

#include "Solving.h"
#include <QHBoxLayout>
#include <QtWidgets/QApplication>
#include "qtcreate.h"
#include "ui_qtcreate.h"
#include <qsplashscreen.h>
#include <qdesktopwidget.h>
#include <qtextcodec.h>
#include <qmultimedia.h>
#include <qmediacontrol.h>
#include <qmediaplayer.h>
#include <qvideowidget.h>

int main(int argc, char *argv[])
{
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
	QApplication a(argc, argv);
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	/*QTextCodec *codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::codecForUtfText("GB2312");*/
	QTextCodec *codec = QTextCodec::codecForName("GB18030");
	

	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap("start.png"));
	splash->show();
	for (int i = 0; i<300; i++)
	{
		splash->repaint();
	}

	#pragma region INVALID CODE
	//QWidget *win0 = new QWidget(0);
	/*
	QtCreate *w1 = new QtCreate(win0);
	w1->resize(1600, 1600);
	MyTimeSolveProject *w2 = new MyTimeSolveProject(win0);
	w2->resize(600, 600);
	*/

	/*MyTimeSolveProject *MyProject = new MyTimeSolveProject();
	QtCreate *w = new QtCreate();
	QHBoxLayout *lay = new QHBoxLayout();
	lay->addWidget(w);
	lay->addWidget(MyProject);
	win0->setLayout(lay);
	win0->show();*/

	//QWidget *win0 = new QWidget(0);
	//QtCreate *w = new QtCreate(win0);

	#pragma endregion

	QtCreate w;
	w.setWindowTitle(codec->toUnicode("IMA环境下多任务实时性能最优化系统"));
	w.show();
	
	splash->finish(&w);
	delete splash;

	//MyTimeSolveProject MyProject(ui.GantWidget);
	//MyTimeSolveProject MyPro(Ui::QtCreateClass);
	////MyTimeSolveProject *myproject = new MyTimeSolveProject(this.ui.GantWidget);
	//
	////MyProject.show();
	///*
	//MyProject.show();
	//*/

	//MyTimeSolveProject  MyProject;
	//MyProject.show();

	return a.exec();
}
