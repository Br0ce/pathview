/** @file field_settings_group.h
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



#ifndef FIELD_SETTINGS_GROUP_H
#define FIELD_SETTINGS_GROUP_H


#include <QGroupBox>
#include <QGridLayout>
#include <QCheckBox>


#include <defines.h>

class Field_settings_group : public QGroupBox
{

  Q_OBJECT

public:

  explicit Field_settings_group(QWidget* parent);

  virtual ~Field_settings_group() = default;

signals:

  void display_request(Display d, bool b);

public slots:

  void cb_g_value_clicked(int i);
  void cb_h_value_clicked(int i);
  void cb_f_value_clicked(int i);
  void cb_expanded_clicked(int i);

  void set_uncheck();

private:

  QGridLayout* g_layout_;
  QCheckBox* cb_g_value_;
  QCheckBox* cb_h_value_;
  QCheckBox* cb_f_value_;
  QCheckBox* cb_rhs_value_;
  QCheckBox* cb_expanded_;

};

#endif // FIELD_SETTINGS_GROUP_H
