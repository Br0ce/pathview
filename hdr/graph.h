/** @file graph.h
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


#ifndef GRAPH_H
#define GRAPH_H

#include <iostream> // for testing eigen

#include <vector>
#include <memory>


#include <QWidget>


#include "defines.h"
#include "state.h"
#include "position.h"


class Graph : public QWidget
{

  Q_OBJECT

public:

  explicit Graph(QWidget* parent = 0);

  virtual ~Graph() = default;

  void init_4_neighborhood(const Map& m);

  void add_wall(const Position& p);
  void remove_wall(const Position& p);

  Vec_state get_states();
  State* get_state(const Position& p) const;

  Vec_state get_succ(const Position& p) const;
  Vec_state get_succ(const State* s) const;

  double get_c(const State* a, const State* b) const;
  double get_h(const Position& a, const Position& b) const;

  void reset_all_states();

signals:

  void update_state(Index i);

public slots:

  void state_update();

private:

  Vec_state states_;
  Matrix_d edges_;

  double make_edge_weight(const double d) const;
};

#endif // GRAPH_H
