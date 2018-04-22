#include "coreproject.h"
#include "ui_coreproject.h"
#include <QTimer>
#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QTime>

#include "time.h"

static QString k_RED_HEXA_CODE = "#FF0000";
static QString k_GREEN_HEXA_CODE = "#00FF00";
static QString k_BLUE_HEXA_CODE = "#0000FF";

CoreProject::CoreProject(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CoreProject)
    , m_fpsCounter(0)
    , m_fpsValue(0)
{
    srand(time(NULL));

    ui->setupUi(this);

    int nodesNumber = rand() % 20 + 10;

    while (--nodesNumber)
    {
        QPoint newCircleCenter;
        newCircleCenter.setX(rand() % geometry().width());
        newCircleCenter.setY(rand() % geometry().height());
        m_circles.push_back(QPair<QPoint, Qt::GlobalColor>(newCircleCenter, static_cast<Qt::GlobalColor>(rand()%20)));
    }

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

    // draw the scene
    drawScene(&painter);

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

void CoreProject::drawCircle(QPainter *painter, QPoint centerPoint, quint32 radius)
{
    QRect elipseRect(QPoint(centerPoint.x() - radius, centerPoint.y() - radius),
                     QPoint(centerPoint.x() + radius, centerPoint.y() + radius));

    painter->drawEllipse(elipseRect);
}

void CoreProject::drawLine(QPainter *painter, QPoint first, QPoint second)
{
    QLine qLine(first, second);
    painter->drawLine(qLine);
}

void CoreProject::drawScene(QPainter *painter)
{
    if (painter == nullptr)
        return;

    QPen blackPen;
    blackPen.setColor(QColor("#000000"));
    painter->setPen(blackPen);

    for (auto iter : m_circles)
    {
        painter->setBrush(iter.second);
        drawCircle(painter, iter.first, 5);
    }
}

CoreProject::~CoreProject()
{
    delete ui;
}
