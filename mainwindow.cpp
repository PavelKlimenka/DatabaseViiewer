#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QString>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", dbConnectionName);
    db.setHostName("localhost");
    db.setDatabaseName("qtdata");
    db.setUserName("postgres");
    db.setPassword("1111");
    if(!db.open())
    {
        QMessageBox::critical(this, "Fatal error", QString("Failed to open database connection: ") + db.lastError().text());
        QApplication::exit(1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

