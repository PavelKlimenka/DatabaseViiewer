#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <vector>
#include "infowindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_refreshButton_clicked();

    void onListViewDoubleClicked(const QModelIndex &index);

private:
    const QString dbConnectionName = "MainConnection";
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQueryModel usersModel;
    InfoWindow infoWindow;
};
#endif // MAINWINDOW_H
