/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  <copyright holder> <email>
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

#ifndef SEARCH_STRATEGY_H
#define SEARCH_STRATEGY_H

#include <queue>


#include <QWidget>


#include "defines.h"
#include "position.h"
#include "graph.h"


class Search_strategy : public QWidget
{
public:

  template<typename T>
  using prio_queue = std::priority_queue<State*, Vec_state, T>;


  Search_strategy(QWidget* parent) : QWidget(parent) {}
  virtual ~Search_strategy() = default;


  virtual bool search(Graph* graph,
                      const Position& start,
                      const Position& goal) = 0;
};

#endif // SEARCH_STRATEGY_H
