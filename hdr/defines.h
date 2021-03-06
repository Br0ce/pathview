/** @file defines.h
 *
 * @brief collection of defines
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


#ifndef DEFINES_H
#define DEFINES_H

#include <QDebug>


#include <utility>

#include <Eigen/Dense>


#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
#define QT_VERSION_5_4_REACHED
#endif

#define __LOG__FUNC \
  qDebug() << Q_FUNC_INFO;

#define __LOG(msg) \
  qDebug() << Q_FUNC_INFO << "in Line" << __LINE__ << ":" << msg;


#define MAX_WEIGHT 10000

class State;

using Dim = std::pair<int, int>;
using Key = std::pair<double, double>;
using Index = int;
using Map = Eigen::MatrixXi;
using Matrix_d = Eigen::MatrixXd;
using Vec_state = std::vector<State*>;
using Vec_bool = std::vector<bool>;


enum class Mode { space,
                  blocked,
                  start,
                  goal,
                  path
                };

enum class Display { g_value,
                     h_value,
                     f_value,
                     rhs_value,
                     expanded
                   };

#endif // DEFINES_H
