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

  dock_frame_(new QFrame(dock_widget_)),
  dock_layout_(new QVBoxLayout(dock_frame_)),

  search_group_(new Search_group(dock_frame_)),
  stats_group_(new Stats_group(dock_frame_)),
  field_settings_group_(new Field_settings_group(dock_frame_)),
  maze_group_(new Maze_group(dock_frame_)),

  maze_admin_(new Maze_admin(this)),
  search_case_(new Search_case(maze_admin_, this)),

  dim_dialog_(new Set_dim_dialog(this))
{
  __LOG("START")

  connect(search_case_, SIGNAL(refresh_maze(QGridLayout*)),
          this, SLOT(set_maze_layout(QGridLayout*)));

  connect(dim_dialog_, SIGNAL(publish_dim_request(Dim)),
          this, SLOT(receive_dim_request(Dim)));

  connect(maze_group_, SIGNAL(load_maze_clicked(bool)),
          search_case_, SLOT(load_maze()));

  connect(maze_group_, SIGNAL(load_maze_clicked(bool)),
          field_settings_group_, SLOT(set_uncheck()));

  connect(maze_group_, SIGNAL(save_maze_clicked(bool)),
          search_case_, SLOT(save_maze()));

  connect(maze_group_, SIGNAL(set_button_clicked(bool, QString)),
          maze_admin_, SLOT(enable_responsive_mode(bool, QString)));

  connect(maze_group_, SIGNAL(set_dim_clicked(bool)),
          this, SLOT(show_dim_dialog()));

  connect(maze_admin_, SIGNAL(uncheck_button()),
          maze_group_, SLOT(uncheck_set_button()));

  connect(field_settings_group_, SIGNAL(display_request(Display, bool)),
          maze_admin_, SLOT(display_dispatch(Display, bool)));

  connect(search_group_, SIGNAL(search_mode_change(QString)),
          search_case_, SLOT(change_search_mode(QString)));

  connect(search_group_, SIGNAL(search_clicked()),
          search_case_, SLOT(start_search()));

  settings_.setFallbacksEnabled(false);
  read_settings();

  init_dimensions();
  init_gui();
}


void Main_window::read_settings()
{
  auto rows = settings_.value("maze_dimension/maze_rows").toInt();
  auto cols = settings_.value("maze_dimension/maze_cols").toInt();

  search_case_->resize_map(std::make_pair(rows, cols));
}


void Main_window::save_settings()
{
  settings_.beginGroup("maze_dimension");
  settings_.setValue("maze_rows", search_case_->map_size().first);
  settings_.setValue("maze_cols", search_case_->map_size().second);
}


void Main_window::init_dimensions()
{
  Position::set_dimensions(search_case_->map_size());
  dim_dialog_->init_dim(search_case_->map_size());
}


void Main_window::set_maze_layout(QGridLayout* l)
{
  dim_dialog_->init_dim(search_case_->map_size());
  main_widget_->setLayout(l);
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

  set_maze_layout(search_case_->get_maze_layout());


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

  dock_layout_->addWidget(search_group_);


  /* stats-elements */

  dock_layout_->addWidget(stats_group_);


  /* field settings-elements */

  dock_layout_->addWidget(field_settings_group_);


  /* maze builder-elements */

  dock_layout_->addWidget(maze_group_);


  dock_widget_->setWidget(dock_frame_);
}


void Main_window::closeEvent(QCloseEvent* event)
{
  __LOG("END")
  save_settings();
  QWidget::closeEvent(event);
}


void Main_window::show_dim_dialog()
{
  dim_dialog_->show();
  dim_dialog_->exec();
}


void Main_window::receive_dim_request(Dim d)
{
  search_case_->resize_map(d);
  set_maze_layout(search_case_->get_maze_layout());
}
