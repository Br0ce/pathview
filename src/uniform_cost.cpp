/** @file uniform_cost.cpp
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



#include "uniform_cost.h"


Uniform_cost::Uniform_cost(QWidget* parent) :
  Search_strategy(parent) {}


bool Uniform_cost::search(Graph* graph,
                          const Position& start,
                          const Position& goal)
{
  auto greater_g = [](State * l, State * r) { return l->g() > r->g(); };

  prio_queue<decltype(greater_g)> open(greater_g);

  graph->reset_all_states();

  auto s = graph->get_state(start);
  s->set_g(0);

  open.push(s);

  int cnt = 0;

  while(!open.empty())
  {
    auto current = open.top();

    if(current->get_position() == goal)
    {
      emit report_exp_uni(cnt);
      return true;
    }

    ++cnt;
    current->set_expanded();

    for(auto& succ : graph->get_succ(current))
    {

      if(succ->g() > current->g() + graph->get_c(current, succ))
      {
        succ->set_g(current->g() + graph->get_c(current, succ));
        succ->set_pred(current);
        open.push(succ);
      }
    }
    open.pop();
  }

  emit report_exp_uni(cnt);
  return false;
}
