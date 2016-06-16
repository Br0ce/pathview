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


Graph::Graph(QWidget* parent) :
  QWidget(parent) {}


void Graph::init_4_neighborhood(const Map& m) //TODO CHECK FOR get_succ()
{
  const int cnt = m.rows() * m.cols();

  states_.clear();

  for(auto i = 0; i < cnt; ++i)
  {
    auto s = new State(i, this);
    connect(s, SIGNAL(update()), this, SLOT(state_update()));
    states_.push_back(s);
  }

  Eigen::MatrixXd e(cnt, cnt); //TODO resize
  e.setZero();
  edges_ = std::move(e);

  for(int i = 0; i < cnt; ++i) // i is 0_index
  {
    Position p(i);

    if(p.check_right_succ())
    {
      edges_(i, i + 1) = make_edge_weight(m(p.right_succ().first,
                                            p.right_succ().second));
    }

    if(p.check_left_succ())
    {
      edges_(i, i - 1) = make_edge_weight(m(p.left_succ().first,
                                            p.left_succ().second));
    }

    if(p.check_upper_succ())
    {
      edges_(i, i - m.cols()) = make_edge_weight(m(p.upper_succ().first,
                                p.upper_succ().second));
    }

    if(p.check_lower_succ())
    {
      edges_(i, i + m.cols()) = make_edge_weight(m(p.lower_succ().first,
                                p.lower_succ().second));
    }
  }
}


double Graph::make_edge_weight(const double d) const
{
  if(d == 0)
    return 1;
  else
    return d;
}


void Graph::add_wall(const Position& p)
{
  const int max = edges_.rows();
  for(int i = 0; i < max; ++i)
  {
    if(edges_(i, p.index()) > 0)
      edges_(i, p.index()) = MAX_WEIGHT;
  }
}


void Graph::remove_wall(const Position& p)
{
  const int max = edges_.rows();
  for(int i = 0; i < max; ++i)
  {
    if(edges_(i, p.index()) > 1)
      edges_(i, p.index()) = 1;
  }
}


Vec_state Graph::get_states() { return states_; }


void Graph::state_update()
{
  if(auto s = qobject_cast<State*>(sender()))
    emit update_state(s->get_index());
}


State* Graph::get_state(const Position& p) const
{
  return states_.at(p.index());
}


Vec_state Graph::get_succ(const Position& p) const
{
  Vec_state tmp;

  const int max = states_.size();

  for(int i = 0; i < max; ++i)
  {
    if(edges_(p.index(), i) > 0)
      tmp.push_back(states_.at(i));
  }
  return tmp;
}


Vec_state Graph::get_succ(const State* s) const
{
  return get_succ(s->get_position());
}



double Graph::get_c(const State* a, const State* b) const
{
  return edges_(a->get_index(), b->get_index());
}
