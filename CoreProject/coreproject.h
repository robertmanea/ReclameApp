#ifndef COREPROJECT_H
#define COREPROJECT_H

#include <QWidget>

class QTime;

namespace Ui {
class CoreProject;
}

class CoreProject : public QWidget
{
    Q_OBJECT

public:
    explicit CoreProject(QWidget *parent = 0);
    ~CoreProject();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void drawFPS(QPainter *painter);

private:
    Ui::CoreProject     *ui;

    quint16             m_fpsCounter;
    quint16             m_fpsValue;
    QTime               *m_fpsTimer = nullptr;
};

#endif // COREPROJECT_H
