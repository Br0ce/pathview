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

#include <vector>
#include <memory>

#include <Eigen/Dense>

#include "defines.h"
#include "state.h"


class Graph
{

public:
  explicit Graph(dim d);

  void init_4_neighorhood();

  inline bool check_right_bound(int i);
  inline bool check_left_bound(int i);
  inline bool check_upper_bound(int i);
  inline bool check_lower_bound(int i);

private:

  std::vector<std::shared_ptr<State>> states_;
  Eigen::MatrixXd edges_;
  dim dim_;

};

#endif // GRAPH_H
