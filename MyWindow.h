#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "grid.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent = nullptr);
    ~MyWindow();

private:
    void Populate_TableWidget();

private slots:
    void on_tableWidget_cellClicked(int row, int column);


private:
    std::unique_ptr<Grid> m_grid;

    Ui::Widget * m_ui;
};
#endif // MYWINDOW_H
