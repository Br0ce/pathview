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

  grid_frame_(new QFrame(main_widget_)),
  grid_layout_(new QGridLayout(grid_frame_)),

  dock_frame_(new QFrame(dock_widget_)),
  dock_layout_(new QVBoxLayout(dock_frame_)),

  search_group_(new QGroupBox(tr("search"), dock_widget_)),
  search_group_layout_(new QGridLayout(search_group_)),

  search_combo_(new QComboBox(search_group_)), // TODO needed!?

  stats_group_(new QGroupBox(tr("stats"), dock_frame_)),
  stats_group_layout_(new QFormLayout(stats_group_)),

  field_settings_group_(new QGroupBox(tr("field settings"), dock_frame_)),
  field_settings_group_layout_(new QGridLayout(field_settings_group_)),

  maze_group_(new QGroupBox(tr("maze builder"), dock_frame_)),
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


  /*
   * Maze
   *
   */


  this->setCentralWidget(main_widget_);

  grid_frame_->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
  grid_layout_->setSpacing(2);
  grid_layout_->setSizeConstraint(QLayout::SetFixedSize);
  main_widget_->setLayout(grid_layout_);


  build_grid(std::make_pair(10, 10)); // TODO just dummy


  /*
   * Dock
   *
   */


  dock_widget_->setFeatures(QDockWidget::DockWidgetFloatable);
  dock_widget_->setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);
  this->addDockWidget(Qt::LeftDockWidgetArea, dock_widget_);

  dock_layout_->setSpacing(8);
  dock_layout_->setSizeConstraint(QLayout::SetFixedSize);


  /* search-elements */

  search_combo_->addItem(" A*");
  search_combo_->addItem(" D*-light");

  auto pb_search = new QPushButton(tr("search path"), search_group_);
  auto pb_go = new QPushButton(tr("go"), search_group_);
  auto pb_pause = new QPushButton(tr("pause"), search_group_);

  search_group_layout_->setSpacing(4);
  search_group_layout_->setSizeConstraint(QLayout::SetFixedSize);

  search_group_layout_->addWidget(search_combo_, 0, 0, 2, 2);
  search_group_layout_->addWidget(pb_search, 2, 0, 2, 2);
  search_group_layout_->addWidget(pb_go, 4, 0, 1, 1);
  search_group_layout_->addWidget(pb_pause, 4, 1, 1, 1);

  search_group_->setLayout(search_group_layout_);
  dock_layout_->addWidget(search_group_);


  /* stats-elements */

  auto ledit_status = new QLineEdit(stats_group_);
  ledit_status->setReadOnly(true);
  ledit_status->setAlignment(Qt::AlignLeft);

  auto ledit_expanded = new QLineEdit(stats_group_);
  ledit_expanded->setReadOnly(true);
  ledit_expanded->setAlignment(Qt::AlignLeft);

  auto ledit_reached_in = new QLineEdit(stats_group_);
  ledit_reached_in->setReadOnly(true);
  ledit_reached_in->setAlignment(Qt::AlignLeft);

  stats_group_layout_->setSpacing(4);
  stats_group_layout_->setSizeConstraint(QLayout::SetFixedSize);

  stats_group_layout_->addRow(tr("status"), ledit_status); //TODO check parent
  stats_group_layout_->addRow(tr("expanded"), ledit_expanded);
  stats_group_layout_->addRow(tr("reached in"), ledit_reached_in);

  stats_group_->setLayout(stats_group_layout_);
  dock_layout_->addWidget(stats_group_);


  /* field settings-elements */

  auto cb_g_value = new QCheckBox(tr("g-value"), field_settings_group_);
  auto cb_h_value = new QCheckBox(tr("h-value"), field_settings_group_);
  auto cb_f_value = new QCheckBox(tr("f-value"), field_settings_group_);
  auto cb_rhs_value = new QCheckBox(tr("rhs-value"), field_settings_group_);
  auto cb_expanded = new QCheckBox(tr("expanded"), field_settings_group_);

  field_settings_group_layout_->setSpacing(4);
  field_settings_group_layout_->setSizeConstraint(QLayout::SetFixedSize);

  field_settings_group_layout_->addWidget(cb_g_value, 0, 0);
  field_settings_group_layout_->addWidget(cb_h_value, 1, 0);
  field_settings_group_layout_->addWidget(cb_f_value, 2, 0);
  field_settings_group_layout_->addWidget(cb_rhs_value, 0, 1);
  field_settings_group_layout_->addWidget(cb_expanded, 1, 1);

  field_settings_group_->setLayout(field_settings_group_layout_);
  dock_layout_->addWidget(field_settings_group_);


  /* maze builder-elements */

  auto pb_load_maze = new QPushButton(tr("load maze"), maze_group_);
  auto pb_save_maze = new QPushButton(tr("save maze"), maze_group_);
  auto pb_set_start = new QPushButton(tr("set start"), maze_group_);
  auto pb_set_goal = new QPushButton(tr("set goal"), maze_group_);
  auto pb_set_dim = new QPushButton(tr("set dim"), maze_group_);
  auto pb_set_wall = new QPushButton(tr("set wall"), maze_group_);

  maze_group_layout_->setSpacing(4);
  maze_group_layout_->setSizeConstraint(QLayout::SetFixedSize);

  maze_group_layout_->addWidget(pb_load_maze, 0, 0);
  maze_group_layout_->addWidget(pb_save_maze, 0, 1);
  maze_group_layout_->addWidget(pb_set_start, 1, 0);
  maze_group_layout_->addWidget(pb_set_goal, 1, 1);
  maze_group_layout_->addWidget(pb_set_dim, 2, 0);
  maze_group_layout_->addWidget(pb_set_wall, 2, 1);

  maze_group_->setLayout(maze_group_layout_);
  dock_layout_->addWidget(maze_group_);

  dock_widget_->setWidget(dock_frame_);
}


void Main_window::build_grid(dim d)
{
  for(auto i = 0; i < d.first; ++i)
  {
    for(auto j = 0; j < d.second; ++j)
    {
      auto f = new Field(std::make_pair(i, j), grid_frame_);

      grid_layout_->addWidget(f, i, j);
    }
  }
}


void Main_window::closeEvent(QCloseEvent* event)
{
  save_settings();
  QWidget::closeEvent(event);
}
