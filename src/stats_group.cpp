/** @file stats_group.cpp
 *
 *
 * @brief
 *
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


#include "stats_group.h"


Stats_group::Stats_group(QWidget* parent) :
  QGroupBox(tr("stats"), parent),

  f_layout_(new QFormLayout(this)),
  l_edit_status_(new QLineEdit(this)),
  l_edit_expanded_(new QLineEdit(this)),
  l_edit_reached_in_(new QLineEdit(this))
{
  l_edit_status_->setReadOnly(true);
  l_edit_status_->setAlignment(Qt::AlignRight);

  l_edit_expanded_->setReadOnly(true);
  l_edit_expanded_->setAlignment(Qt::AlignRight);

  l_edit_reached_in_->setReadOnly(true);
  l_edit_reached_in_->setAlignment(Qt::AlignRight);

  f_layout_->setSpacing(4);
  f_layout_->setSizeConstraint(QLayout::SetFixedSize);

  f_layout_->addRow(tr("status"), l_edit_status_);
  f_layout_->addRow(tr("expanded"), l_edit_expanded_);
  f_layout_->addRow(tr("reached in"), l_edit_reached_in_);

  this->setLayout(f_layout_);
}


void Stats_group::display_reached(int i)
{
  if(i >= 0)
    l_edit_reached_in_->setText(QString::number(i));
  else
    l_edit_reached_in_->setText("--");
}


void Stats_group::display_status(QString s)
{
  l_edit_status_->setText(s);
}


void Stats_group::display_expanded(int i)
{
  l_edit_expanded_->setText(QString::number(i));
}
