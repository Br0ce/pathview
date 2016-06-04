/** @file field.h
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


#ifndef FIELD_H
#define FIELD_H

#include <QTextEdit>
#include <QEvent>

#include "defines.h"
#include "position.h"


class Field : public QTextEdit
{

  Q_OBJECT

public:

  explicit Field(const Position& p,
                 const int cost = 0,
                 QWidget* parent = 0);

  virtual ~Field() = default;

  void init_gui();
  void set_mode(const Mode& m);
  Mode get_mode() const;
  void refresh_mode();

protected:

  void mousePressEvent(QMouseEvent* m) override;

private:

  Position pos_;
  Mode mode_;

};

#endif // FIELD_H
