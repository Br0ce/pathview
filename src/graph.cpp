/** @file graph.cpp
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



#include "graph.h"


Graph::Graph(dim d) :
  states_((d.first * d.second), std::make_shared<State>(d.first * d.second)),
  edges_((d.first * d.second), (d.first * d.second)), //TODO test for zero init
  dim_(d)
{
  init_4_neighorhood();
}


void Graph::init_4_neighorhood()
{
  for(std::size_t i = 0; i < states_.size(); ++i)
  {
    if(check_right_bound(i))
      edges_(i, i + 1) = 1;

    if(check_left_bound(i))
      edges_(i, i - 1) = 1;

    if(check_upper_bound(i))
      edges_(i, i - dim_.second) = 1;

    if(check_lower_bound(i))
      edges_(i, i + dim_.second) = 1;
  }
}

bool Graph::check_right_bound(int i)
{
  return ((i % dim_.second) + 1) < dim_.second;
}

bool Graph::check_left_bound(int i)
{
  return ((i % dim_.second) - 1) >= dim_.second;
}

bool Graph::check_upper_bound(int i)
{
  return (i - dim_.second) >= 0;
}

bool Graph::check_lower_bound(int i)
{
  return (i + dim_.second) < (dim_.first * dim_.second);
}
