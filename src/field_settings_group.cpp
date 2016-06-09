/** @file field_settings_group.cpp
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



#include "field_settings_group.h"


Field_settings_group::Field_settings_group(QWidget* parent) :
  QGroupBox(tr("field settings"), parent),

  g_layout_(new QGridLayout(this)),

  cb_g_value_(new QCheckBox(tr("g-value"), this)),
  cb_h_value_(new QCheckBox(tr("h-value"), this)),
  cb_f_value_(new QCheckBox(tr("f-value"), this)),
  cb_rhs_value_(new QCheckBox(tr("rhs-value"), this)),
  cb_expanded_(new QCheckBox(tr("expanded"), this))
{
  g_layout_->setSpacing(4);
  g_layout_->setSizeConstraint(QLayout::SetFixedSize);

  g_layout_->addWidget(cb_g_value_, 0, 0);
  g_layout_->addWidget(cb_h_value_, 1, 0);
  g_layout_->addWidget(cb_f_value_, 2, 0);
  g_layout_->addWidget(cb_rhs_value_, 0, 1);
  g_layout_->addWidget(cb_expanded_, 1, 1);


  this->setLayout(g_layout_);
}

