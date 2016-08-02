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
#include <algorithm>


#include <QWidget>
#include <QFileDialog>
#include <QSettings>
#include <QGridLayout>


#include "defines.h"
#include "maze_admin.h"
#include "graph.h"
#include "position.h"
#include "search_strategy.h"
#include "uniform_cost.h"
#include "astar.h"
#include "dstar.h"


class Search_case : public QWidget
{

  Q_OBJECT

public:

  explicit Search_case(Maze_admin* maze_ad, QWidget* parent = 0);
  virtual ~Search_case(); // = default;


  void set_strategy(Search_strategy* strategy);

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
  Position get_next() const;

  bool start_status() const;
  bool goal_status() const;
  bool dstar_status() const;

  void set_start_status(bool b);
  void set_goal_status(bool b);
  void set_dstar_status(bool b);

  void show_path();

signals:

  void refresh_maze(QGridLayout* l);
  void unset(Position p);
  void stats_reached(int i);
  void stats_status(QString s);
  void stats_expanded(int i);

public slots:

  void load_maze();
  void save_maze();
  void start_request(Position p);
  void goal_request(Position p);
  void wall_request(Position p);
  void unset_wall_request(Position p);
  void change_search_mode(QString s);
  void start_search();
  void receive_expanded(int i);
  void reset_maze();
  void exec_go();

private:

  Maze_admin* maze_ad_;
  Graph* graph_;
  Map map_;
  Uniform_cost* uni_cost_;
  Astar* astar_;
  Dstar* dstar_;
  Search_strategy* strategy_;
  Position start_;
  Position goal_;
  Position next_;
  Position next_dstar_;
  Vec_bool status_;

};

#endif // SEARCH_CASE_H
