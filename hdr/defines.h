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



#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
#define QT_VERSION_5_4_REACHED
#endif

#define __LOG__FUNC \
  qDebug() << Q_FUNC_INFO;

#define __LOG(msg) \
  qDebug() << Q_FUNC_INFO << "in Line" << __LINE__ << ":" << msg;


using Dim = std::pair<int, int>;
using Index = int;

#endif // DEFINES_H
