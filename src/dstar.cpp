/** @file dstar.cpp
 *
 * @brief Smallest unit in a maze.
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


#include "dstar.h"


Dstar::Dstar(QWidget* parent) :
  Search_strategy(parent) {}


bool Dstar::search(Graph* graph,
                   const Position& start,
                   const Position& goal)
{
  /*
  auto greater_k = [](State* l, State* r)
  {
    return std::tie(std::min(l->g(), l->rhs() + l->h()),
                    std::min(l->g(), l->rhs())) >
           std::tie(std::min(r->g(), r->rhs() + r->h()),
                    std::min(r->g(), r->rhs()));
  };

  prio_queue<decltype(greater_k)> open(greater_k);

  auto s = graph->get_state(start);
  s->set_g(MAX_WEIGHT);
  s->set_rhs(MAX_WEIGHT);

  auto g = graph->get_state(goal);
  g->set_g(MAX_WEIGHT);
  g->set_rhs(0);

  open.push(g);
  */

  return false;
}
