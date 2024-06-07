#include "MyWindow.h"
#include "./ui_MyWindow.h"

MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::Widget)
{
    m_ui->setupUi(this);
    this->setWindowTitle("Sudoku");

    m_grid = std::make_unique<Grid>();
    Populate_TableWidget();
    m_selected_cell = m_ui->tableWidget->item(0, 0);
}

MyWindow::~MyWindow()
{
    delete m_ui;
}


void
MyWindow::Populate_TableWidget()
{
    const Raw_grid & raw_grid = m_grid->get_grid();

    for (int line = 0 ; line < 9 ; ++line)
    {
        for (int column = 0 ; column < 9 ; ++column)
        {
            QTableWidgetItem * cell = m_ui->tableWidget->item(line, column);

            if (cell == nullptr) {
                cell = new QTableWidgetItem ("");

                cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
                cell->setTextAlignment(Qt::AlignCenter);

                m_ui->tableWidget->setItem(line, column, cell);
            }

            if (raw_grid[line][column]) {
                cell->setText(QString::number(raw_grid[line][column]));
                cell->setFlags(cell->flags() ^ Qt::ItemIsSelectable);
                cell->setBackground(QColor("light grey"));
            }
        }
    }
}

void
    MyWindow::Set_CrossCells_color(const QColor color)
{
    int line = m_selected_cell->row();
    int column = m_selected_cell->column();

    for (int cell_in_line = 0 ; cell_in_line < 9 ; ++cell_in_line)
    {
        QTableWidgetItem * cell = m_ui->tableWidget->item(cell_in_line, column);

        if (cell->flags() & Qt::ItemIsSelectable)
            cell->setBackground(QColor(color));
    }
    for (int cell_in_column = 0 ; cell_in_column < 9 ; ++cell_in_column)
    {
        QTableWidgetItem * cell = m_ui->tableWidget->item(line, cell_in_column);

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
        //cell->setText(QString::number(row) + ',' + QString::number(column));
}

