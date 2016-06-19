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
  respo_status_(3, false), // 0=start, 1=goal, 2=wall
  displ_status_(5, false),
  /**
   * 0=g-value,
   * 1=h-value,
   * 2=f-value,
   * 3=rhs-value,
   * 4=expanded
   */
  state_(nullptr)
{
  this->setObjectName(QStringLiteral("Field_%1").arg(pos_.index()));

  if(cost > 0)
    mode_ = Mode::blocked;

  init_gui();
}


void Field::init_gui()
{
  this->setFixedSize(80, 80);
  this->setReadOnly(true);
  this->setLineWidth(3);
  this->setFontPointSize(10);
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
    this->setText(get_text());

    if(get_expand_status())
      show_expanded();

    break;

  case Mode::blocked:

    this->setStyleSheet("background-color: black");
    this->setFrameStyle(QFrame::Panel | QFrame::Raised);
    this->clear();
    break;

  case Mode::goal:

    this->setStyleSheet("background-color: red");
    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->setText(get_text());
    break;

  case Mode::start:

    this->setStyleSheet("background-color: green");
    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->setText(get_text());
    break;

  case Mode::path:

    this->setStyleSheet("background-color: blue");
    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->setText(get_text());
    break;


  default:

    this->setStyleSheet("background-color: white");
    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  }
}


void Field::set_state(State* s) { state_ = s; }

Position Field::get_position() const { return pos_; }

bool Field::get_start_status() const { return respo_status_.at(0); }

bool Field::get_goal_status() const { return respo_status_.at(1); }

bool Field::get_wall_status() const { return respo_status_.at(2); }


void Field::set_start_status(const bool b) { respo_status_.at(0) = b; }

void Field::set_goal_status(const bool b) { respo_status_.at(1) = b; }

void Field::set_wall_status(const bool b) { respo_status_.at(2) = b; }


bool Field::get_g_status() const { return displ_status_.at(0); }

bool Field::get_h_status() const { return displ_status_.at(1); }

bool Field::get_f_status() const { return displ_status_.at(2); }

bool Field::get_rhs_status() const { return displ_status_.at(3); }

bool Field::get_expand_status() const { return displ_status_.at(4); }


void Field::set_g_status(const bool b) { displ_status_.at(0) = b; }

void Field::set_h_status(const bool b) { displ_status_.at(1) = b; }

void Field::set_f_status(const bool b) { displ_status_.at(2) = b; }

void Field::set_rhs_status(const bool b) { displ_status_.at(3) = b; }

void Field::set_expand_status(const bool b) { displ_status_.at(4) = b; }


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
  for(std::size_t i = 0; i < respo_status_.size(); ++i)
    respo_status_.at(i) = false;
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

    emit report_goal_request();
  }

  if(get_wall_status() && (get_mode() == Mode::blocked))
  {
    set_mode(Mode::space);

    emit report_unset_wall_request();
  }
  else if(get_wall_status()
          && (!((get_mode() == Mode::start) || (get_mode() == Mode::goal))))
  {
    set_mode(Mode::blocked);

    emit report_wall_request();
  }
}


QString Field::get_text() const
{

  QString tmp;

  if(state_)
  {
    QString t(":");
    QString e("\n");

    if(get_g_status())
    {
      QString g(QString::number(state_->g()));
      tmp.append(QString("%1%2%3%4").arg("g", -4).arg(t).arg(g, 4).arg(e));
    }

    if(get_h_status())
    {
      QString h(QString::number(state_->h()));
      tmp.append(QString("%1%2%3%4").arg("h", -4).arg(t).arg(h, 4).arg(e));
    }

    if(get_f_status())
    {
      QString f(QString::number(state_->f()));
      tmp.append(QString("%1%2%3").arg("f", -4).arg(t).arg(f, 4));
    }

    if(get_rhs_status())
    {
      QString rhs(QString::number(state_->rhs()));
      tmp.append(QString("%1%2%3").arg("rhs", -3).arg(t).arg(rhs, 4));
    }
  }

  return tmp;
}


void Field::show_expanded()
{
  if(state_ && state_->get_expanded())
    this->setStyleSheet("background-color: yellow");
}


void Field::display(Display d, bool b)
{
  switch(d)
  {

  case Display::g_value :

    if(b)
      set_g_status(true);
    else
      set_g_status(false);
    break;

  case Display::h_value :

    if(b)
      set_h_status(true);
    else
      set_h_status(false);
    break;

  case Display::f_value :
    if(b)
      set_f_status(true);
    else
      set_f_status(false);
    break;

  case Display::rhs_value :
    if(b)
      set_rhs_status(true);
    else
      set_rhs_status(false);
    break;

  case Display::expanded :
    if(b)
      set_expand_status(true);
    else
      set_expand_status(false);
    break;

  }

  refresh_mode();
}
