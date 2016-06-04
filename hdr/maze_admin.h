/** @file maze_admin.h
 *
 * @brief Class to hold responsibility for display maze
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

#ifndef MAZE_ADMIN_H
#define MAZE_ADMIN_H


#include <QWidget>
#include <QGridLayout>


#include "defines.h"
#include "position.h"
#include "field.h"



class Maze_admin : public QWidget
{

  Q_OBJECT

public:

  explicit Maze_admin(QWidget* parent = 0);
  virtual ~Maze_admin() = default;

  QGridLayout* make_maze(const Dim& d); // TODO not needed
  QGridLayout* make_maze(const Map& m);


private:

  void build_maze(const Dim& d); // TODO needed?
  void build_maze(const Map& m);
  void remove_maze();

  QGridLayout* grid_;
  QList<Field*> fields_; //TODO needed?

};

#endif // MAZE_ADMIN_H
