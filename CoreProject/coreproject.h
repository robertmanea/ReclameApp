#ifndef COREPROJECT_H
#define COREPROJECT_H

#include <QWidget>

namespace Ui {
class CoreProject;
}

class CoreProject : public QWidget
{
    Q_OBJECT

public:
    explicit CoreProject(QWidget *parent = 0);
    ~CoreProject();

private:
    Ui::CoreProject *ui;
};

#endif // COREPROJECT_H
