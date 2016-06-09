/** @file maze_group.h
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


#ifndef MAZE_GROUP_H
#define MAZE_GROUP_H

#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>

#include <defines.h>

class Maze_group : public QGroupBox
{

  Q_OBJECT

public:

  explicit Maze_group(QWidget* parent);

  virtual ~Maze_group() = default;


signals:

  void load_maze_clicked(bool);
  void save_maze_clicked(bool);
  void set_button_clicked(bool, QString);
  void set_dim_clicked(bool);

public slots:

  void pb_load_maze_clicked(bool b);
  void pb_save_maze_clicked(bool b);
  void pb_set_start_clicked(bool b);
  void pb_set_goal_clicked(bool b);
  void pb_set_dim_clicked(bool b);
  void pb_set_wall_clicked(bool b);
  void uncheck_set_button();

private:

  QGridLayout* g_layout_;

  QPushButton* pb_load_maze_;
  QPushButton* pb_save_maze_;
  QPushButton* pb_set_start_;
  QPushButton* pb_set_goal_;
  QPushButton* pb_set_wall_;
  QPushButton* pb_set_dim_;

  void exclusiv(const QPushButton* p); // TODO make varidic template
};

#endif // MAZE_GROUP_H
