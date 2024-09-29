#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "grid.h"
#include "solver.h"

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
    void Set_SquareCells_color(const QColor color);
    void UnHighlight_cells();
    void Highlight_cells();

    void                Blink_cell_in_red(QTableWidgetItem * cell);
    QTableWidgetItem *  Row_check(const int column, const int value);
    QTableWidgetItem *  Column_check(const int row, const int value);
    QTableWidgetItem *  Square_check(const int row, const int column, const int value);
    bool                Can_edit_cell(const int row, const int column, const int value);

    void on_numberButton_clicked(const int value);
    void set_value_in_row_grid(const int row, const int column, const int value);

private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_clear_clicked();

    void on_pushButton_Hint_clicked();

private:
    std::shared_ptr<Grid>   m_grid;
    std::unique_ptr<Solver> m_solver;

    QTableWidgetItem *      m_selected_cell;

    Ui::Widget * m_ui;
};
#endif // MYWINDOW_H
