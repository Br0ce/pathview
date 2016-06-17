/** @file astar.cpp
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


#include "astar.h"


Astar::Astar(QWidget* parent) :
  Search_strategy(parent) {}


bool Astar::search(Graph* graph,
                   const Position& start,
                   const Position& goal)
{
  auto greater_f = [](State * l, State * r) { return l->f() > r->f(); };

  prio_queue<decltype(greater_f)> open(greater_f);

  graph->reset_all_states();

  auto s = graph->get_state(start);
  s->set_g(0);
  s->set_h(graph->get_h(start, goal));
  s->set_f(s->g() + s->h());

  open.push(s);

  int cnt = 0;

  while(!open.empty())
  {
    auto current = open.top();

    if(current->get_position() == goal)
    {
      emit report_exp_ast(cnt);
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
        succ->set_h(graph->get_h(succ->get_position(), goal));
        succ->set_f(succ->g() + succ->h());
        open.push(succ);
      }
    }
    open.pop();
  }

  emit report_exp_ast(cnt);
  return false;
}
