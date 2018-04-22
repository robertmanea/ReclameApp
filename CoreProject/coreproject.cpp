#include "coreproject.h"
#include "ui_coreproject.h"
#include <QTimer>
#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QTime>

static QString k_RED_HEXA_CODE = "#FF0000";
static QString k_GREEN_HEXA_CODE = "#00FF00";
static QString k_BLUE_HEXA_CODE = "#0000FF";

CoreProject::CoreProject(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CoreProject)
    , m_fpsCounter(0)
    , m_fpsValue(0)
{
    ui->setupUi(this);

    ui->textEdit->setText("Hello everyone!\nCome and watch some content!");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);

    m_fpsTimer = new QTime();
    m_fpsTimer->start();
}

void CoreProject::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    //white background
    painter.fillRect(event->rect(), Qt::white);

    drawFPS(&painter);

    if(m_fpsTimer->msecsTo(m_fpsTimer->currentTime()) >= 1000)
    {
        m_fpsValue = m_fpsCounter;
        m_fpsCounter = 0;
        m_fpsTimer->restart();
    }
    m_fpsCounter++;
}

void CoreProject::drawFPS(QPainter *painter)
{
    QPen penFpsText;

    if (m_fpsValue < 30)
        penFpsText.setColor(QColor(k_RED_HEXA_CODE));
    else
        penFpsText.setColor(QColor(k_GREEN_HEXA_CODE));

    painter->setPen(penFpsText);
    painter->drawText(QPoint(10, 10), QString("FPS: ") + QString::number(m_fpsValue));
}

CoreProject::~CoreProject()
{
    delete ui;
}
