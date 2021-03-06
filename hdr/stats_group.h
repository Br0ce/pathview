/** @file stats_group.h
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


#ifndef STATS_GROUP_H
#define STATS_GROUP_H

#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>



class Stats_group : public QGroupBox
{

  Q_OBJECT

public:

  explicit Stats_group(QWidget* parent);
  virtual ~Stats_group() = default;

public slots:

  void display_reached(int i);
  void display_status(QString s);
  void display_expanded(int i);
  void reset_display();

private:

  QFormLayout* f_layout_;

  QLineEdit* l_edit_status_;
  QLineEdit* l_edit_expanded_;
  QLineEdit* l_edit_reached_in_;

};

#endif // STATS_GROUP_H
