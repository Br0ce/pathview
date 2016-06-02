/** @file position.cpp
 *
 *
 * @brief Type to get Index - handling right
 *
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


#include "position.h"



Dim Position::dimension_;

Position::Position(const Index& i) :
  index_(i)
{
  if(!valid_position(index_))
    throw Pathview_error("Position is not valid");
}


Position::Position(const Dim& p) :
  index_((p.first * dimension_.second) + p.second)
{
  if(!valid_position(index_))
    throw Pathview_error("Position is not valid");
}


Position::Position(Dim&& p) :
  index_((p.first * dimension_.second) + p.second)
{
  if(!valid_position(index_))
    throw Pathview_error("Position is not valid");
}

bool Position::valid_position(const Index& i) const
{
  if(dimension_.first == 0 || dimension_.second == 0)
    throw Pathview_error("First set maze dimension");

  return ((i >= 0) && (i < (dimension_.first * dimension_.second)));
}


bool Position::valid_position(const Dim& pos) const
{
  if(dimension_.first == 0 || dimension_.second == 0)
    throw Pathview_error("First set maze dimension");

  if(((pos.first >= 0) && (pos.first <= dimension_.first))
      && ((pos.second >= 0) && (pos.second <= dimension_.second)))
    return true;
  else
    return false;
}


Index Position::index() const { return index_; }


Dim Position::position() const
{
  return std::make_pair(std::floor(index_ / dimension_.second),
                        (index_ % dimension_.second));
}


void Position::set_cols(int c) { dimension_.second = c; }

void Position::set_rows(int r) { dimension_.first = r; }

void Position::set_dimensions(const Dim& d) { dimension_ = d; }

void Position::set_dimensions(Dim&& d) { dimension_ = std::move(d); }


