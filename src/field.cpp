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

#include "field.h"



Field::Field(const Position& p, const int cost, QWidget* parent) :
  QTextEdit(parent),
  pos_(p),
  mode_(Mode::space),
  status_(3, false) // 0=start, 1=goal, 2=wall
{
  this->setObjectName(QStringLiteral("Field_%1").arg(pos_.index()));

  if(cost > 0)
    mode_ = Mode::blocked;

  init_gui();
}


void Field::init_gui()
{
  this->setFixedSize(60, 60);
  this->setReadOnly(true);
  this->setLineWidth(3);
  refresh_mode();
}


void Field::set_mode(const Mode& m)
{
  mode_ = m;
  refresh_mode();
}

Mode Field::get_mode() const { return mode_; }

void Field::refresh_mode()
{
  switch(mode_)
  {
  case Mode::space:

    this->setStyleSheet("background-color: white");
    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    break;

  case Mode::blocked:

    this->setStyleSheet("background-color: black");
    this->setFrameStyle(QFrame::Panel | QFrame::Raised);
    break;

  case Mode::start:

    this->setStyleSheet("background-color: red");
    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    break;

  case Mode::goal:

    this->setStyleSheet("background-color: green");
    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    break;

  case Mode::path:

    this->setStyleSheet("background-color: blue");
    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    break;

  case Mode::expanded:

    this->setStyleSheet("background-color: yellow");
    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    break;

  default:

    this->setStyleSheet("background-color: white");
    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  }
}


Position Field::get_position() const { return pos_; }

bool Field::get_start_status() const { return status_.at(0); }

bool Field::get_goal_status() const { return status_.at(1); }

bool Field::get_wall_status() const { return status_.at(2); }

void Field::set_start_status(const bool b) { status_.at(0) = b; }

void Field::set_goal_status(const bool b) { status_.at(1) = b; }

void Field::set_wall_status(const bool b) { status_.at(2) = b; }


void Field::set_responsive(Mode m)
{
  switch(m)
  {

  case Mode::start :
    set_start_status(true);
    break;

  case Mode::goal :
    set_goal_status(true);
    break;

  case Mode::blocked:
    set_wall_status(true);

  default:
    // TODO
    break;

  }
}


void Field::unset_responsive()
{
  for(std::size_t i = 0; i < status_.size(); ++i)
    status_.at(i) = false;
}



void Field::mousePressEvent(QMouseEvent* m)
{
  QTextEdit::mousePressEvent(m);

  if(get_start_status() && (get_mode() != Mode::blocked))
  {
    set_mode(Mode::start);
    set_start_status(false);

    emit report_start_request();
  }

  if(get_goal_status() && (get_mode() != Mode::blocked))
  {
    set_mode(Mode::goal);
    set_goal_status(false);

    emit report_goal_request(); // TODO dummy
  }

  if(get_wall_status() && (get_mode() == Mode::blocked))
    set_mode(Mode::space);
  else if(get_wall_status()
          && (!((get_mode() == Mode::start) || (get_mode() == Mode::goal))))
    set_mode(Mode::blocked);
}
