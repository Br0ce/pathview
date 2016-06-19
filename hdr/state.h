/** @file state.h
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


#ifndef STATE_H
#define STATE_H

#include <iostream> // TODO


#include <QWidget>


#include "defines.h"
#include "position.h"



class State : public QWidget
{

  Q_OBJECT

public:

  State(Index i, QWidget* parent = 0);
  virtual ~State() = default;


  friend bool operator==(const State& l, const State& r);

  double g() const;//TODO get_g
  double h() const;
  double f() const;
  double rhs() const;

  Index get_index() const;
  Position get_position() const;
  bool get_expanded() const;
  State* get_pred() const;

  void set_g(const double g);
  void set_h(const double h);
  void set_f(const double f);
  void set_rhs(const double rhs);
  void set_expanded();
  void set_pred(State* s);

  void reset_state();

signals:

  void update();

private:

  Index index_; // TODO
  Position pos_;
  double g_; //TODO
  double h_;
  double f_;
  double rhs_;
  State* pred_;
  bool expanded_;

};


inline bool operator==(const State& l, const State& r)
{ return (l.pos_ == r.pos_); }


inline bool operator!=(const State& l, const State& r)
{ return !(l == r); }


#endif // STATE_H
