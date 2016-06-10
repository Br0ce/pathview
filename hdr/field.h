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


#include <vector>


#include <QTextEdit>
#include <QEvent>


#include "defines.h"
#include "position.h"
#include "state.h"


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

  void set_state(State* s);

  Position get_position() const;

  bool get_start_status() const;
  bool get_goal_status() const;
  bool get_wall_status() const;

  void set_start_status(const bool b);
  void set_goal_status(const bool b);
  void set_wall_status(const bool b);


  bool get_g_status() const;
  bool get_h_status() const;
  bool get_f_status() const;

  void set_g_status(const bool b);
  void set_h_status(const bool b);
  void set_f_status(const bool b);

  QString get_text() const;

signals:

  void report_start_request();
  void report_goal_request();
  void report_wall_request();
  void report_unset_wall_request();

public slots:

  void set_responsive(Mode m);
  void unset_responsive();
  void refresh_mode();
  void display(Display d, bool b);

protected:

  void mousePressEvent(QMouseEvent* m) override;

private:

  Position pos_;
  Mode mode_;
  std::vector<bool> respo_status_;
  std::vector<bool> displ_status_;
  State* state_;

};

#endif // FIELD_H
