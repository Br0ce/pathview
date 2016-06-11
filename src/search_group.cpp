/** @file search_group.cpp
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



#include "search_group.h"


Search_group::Search_group(QWidget* parent) :

  QGroupBox(tr("search"), parent),

  g_layout_(new QGridLayout(this)),
  pb_search_(new QPushButton(tr("search path"), parent)),
  pb_go_(new QPushButton(tr("go"), parent)),
  pb_pause_(new QPushButton(tr("pause"), parent)),

  search_combo_(new QComboBox(parent))
{
  search_combo_->addItem(tr("Breadth first"));
  search_combo_->addItem(tr("Depth first"));
  search_combo_->addItem(tr("A*"));
  search_combo_->addItem(tr("D*-light"));

  g_layout_->setSpacing(4);
  g_layout_->setSizeConstraint(QLayout::SetFixedSize);

  g_layout_->addWidget(search_combo_, 0, 0, 2, 2);
  g_layout_->addWidget(pb_search_, 2, 0, 2, 2);
  g_layout_->addWidget(pb_go_, 4, 0, 1, 1);
  g_layout_->addWidget(pb_pause_, 4, 1, 1, 1);

  connect(search_combo_, SIGNAL(currentIndexChanged(QString)),
          this, SLOT(search_mode(QString)));

  this->setLayout(g_layout_);
}


void Search_group::search_mode(QString s)
{
  // TODO dummy
  if(s == "Breadth first")
    qDebug() << "Breadth first";
  if(s == "Depth first")
    qDebug() << "Depth first";
  if(s == "A*")
    qDebug() << "A*";
  if(s == "D*-light")
    qDebug() << "D*-light";
}
