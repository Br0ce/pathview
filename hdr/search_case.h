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

#include <fstream>


#include <QWidget>
#include <QFileDialog>
#include <QSettings>
#include <QGridLayout>


#include "defines.h"
#include "maze_admin.h"
#include "graph.h"
#include "position.h"


class Search_case : public QWidget
{

  Q_OBJECT

public:

  explicit Search_case(Maze_admin* maze_ad, QWidget* parent = 0);
  virtual ~Search_case() = default;

  /*
  void resize_map(const Dim& d); //TODO avoid overload
  void resize_map(Dim&& d);
  */

  template<typename T>
  void resize_map(T&& d)
  {
    map_.resize(d.first, d.second);
    Position::set_dimensions(std::forward<T>(d));
  }

  QGridLayout* get_maze_layout();

  Dim map_size() const;

  template<typename T>
  void set_start(T&& p) { start_ = std::forward<T>(p); }

  template<typename T>
  void set_goal(T&& p) { goal_ = std::forward<T>(p); }

  Position get_start() const;
  Position get_goal() const;

signals:

  void refresh_maze(QGridLayout* l);

public slots:

  void load_maze();
  void start_request(Position p);
  void goal_request(Position p);

private:

  Maze_admin* maze_ad_;
  Graph* graph_;
  Map map_;
  Position start_;
  Position goal_;

};

#endif // SEARCH_CASE_H
