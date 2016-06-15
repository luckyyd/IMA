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

void QtCreate::Preflight_Click()
{
	#pragma region VIDEOVIEW1ForPreflight
	QMediaPlayer* player1 = new QMediaPlayer;
	player1->setVideoOutput(ui.View1Widget);

	QFile file1("v4_4.avi");
	if (!file1.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player1->setMedia(QUrl::fromLocalFile("v4_4.avi"));
	player1->play();
	#pragma endregion

	#pragma region VIDEOVIEW2ForPreflight
	QMediaPlayer* player2 = new QMediaPlayer;
	player2->setVideoOutput(ui.View2Widget);

	QFile file2("v4_5.avi");
	if (!file2.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player2->setMedia(QUrl::fromLocalFile("v4_5.AVI"));
	player2->play();
	#pragma endregion

	#pragma region VIDEOVIEWPANELForPreflight
	QMediaPlayer* player3 = new QMediaPlayer;
	player3->setVideoOutput(ui.PanelWidget);

	QFile file3("v4_1.avi");
	if (!file3.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player3->setMedia(QUrl::fromLocalFile("v4_1.AVI"));
	player3->play();
	#pragma endregion
}


void QtCreate::Departure_Click()
{
	#pragma region VIDEOVIEW1ForDeparture
	QMediaPlayer* player1 = new QMediaPlayer;
	player1->setVideoOutput(ui.View1Widget);

	QFile file1("Video02.AVI");
	if (!file1.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player1->setMedia(QUrl::fromLocalFile("Video02.AVI"));
	player1->play();
	#pragma endregion
	
	#pragma region VIDEOVIEW2ForDeparture
	QMediaPlayer* player2 = new QMediaPlayer;
	player2->setVideoOutput(ui.View2Widget);

	QFile file2("Video03.AVI");
	if (!file2.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player2->setMedia(QUrl::fromLocalFile("Video03.AVI"));
	player2->play();
	#pragma endregion

	#pragma region VIDEOVIEWPANELForDeparture
	QMediaPlayer* player3 = new QMediaPlayer;
	player3->setVideoOutput(ui.PanelWidget);

	QFile file3("Video01.AVI");
	if (!file3.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player3->setMedia(QUrl::fromLocalFile("Video01.AVI"));
	player3->play();
	#pragma endregion
}


void QtCreate::Cruise_Click()
{
	#pragma region VIDEOVIEW1ForCruise
	QMediaPlayer* player1 = new QMediaPlayer;
	player1->setVideoOutput(ui.View1Widget);

	QFile file1("Video02.AVI");
	if (!file1.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player1->setMedia(QUrl::fromLocalFile("Video02.AVI"));
	player1->play();
	#pragma endregion

	#pragma region VIDEOVIEW2ForCruise
	QMediaPlayer* player2 = new QMediaPlayer;
	player2->setVideoOutput(ui.View2Widget);

	QFile file2("Video03.AVI");
	if (!file2.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player2->setMedia(QUrl::fromLocalFile("Video03.AVI"));
	player2->play();
	#pragma endregion

	#pragma region VIDEOVIEWPANELForCruise
	QMediaPlayer* player3 = new QMediaPlayer;
	player3->setVideoOutput(ui.PanelWidget);

	QFile file3("Video01.AVI");
	if (!file3.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player3->setMedia(QUrl::fromLocalFile("Video01.AVI"));
	player3->play();
	#pragma endregion
}

void QtCreate::Arrival_Click()
{
	#pragma region VIDEOVIEW1ForArrival
	QMediaPlayer* player1 = new QMediaPlayer;
	player1->setVideoOutput(ui.View1Widget);

	QFile file1("Video02.AVI");
	if (!file1.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player1->setMedia(QUrl::fromLocalFile("Video02.AVI"));
	player1->play();
	#pragma endregion

	#pragma region VIDEOVIEW2ForArrival
	QMediaPlayer* player2 = new QMediaPlayer;
	player2->setVideoOutput(ui.View2Widget);

	QFile file2("Video03.AVI");
	if (!file2.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player2->setMedia(QUrl::fromLocalFile("Video03.AVI"));
	player2->play();
	#pragma endregion

	#pragma region VIDEOVIEWPANELForArrival
	QMediaPlayer* player3 = new QMediaPlayer;
	player3->setVideoOutput(ui.PanelWidget);

	QFile file3("Video01.AVI");
	if (!file3.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	player3->setMedia(QUrl::fromLocalFile("Video01.AVI"));
	player3->play();
	#pragma endregion
}

void QtCreate::BroadcastVideo()
{
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
	//Start here
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
}