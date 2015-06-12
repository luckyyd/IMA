#pragma once
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QImage>

class showWidget : public QWidget
{
	Q_OBJECT

public:
	showWidget(QWidget *parent = 0);
	~showWidget();
	QTextEdit *text;

signals:

	public slots:

};

