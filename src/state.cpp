/** @file state.cpp
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

#include "state.h"


State::State(Index i, QWidget* parent) :
  QWidget(parent),
  index_(i), // TODO
  pos_(i),
  g_(MAX_WEIGHT),
  h_(0),
  f_(g_ + h_),
  pred_(nullptr),
  expanded_(false) {}


double State::g() const { return g_; }
double State::h() const { return h_; }
double State::f() const { return f_; }


Index State::get_index() const { return pos_.index(); }

Position State::get_position() const { return pos_; }

bool State::get_expanded() const { return expanded_; }

State* State::get_pred() const { return pred_; }


void State::set_g(const double g)
{
  g_ = g;

  emit update();
}


void State::set_h(const double h)
{
  h_ = h;

  emit update();
}

void State::set_f(const double f) // ???
{
  f_ = f;

  emit update();
}


void State::set_expanded()
{
  expanded_ = true;

  emit update();
}


void State::set_pred(State* s) { pred_ = s; }


void State::reset_state()
{
  g_ = MAX_WEIGHT;
  h_ = 0;
  f_ = g_ + h_;
  pred_ = nullptr;
  expanded_ = false;

  emit update();
}
