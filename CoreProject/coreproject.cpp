#include "coreproject.h"
#include "ui_coreproject.h"

CoreProject::CoreProject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoreProject)
{
    ui->setupUi(this);
}

CoreProject::~CoreProject()
{
    delete ui;
}
