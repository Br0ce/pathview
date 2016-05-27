/** @file main_window.cpp
 *
 * @brief Main window for pathview
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

#include "main_window.h"


Main_window::Main_window(QWidget* parent):
  QMainWindow(parent),
  settings_("pathview_user",
            "pathview"), // stored in ~/confi/pathview_user/pathview.conf
  main_widget_(new QWidget(this)),
  dock_widget_(new QDockWidget(this)),
  frame_(new QFrame(main_widget_)),
  grid_(new QGridLayout(frame_)),
  maze_group_(new QGroupBox(dock_widget_)),
  maze_group_layout_(new QGridLayout(maze_group_))
{
  settings_.setFallbacksEnabled(false);
  read_settings();
  init_gui();
}


void Main_window::read_settings()
{
  maze_dim_.first = settings_.value("maze_dimension/maze_rows").toInt();
  maze_dim_.second = settings_.value("maze_dimension/maze_cols").toInt();
}


void Main_window::save_settings()
{
  settings_.beginGroup("maze_dimension");
  settings_.setValue("maze_rows", maze_dim_.first);
  settings_.setValue("maze_cols", maze_dim_.second);
}


void Main_window::init_gui()
{
  this->setWindowTitle(tr("pathview"));
  setUnifiedTitleAndToolBarOnMac(true); //TODO check

  this->setCentralWidget(main_widget_);

  dock_widget_->setFeatures(QDockWidget::DockWidgetFloatable);
  dock_widget_->setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);
  this->addDockWidget(Qt::LeftDockWidgetArea, dock_widget_);

  //TODO check titlebar - QDockWidget::DockWidgetVerticalTitleBar);

  auto p = new QPushButton(tr("test"), maze_group_); //TODO just dummy

  maze_group_layout_->addWidget(p);
  maze_group_->setLayout(maze_group_layout_);
  dock_widget_->setWidget(maze_group_);
  frame_->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

  grid_->setSpacing(2);

  build_grid(std::make_pair(5, 5)); // TODO just dummy
}


void Main_window::build_grid(dim d)
{
  for(auto i = 0; i < d.first; ++i)
  {
    for(auto j = 0; j < d.second; ++j)
    {
      auto f = new Field(std::make_pair(i, j), frame_);

      grid_->addWidget(f, i, j);
    }
  }
}


void Main_window::closeEvent(QCloseEvent* event)
{
  save_settings();
  QWidget::closeEvent(event);
}
