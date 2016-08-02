/** @file search_group.h
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



#ifndef SEARCH_GROUP_H
#define SEARCH_GROUP_H


#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>

#include "defines.h"


class Search_group : public QGroupBox
{

  Q_OBJECT

public:

  explicit Search_group(QWidget* parent);
  virtual ~Search_group() = default;

public slots:

  void pb_search_clicked();
  void cb_search_combo_changed(QString s);
  void pb_clear_clicked();
  void pb_go_clicked();

signals:

  void search_clicked();
  void search_mode_change(QString s);
  void clear_clicked();
  void go_clicked();

private:

  QGridLayout* g_layout_;

  QPushButton* pb_search_;
  QPushButton* pb_go_;
  QPushButton* pb_clear_;

  QComboBox* search_combo_;

};

#endif // SEARCH_GROUP_H
