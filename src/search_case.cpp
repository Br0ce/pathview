/** @file maze_admin.h
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


#include "search_case.h"


Search_case::Search_case(Maze_admin* maze_ad, QWidget* parent) :
  QWidget(parent),
  maze_(maze_ad) {}

/*
void Search_case::resize_map(const Dim& d)
{
  Position::set_dimensions(d);
  map_.resize(d.first, d.second);
}

void Search_case::resize_map(Dim&& d)
{
  Position::set_dimensions(d);
  map_.resize(d.first, d.second);
}
*/


Dim Search_case::map_size() const
{
  return std::make_pair(map_.rows(), map_.cols());
}
