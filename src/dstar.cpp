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

  auto s = graph->get_state(start);
  s->set_rhs(MAX_WEIGHT);
  s->set_g(MAX_WEIGHT);

  auto g = graph->get_state(goal);
  auto g_elem = std::find(open_.begin(), open_.end(), g);
  if(g_elem == open_.end())
  {
    g->set_rhs(0);
    g->set_g(MAX_WEIGHT);
    open_.push_back(g);
  }
  g->set_h(graph->get_h(start, g->get_position()));


  auto current = g;

  auto search_limit = graph->get_states().size() * 2;

  std::size_t cnt = 0;
  while((current->get_key() < s->get_key()) || (s->rhs() != s->g()))
  {
    if(cnt > search_limit)
    {
      emit report_exp_dst(cnt);
      return false;
    }

    ++cnt;
    current->set_expanded();

    if(current->g() > current->rhs())
    {
      current->set_g(current->rhs());
      for(auto& pred : graph->get_succ(current)) // succ = pred
        update_state(pred, start, goal, graph);
    }
    else
    {
      current->set_g(MAX_WEIGHT);
      update_state(current, start, goal, graph);
      for(auto& pred : graph->get_succ(current)) // succ = pred
        update_state(pred, start, goal, graph);
    }

    auto it_elem = std::find(open_.begin(), open_.end(), current);
    if(it_elem != open_.end())
      open_.erase(it_elem);

    current = *(std::min_element(open_.begin(),
                                 open_.end(),
                                 [](State * l, State * r)
    { return l->get_key() < r->get_key(); }));

  }

  emit report_exp_dst(cnt);

  return true;
}


void Dstar::update_state(State* s,
                         const Position& start,
                         const Position& goal,
                         Graph* graph)
{
  if(!s->get_expanded())
    s->set_g(MAX_WEIGHT);

  if(s->get_position() != goal)
  {
    auto tmp_rhs = s->rhs();
    for(auto& succ : graph->get_succ(s))
    {
      if(tmp_rhs > (succ->g() + graph->get_c(succ, s)))
      {
        tmp_rhs = succ->g() + graph->get_c(succ, s);
      }
    }
    s->set_rhs(tmp_rhs);
  }

  auto it_elem = std::find(open_.begin(), open_.end(), s);
  if(it_elem != open_.end())
    open_.erase(it_elem);

  if(s->g() != s->rhs())
  {
    s->set_h(graph->get_h(start, s->get_position()));
    open_.push_back(s);
  }
}
