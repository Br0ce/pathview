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


#include <Eigen/Dense>

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

  double get_edge_weight(const double d) const;
  void add_wall(const Position& p);
  void remove_wall(const Position& p);
  std::vector<State*> get_states();

signals:

  void update_state(Index i);

public slots:

  void state_update();

private:

  std::vector<State*> states_;
  Eigen::MatrixXd edges_;

};

#endif // GRAPH_H
