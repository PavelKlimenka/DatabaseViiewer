#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>
#include <QSqlQuery>
#include <QString>
#include <QUuid>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , infoWindow(this)
{
    ui->setupUi(this);

    ui->statusLabel->hide();


    db = QSqlDatabase::addDatabase("QPSQL", dbConnectionName);
    db.setHostName("localhost");
    db.setDatabaseName("qtdata");
    db.setUserName("postgres");
    db.setPassword("1111");
    if(!db.open())
    {
        QMessageBox::critical(this, "Fatal error", QString("Failed to open database connection: ") + db.lastError().text());
        exit(1);
    }

    usersModel.setQuery("SELECT * FROM users", db);
    if(usersModel.lastError().isValid())
    {
        QMessageBox::critical(this, "Failure", QString("Failed to fetch info on user items: %1").arg(usersModel.lastError().text()));
        exit(1);
    }

    ui->listView->setModel(&usersModel);
    ui->listView->setModelColumn(1);
    connect(ui->listView, &QListView::doubleClicked, this, &MainWindow::onListViewDoubleClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_refreshButton_clicked()
{
    ui->statusLabel->setText("Refreshing...");
    ui->statusLabel->show();
    usersModel.setQuery("SELECT * FROM users", db);
    ui->statusLabel->hide();
}


void MainWindow::onListViewDoubleClicked(const QModelIndex &index)
{
    QSqlQueryModel* infoModel = new QSqlQueryModel();
    QUuid selectedUserId = usersModel.record(index.row()).value("user_id").toUuid();

    infoModel->setQuery(QString("SELECT * FROM items WHERE owner_id='%1'").arg(selectedUserId.toString()), db);
    if(infoModel->lastError().isValid())
    {
        QMessageBox::critical(this, "Failure", QString("Failed to fetch info on user items: %1").arg(infoModel->lastError().text()));
        delete infoModel;
        return;
    }

    infoWindow.setData(index.data().toString(), infoModel);

    infoWindow.show();
}
