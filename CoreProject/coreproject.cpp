#include "coreproject.h"
#include "ui_coreproject.h"
#include <QTimer>
#include <QPainter>
#include <QEvent>
#include <QPaintEvent>

CoreProject::CoreProject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoreProject)
{
    ui->setupUi(this);

    ui->textEdit->setText("Hello everyone!\nCome and watch some content!");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);
}

void CoreProject::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    //white background
    painter.fillRect(event->rect(), Qt::white);
}

CoreProject::~CoreProject()
{
    delete ui;
}
