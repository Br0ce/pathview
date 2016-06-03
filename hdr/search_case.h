/** @file search_case.h
 *
 * @brief
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


#ifndef SEARCH_CASE_H
#define SEARCH_CASE_H

#include <QWidget>

#include "defines.h"
#include "maze_admin.h"
#include "graph.h"
#include "position.h"


class Search_case : public QWidget
{

  Q_OBJECT

public:

  explicit Search_case(Maze_admin* maze, QWidget* parent = 0);
  virtual ~Search_case() = default;

private:

  Maze_admin* maze_;
  Graph* graph_;
  Map map_;

};

#endif // SEARCH_CASE_H
