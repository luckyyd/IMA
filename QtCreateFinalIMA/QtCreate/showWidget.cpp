#include "showWidget.h"
#include <QHBoxLayout>

showWidget::showWidget(QWidget *parent) :QWidget(parent)
{
	text = new QTextEdit;
	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(text);
}


showWidget::~showWidget()
{
}
