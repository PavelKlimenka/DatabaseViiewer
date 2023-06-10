#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>
#include <QAbstractItemModel>

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InfoWindow(QWidget *parent = nullptr);
    ~InfoWindow();

    void setData(QString username, QAbstractItemModel* model);
private:
    QAbstractItemModel* model{};
    Ui::InfoWindow *ui;

    void closeEvent(QCloseEvent* event);
};

#endif // INFOWINDOW_H
