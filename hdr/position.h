/** @file position.h
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


#ifndef POSITION_H
#define POSITION_H

#include <utility>
#include <cmath>
#include <stdexcept>

#include "defines.h"
#include "helper.h"



class Position
{
public:

  explicit Position(const Index& i);
  explicit Position(const Dim& p);
  explicit Position(Dim&& p);

  static void set_rows(int r);
  static void set_cols(int c);
  static void set_dimensions(const Dim& d);
  static void set_dimensions(Dim&& d);

  Index index() const;
  Dim position() const;

private:

  bool valid_position(const Index& i) const;
  bool valid_position(const Dim& pos) const;

  Index index_;
  static Dim dimension_;

};

#endif // POSITION_H
