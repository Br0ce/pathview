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


QGridLayout* Maze_admin::make_maze(Dim d)
{
  for(auto i = 0; i < d.first; ++i)
  {
    for(auto j = 0; j < d.second; ++j)
    {
      auto f = new Field(Position(std::make_pair(i, j)), this);
      grid_->addWidget(f, i, j);
      fields_.push_back(f); //TODO needed?
    }
  }
  return grid_;
}

void Maze_admin::remove_maze()
{
  auto all_fields = this->findChildren<Field*>();
  for(auto& f : all_fields)
    delete f;
  all_fields.clear();
}