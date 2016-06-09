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

      grid_->addWidget(f, i, j);
      fields_.push_back(f);
    }
  }
}


void Maze_admin::remove_maze()
{
  for(auto f : fields_)
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
}


void Maze_admin::receive_start_request()
{
  if(auto f = qobject_cast<Field*>(sender()))
    emit publish_start(f->get_position());

  emit disable_responsive();
  emit uncheck_button();
  //TODO uncheck old start
}


void Maze_admin::receive_goal_request()
{
  if(auto f = qobject_cast<Field*>(sender()))
    emit publish_goal(f->get_position());

  emit disable_responsive();
  emit uncheck_button();
  //TODO uncheck old goal
}


void Maze_admin::set_space(Position p)
{
  auto f = fields_.at(p.index());
  f->set_mode(Mode::space);
}

