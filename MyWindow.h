#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "grid.h"

#include <QWidget>
#include <QTableWidgetItem>

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
    void Set_CrossCells_color(const QColor color);
    void UnHighlight_cells();
    void Highlight_cells();

    void Blink_cell_in_red(QTableWidgetItem * cell);
    bool Can_edit_cell(const int row, const int column, const int value);

    void set_value_in_row_grid(const int row, const int column, const int value);

private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_1_clicked();


private:
    std::unique_ptr<Grid>   m_grid;
    QTableWidgetItem *      m_selected_cell;

    Ui::Widget * m_ui;
};
#endif // MYWINDOW_H
