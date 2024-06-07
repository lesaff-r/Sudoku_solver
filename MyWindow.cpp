#include "MyWindow.h"
#include "./ui_MyWindow.h"

#include <QTimer>

MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::Widget)
{
    m_ui->setupUi(this);
    this->setWindowTitle("Sudoku");

    m_grid = std::make_unique<Grid>();
    Populate_TableWidget();
    m_selected_cell = m_ui->tableWidget->item(0, 0);
    Highlight_cells();
}

MyWindow::~MyWindow()
{
    delete m_ui;
}


void
MyWindow::Populate_TableWidget()
{
    const Raw_grid & raw_grid = m_grid->get_grid();

    for (int row = 0 ; row < 9 ; ++row)
    {
        for (int column = 0 ; column < 9 ; ++column)
        {
            QTableWidgetItem * cell = m_ui->tableWidget->item(row, column);

            if (cell == nullptr) {
                cell = new QTableWidgetItem ("");

                cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
                cell->setTextAlignment(Qt::AlignCenter);

                m_ui->tableWidget->setItem(row, column, cell);
            }

            if (raw_grid[row][column]) {
                cell->setText(QString::number(raw_grid[row][column]));
                cell->setFlags(cell->flags() ^ Qt::ItemIsSelectable);
                cell->setBackground(QColor("light grey"));
            }
        }
    }
}

void
    MyWindow::Set_CrossCells_color(const QColor color)
{
    int row = m_selected_cell->row();
    int column = m_selected_cell->column();

    for (int row_check = 0 ; row_check < 9 ; ++row_check)
    {
        QTableWidgetItem * cell = m_ui->tableWidget->item(row_check, column);

        if (cell->flags() & Qt::ItemIsSelectable)
            cell->setBackground(QColor(color));
    }
    for (int column_check = 0 ; column_check < 9 ; ++column_check)
    {
        QTableWidgetItem * cell = m_ui->tableWidget->item(row, column_check);

        if (cell->flags() & Qt::ItemIsSelectable)
            cell->setBackground(QColor(color));
    }
}

void
MyWindow::UnHighlight_cells()
{
    Set_CrossCells_color(QColor("white"));
}

void
MyWindow::Highlight_cells()
{
    Set_CrossCells_color(QColor("light blue"));
    m_selected_cell->setBackground(QColor("blue"));
}


void
MyWindow::set_value_in_row_grid(const int row, const int column, const int value)
{
    m_grid->set_value_in_cell(row, column, value);
}


void MyWindow::on_tableWidget_cellClicked(int row, int column)
{
    QTableWidgetItem * cell = m_ui->tableWidget->item(row, column);

    if (cell->flags() & Qt::ItemIsSelectable)
    {
        UnHighlight_cells();
        m_selected_cell = cell;
        Highlight_cells();

    }
}


void
    MyWindow::Blink_cell_in_red(QTableWidgetItem * cell)
{
    QBrush color = cell->background();
    cell->setBackground(QColor("red"));
    QTimer::singleShot(1000, [cell, color]{
        cell->setBackground(color);
    });
}

bool
MyWindow::Can_edit_cell(const int row, const int column, const int value)
{
    for (int row_check = 0 ; row_check < 9 ; ++row_check)
    {
        if (m_grid->Is_number_in_cell(row_check, column, value))
        {
            QTableWidgetItem * cell = m_ui->tableWidget->item(row_check, column);

            Blink_cell_in_red(cell);
            return false;
        }
    }
    for (int column_check = 0 ; column_check < 9 ; ++column_check)
    {
        if (m_grid->Is_number_in_cell(row, column_check, value))
        {
            QTableWidgetItem * cell = m_ui->tableWidget->item(row, column_check);

            Blink_cell_in_red(cell);
            return false;
        }
    }

    return true;
}

void MyWindow::on_pushButton_1_clicked()
{
    const int row = m_selected_cell->row();
    const int column = m_selected_cell->column();
    const QString value = "1";

    if (Can_edit_cell(row, column, value.toInt()))
    {
        m_selected_cell->setText(value);
        set_value_in_row_grid(row, column, value.toInt());
    }
}

