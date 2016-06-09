/** @file maze_group.cpp
 *
 *
 * @brief
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


#include "maze_group.h"


Maze_group::Maze_group(QWidget* parent) :
  QGroupBox(tr("maze builder"), parent),

  g_layout_(new QGridLayout(this)),

  pb_load_maze_(new QPushButton(tr("load map"), this)),
  pb_save_maze_(new QPushButton(tr("save map"), this)),
  pb_set_start_(new QPushButton(tr("set start"), this)),
  pb_set_goal_(new QPushButton(tr("set goal"), this)),
  pb_set_wall_(new QPushButton(tr("set wall"), this)),
  pb_set_dim_(new QPushButton(tr("set dim"), this))
{
  connect(pb_load_maze_, SIGNAL(clicked(bool)),
          this, SLOT(pb_load_maze_clicked(bool)));

  connect(pb_save_maze_, SIGNAL(clicked(bool)),
          this, SLOT(pb_save_maze_clicked(bool)));

  connect(pb_set_start_, SIGNAL(clicked(bool)),
          this, SLOT(pb_set_start_clicked(bool)));

  connect(pb_set_goal_, SIGNAL(clicked(bool)),
          this, SLOT(pb_set_goal_clicked(bool)));

  connect(pb_set_wall_, SIGNAL(clicked(bool)),
          this , SLOT(pb_set_wall_clicked(bool)));

  connect(pb_set_dim_, SIGNAL(clicked(bool)),
          this, SLOT(pb_set_dim_clicked(bool)));


  pb_set_start_->setCheckable(true);
  pb_set_goal_->setCheckable(true);
  pb_set_wall_->setCheckable(true);

  g_layout_->setSpacing(4);
  g_layout_->setSizeConstraint(QLayout::SetFixedSize);

  g_layout_->addWidget(pb_load_maze_, 0, 0);
  g_layout_->addWidget(pb_save_maze_, 0, 1);
  g_layout_->addWidget(pb_set_start_, 1, 0);
  g_layout_->addWidget(pb_set_goal_, 1, 1);
  g_layout_->addWidget(pb_set_dim_, 2, 0);
  g_layout_->addWidget(pb_set_wall_, 2, 1);


  this->setLayout(g_layout_);
}


void Maze_group::pb_load_maze_clicked(bool b)
{
  uncheck_set_button();

  emit load_maze_clicked(b);
}


void Maze_group::pb_save_maze_clicked(bool b)
{
  uncheck_set_button();

  emit save_maze_clicked(b);
}



void Maze_group::pb_set_start_clicked(bool b)
{
  auto p = qobject_cast<QPushButton*>(sender());
  exclusiv(p);

  emit set_button_clicked(b, p->text());
}


void Maze_group::pb_set_goal_clicked(bool b)
{
  auto p = qobject_cast<QPushButton*>(sender());
  exclusiv(p);

  emit set_button_clicked(b, p->text());
}


void Maze_group::pb_set_wall_clicked(bool b)
{
  auto p = qobject_cast<QPushButton*>(sender()); //TODO no repeat
  exclusiv(p);

  emit set_button_clicked(b, p->text());
}


void Maze_group::pb_set_dim_clicked(bool b)
{
  uncheck_set_button();

  emit set_dim_clicked(b);
}


void Maze_group::exclusiv(const QPushButton* p)
{
  if(p->text() == "set start")
  {
    pb_set_goal_->setChecked(false);
    pb_set_wall_->setChecked(false);
  }

  if(p->text() == "set goal")
  {
    pb_set_start_->setChecked(false);
    pb_set_wall_->setChecked(false);
  }

  if(p->text() == "set wall")
  {
    pb_set_start_->setChecked(false);
    pb_set_goal_->setChecked(false);
  }
}

void Maze_group::uncheck_set_button()
{
  pb_set_start_->setChecked(false);
  pb_set_goal_->setChecked(false);
  pb_set_wall_->setChecked(false); //TODO
}
