/** @file astar.h
 *
 * @brief Smallest unit in a maze.
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


#ifndef ASTAR_H
#define ASTAR_H


#include "search_strategy.h"


class Astar : public Search_strategy
{

  Q_OBJECT

public:

  explicit Astar(QWidget* parent);
  virtual ~Astar() = default;

  bool search(Graph* graph,
              const Position& start,
              const Position& goal) override;

signals:

  void report_exp_ast(int i);

};

#endif // ASTAR_H
