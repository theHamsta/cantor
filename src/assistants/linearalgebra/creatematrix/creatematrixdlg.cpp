/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301, USA.

    ---
    Copyright (C) 2009 Alexander Rieder <alexanderrieder@gmail.com>
 */

#include "creatematrixdlg.h"
#include <QPushButton>

CreateMatrixDlg::CreateMatrixDlg(QWidget* parent) : QDialog(parent)
{
    m_base=new Ui::CreateMatrixAssistantBase;
    QWidget* mainW=new QWidget(this);
    m_base->setupUi(mainW);

    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);
    layout->addWidget(mainW);

    m_base->buttonBox->button(QDialogButtonBox::Ok)->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogOkButton));
    m_base->buttonBox->button(QDialogButtonBox::Cancel)->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogCancelButton));
    connect(m_base->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_base->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(m_base->rows, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &CreateMatrixDlg::changeNumRows);
    connect(m_base->columns, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &CreateMatrixDlg::changeNumCols);
}

CreateMatrixDlg::~CreateMatrixDlg()
{
    delete m_base;
}

void CreateMatrixDlg::changeNumRows(int rows)
{
    m_base->values->setRowCount(rows);
}

void CreateMatrixDlg::changeNumCols(int cols)
{
    m_base->values->setColumnCount(cols);
}

int CreateMatrixDlg::numRows()
{
    return m_base->rows->value();
}

int CreateMatrixDlg::numCols()
{
    return m_base->columns->value();
}

QString CreateMatrixDlg::value(int i, int j)
{
    const QTableWidgetItem* item=m_base->values->item(i, j);
    if(item)
        return item->text();
    else
        return QLatin1String("0");
}


