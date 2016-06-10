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


void Graph::init_4_neighborhood(const Map& m)
{
  int cnt = m.rows() * m.cols();

  /*
  states_.resize(cnt, new State(this));

  for(auto& s : states_)
    connect(s, SIGNAL(update()), this, SLOT(state_update()));
  */

  states_.clear();

  for(auto i = 0; i < cnt; ++i)
  {
    auto s = new State(i, this);
    connect(s, SIGNAL(update()), this, SLOT(state_update()));
    states_.push_back(s);
  }

  Eigen::MatrixXd e(cnt, cnt);
  e.setZero();
  edges_ = std::move(e);

  for(int i = 0; i < cnt; ++i) // i is 0_index
  {
    Position p(i);

    if(p.check_right_succ())
    {
      edges_(i, i + 1) = get_edge_weight(m(p.right_succ().first,
                                           p.right_succ().second));
    }

    if(p.check_left_succ())
    {
      edges_(i, i - 1) = get_edge_weight(m(p.left_succ().first,
                                           p.left_succ().second));
    }

    if(p.check_upper_succ())
    {
      edges_(i, i - m.cols()) = get_edge_weight(m(p.upper_succ().first,
                                p.upper_succ().second));
    }

    if(p.check_lower_succ())
    {
      edges_(i, i + m.cols()) = get_edge_weight(m(p.lower_succ().first,
                                p.lower_succ().second));
    }
  }
}


double Graph::get_edge_weight(const double d) const
{
  if(d == 0)
    return 1;
  else
    return d;
}


void Graph::add_wall(const Position& p)
{
  edges_.col(p.pos().second) *= MAX_WEIGHT;
}


void Graph::remove_wall(const Position& p)
{
  for(int i = 0; i < edges_.rows(); ++i)
  {
    if(edges_(i, p.pos().second) > 1)
      edges_(i, p.pos().second) = 1;
  }
}


std::vector<State*> Graph::get_states() { return states_; }


void Graph::state_update()
{
  if(auto s = qobject_cast<State*>(sender()))
    emit update_state(s->get_index());
}
