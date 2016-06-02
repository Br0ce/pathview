/** @file set_dim_dialog.cpp
 *
 * @brief Dialog to set dimensions of maze
 *
 * Copyright (C) 2016  @author Niklas Beck, beck@informatik.uni-bonn.de
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */


#include "set_dim_dialog.h"


Set_dim_dialog::Set_dim_dialog(QWidget* parent) :
  QDialog(parent),
  db_box_(new QDialogButtonBox(QDialogButtonBox::Ok |
                               QDialogButtonBox::Cancel, this)),

  sb_rows_(new QSpinBox(this)),
  sb_cols_(new QSpinBox(this)),

  l_rows_(new QLabel(this)),
  l_cols_(new QLabel(this)),

  g_layout_(new QGridLayout(this))
{
  this->setModal(true);
  this->setWindowTitle("set maze dimensions");
  this->setLayout(g_layout_);

  l_rows_->setText(tr("rows"));
  l_cols_->setText(tr("cols"));

  sb_rows_->setMinimum(1);
  sb_rows_->setMaximum(20);
  sb_cols_->setMinimum(1);
  sb_cols_->setMaximum(20);

  g_layout_->setAlignment(Qt::AlignCenter);
  g_layout_->setSizeConstraint(QLayout::SetFixedSize);

  g_layout_->addWidget(l_rows_, 0, 0);
  g_layout_->addWidget(l_cols_, 1, 0);
  g_layout_->addWidget(sb_rows_, 0, 1);
  g_layout_->addWidget(sb_cols_, 1, 1);
  g_layout_->addWidget(db_box_, 2, 0, 2, 2);

  connect(db_box_, SIGNAL(rejected()), this, SLOT(close()));
  connect(db_box_, SIGNAL(accepted()), this, SLOT(pb_ok_clicked()));
}


void Set_dim_dialog::init_dim(Dim& d)
{
  sb_rows_->setValue(d.first);
  sb_cols_->setValue(d.second);
}


void Set_dim_dialog::pb_ok_clicked()
{
  emit publish_dim_request(std::make_pair(sb_rows_->value(),
                                          sb_cols_->value()));

  this->close();
}
