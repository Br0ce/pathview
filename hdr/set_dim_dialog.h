/** @file set_dim_dialog.h
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


#ifndef SET_DIM_DIALOG_H
#define SET_DIM_DIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>

#include "defines.h"

class Set_dim_dialog : public QDialog
{
  Q_OBJECT

public:

  explicit Set_dim_dialog(QWidget* parent = 0);
  virtual ~Set_dim_dialog() = default;

  void init_dim(Dim& d);

signals:

  void publish_dim_request(Dim d);

public slots:

  void pb_ok_clicked();

private:

  QDialogButtonBox* db_box_;

  QSpinBox* sb_rows_;
  QSpinBox* sb_cols_;

  QLabel* l_rows_;
  QLabel* l_cols_;

  QGridLayout* g_layout_;

};

#endif // SET_DIM_DIALOG_H
