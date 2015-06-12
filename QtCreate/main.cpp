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

	#pragma region VIDEOVIEW1
	QWidget *widget1 = new QWidget;
	widget1->resize(400, 300);   //
	widget1->setWindowTitle("View1");
	QVBoxLayout *layout1 = new QVBoxLayout;
	QMediaPlayer* player1 = new QMediaPlayer;
	QVideoWidget* vw1 = new QVideoWidget;

	layout1->addWidget(vw1);
	widget1->setLayout(layout1);

	player1->setVideoOutput(vw1);

	QFile file1("Video02.AVI");
	if (!file1.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player1->setMedia(QUrl::fromLocalFile("Video02.AVI"));
	player1->play();
	widget1->show();
	#pragma endregion

	#pragma region VIDEOVIEW2
	QWidget *widget2 = new QWidget;
	widget2->resize(400, 300);   //
	widget2->setWindowTitle("View2");
	QVBoxLayout *layout2 = new QVBoxLayout;
	QMediaPlayer* player2 = new QMediaPlayer;
	QVideoWidget* vw2 = new QVideoWidget;

	layout2->addWidget(vw2);
	widget2->setLayout(layout2);

	player2->setVideoOutput(vw2);

	QFile file2("Video03.AVI");
	if (!file2.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player2->setMedia(QUrl::fromLocalFile("Video03.AVI"));
	player2->play();
	widget2->show();
	#pragma endregion

	#pragma region VIDEOVIEWPANEL
	QWidget *widget3 = new QWidget;
	widget3->resize(400, 300);   //
	widget3->setWindowTitle("Panel");
	QVBoxLayout *layout3 = new QVBoxLayout;
	QMediaPlayer* player3 = new QMediaPlayer;
	QVideoWidget* vw3 = new QVideoWidget;

	layout3->addWidget(vw3);
	widget3->setLayout(layout3);

	player3->setVideoOutput(vw3);

	QFile file3("Video01.AVI");
	if (!file3.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player3->setMedia(QUrl::fromLocalFile("Video01.AVI"));
	player3->play();
	widget3->show();
	#pragma endregion

	return a.exec();
}
