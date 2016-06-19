/** @file maze_admin.cpp
 *
 * @brief Class to hold responsibility for display maze
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


#include "maze_admin.h"

Maze_admin::Maze_admin(QWidget* parent) :
  QWidget(parent),
  grid_(new QGridLayout(this))
{
  grid_->setSpacing(2);
  grid_->setSizeConstraint(QLayout::SetFixedSize);
}


QGridLayout* Maze_admin::make_maze(const Dim& d)
{
  remove_maze();
  build_maze(d);

  return grid_;
}


QGridLayout* Maze_admin::make_maze(const Map& m)
{
  remove_maze();
  build_maze(m);

  return grid_;
}

void Maze_admin::link_states(Vec_state s)
{
  auto i = 0;

  for(auto& f : fields_)
    f->set_state(s.at(i++));
}


void Maze_admin::build_maze(const Dim& d)
{
  for(auto i = 0; i < d.first; ++i)
  {
    for(auto j = 0; j < d.second; ++j)
    {
      auto f = new Field(Position(std::make_pair(i, j)), 0, this);
      grid_->addWidget(f, i, j);

      connect(this, SIGNAL(enable_responsive(Mode)),
              f, SLOT(set_responsive(Mode)));

      fields_.push_back(f);
    }
  }
}


void Maze_admin::build_maze(const Map& m)
{
  for(auto i = 0; i < m.rows(); ++i)
  {
    for(auto j = 0; j < m.cols(); ++j)
    {
      auto f = new Field(Position(std::make_pair(i, j)), m(i, j), this);

      connect(this, SIGNAL(enable_responsive(Mode)),
              f, SLOT(set_responsive(Mode)));

      connect(this, SIGNAL(disable_responsive()),
              f, SLOT(unset_responsive()));

      connect(f, SIGNAL(report_start_request()),
              this, SLOT(receive_start_request()));

      connect(f, SIGNAL(report_goal_request()),
              this, SLOT(receive_goal_request()));

      connect(f, SIGNAL(report_wall_request()),
              this, SLOT(receive_wall_request()));

      connect(f, SIGNAL(report_unset_wall_request()),
              this, SLOT(receive_unset_wall_request()));

      connect(this, SIGNAL(forward_display(Display, bool)),
              f, SLOT(display(Display, bool)));

      grid_->addWidget(f, i, j);
      fields_.push_back(f);
    }
  }
}


void Maze_admin::remove_maze()
{
  for(auto& f : fields_) //TODO
    delete f;

  fields_.clear();
}


void Maze_admin::enable_responsive_mode(bool b, QString s)
{
  if(b)
  {
    Mode m = Mode::space;

    if(s == "set start")
      m = Mode::start;

    if(s == "set goal")
      m = Mode::goal;

    if(s == "set wall")
      m = Mode::blocked;

    emit enable_responsive(m);
  }
  else
    emit disable_responsive();
}


void Maze_admin::receive_start_request()
{
  if(auto f = qobject_cast<Field*>(sender()))
    emit publish_start(f->get_position());

  emit disable_responsive();
  emit uncheck_button();
}


void Maze_admin::receive_goal_request()
{
  if(auto f = qobject_cast<Field*>(sender()))
    emit publish_goal(f->get_position());

  emit disable_responsive();
  emit uncheck_button();
}


void Maze_admin::receive_wall_request()
{
  if(auto f = qobject_cast<Field*>(sender()))
    emit publish_wall(f->get_position());
}


void Maze_admin::receive_unset_wall_request()
{
  if(auto f = qobject_cast<Field*>(sender()))
    emit publish_unset_wall(f->get_position());
}


void Maze_admin::set_space(Position p)
{
  fields_.at(p.index())->set_mode(Mode::space);
}


void Maze_admin::set_path(Position p)
{
  fields_.at(p.index())->set_mode(Mode::path);
}


void Maze_admin::reset_path()
{
  for(auto& f : fields_)
  {
    if(f->get_mode() == Mode::path)
      f->set_mode(Mode::space);
  }
}


void Maze_admin::set_start(Position p)
{
  fields_.at(p.index())->set_mode(Mode::start);
}


void Maze_admin::update_field(Index i)
{
  fields_.at(i)->refresh_mode();
}

void Maze_admin::display_dispatch(Display d, bool b)
{
  emit forward_display(d, b);
}
