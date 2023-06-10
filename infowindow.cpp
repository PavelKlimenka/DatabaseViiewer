#include "infowindow.h"
#include "ui_infowindow.h"

InfoWindow::InfoWindow(QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
}

InfoWindow::~InfoWindow()
{
    delete ui;
}

void InfoWindow::setData(QString username, QAbstractItemModel* model)
{
    this->model = model;

    ui->usernameLabel->setText(QString("%1's items:").arg(username));

    ui->listView->setModel(model);
    ui->listView->setModelColumn(1);
}

void InfoWindow::closeEvent(QCloseEvent *event)
{
    if(model)
    {
        delete model;
        model = nullptr;
    }
}
