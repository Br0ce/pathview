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

  maze_admin_(new Maze_admin(this)),
  search_case_(new Search_case(maze_admin_, this)),

  dim_dialog_(new Set_dim_dialog(this))
{
  __LOG("START")

  connect(search_case_, SIGNAL(refresh_maze(QGridLayout*)),
          this, SLOT(set_maze_layout(QGridLayout*)));

  connect(dim_dialog_, SIGNAL(publish_dim_request(Dim)),
          this, SLOT(receive_dim_request(Dim)));


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

  dock_layout_->addWidget(make_search_group(dock_widget_));


  /* stats-elements */

  dock_layout_->addWidget(make_stats_group(dock_frame_));


  /* field settings-elements */

  dock_layout_->addWidget(make_field_settings_group(dock_frame_));


  /* maze builder-elements */

  dock_layout_->addWidget(make_maze_group(dock_frame_));


  dock_widget_->setWidget(dock_frame_);
}


QGroupBox* Main_window::make_search_group(QWidget* parent)
{
  auto g_box = new QGroupBox(tr("search"), parent); //dock_widget_

  auto pb_search = new QPushButton(tr("search path"), g_box);
  auto pb_go = new QPushButton(tr("go"), g_box);
  auto pb_pause = new QPushButton(tr("pause"), g_box);

  auto search_combo = new QComboBox(g_box);
  search_combo->addItem(" A*");
  search_combo->addItem(" D*-light");

  connect(search_combo, SIGNAL(activated(int)),
          this, SLOT(search_mode(int)));

  auto g_layout = new QGridLayout(g_box);
  g_layout->setSpacing(4);
  g_layout->setSizeConstraint(QLayout::SetFixedSize);

  g_layout->addWidget(search_combo, 0, 0, 2, 2);
  g_layout->addWidget(pb_search, 2, 0, 2, 2);
  g_layout->addWidget(pb_go, 4, 0, 1, 1);
  g_layout->addWidget(pb_pause, 4, 1, 1, 1);


  g_box->setLayout(g_layout);

  return g_box;
}


QGroupBox* Main_window::make_stats_group(QWidget* parent)
{
  auto g_box = (new QGroupBox(tr("stats"), parent)); // dock_frame_

  auto l_edit_status = new QLineEdit(g_box);
  l_edit_status->setReadOnly(true);
  l_edit_status->setAlignment(Qt::AlignLeft);

  auto l_edit_expanded = new QLineEdit(g_box);
  l_edit_expanded->setReadOnly(true);
  l_edit_expanded->setAlignment(Qt::AlignLeft);

  auto l_edit_reached_in = new QLineEdit(g_box);
  l_edit_reached_in->setReadOnly(true);
  l_edit_reached_in->setAlignment(Qt::AlignLeft);

  auto f_layout = new QFormLayout(g_box);

  f_layout->setSpacing(4);
  f_layout->setSizeConstraint(QLayout::SetFixedSize);

  f_layout->addRow(tr("status"), l_edit_status); //TODO check parent
  f_layout->addRow(tr("expanded"), l_edit_expanded);
  f_layout->addRow(tr("reached in"), l_edit_reached_in);


  g_box->setLayout(f_layout);

  return g_box;
}


QGroupBox* Main_window::make_field_settings_group(QWidget* parent)
{
  auto g_box = new QGroupBox(tr("field settings"), parent); // dock_frame_
  auto g_layout = new QGridLayout(g_box);

  auto cb_g_value = new QCheckBox(tr("g-value"), g_box);
  auto cb_h_value = new QCheckBox(tr("h-value"), g_box);
  auto cb_f_value = new QCheckBox(tr("f-value"), g_box);
  auto cb_rhs_value = new QCheckBox(tr("rhs-value"), g_box);
  auto cb_expanded = new QCheckBox(tr("expanded"), g_box);

  g_layout->setSpacing(4);
  g_layout->setSizeConstraint(QLayout::SetFixedSize);

  g_layout->addWidget(cb_g_value, 0, 0);
  g_layout->addWidget(cb_h_value, 1, 0);
  g_layout->addWidget(cb_f_value, 2, 0);
  g_layout->addWidget(cb_rhs_value, 0, 1);
  g_layout->addWidget(cb_expanded, 1, 1);


  g_box->setLayout(g_layout);

  return g_box;
}


QGroupBox* Main_window::make_maze_group(QWidget* parent)
{
  auto g_box = new QGroupBox(tr("maze builder"), parent); // dock_frame_
  auto g_layout = new QGridLayout(g_box);

  auto pb_load_maze = new QPushButton(tr("load map"), g_box);
  auto pb_save_maze = new QPushButton(tr("save map"), g_box);
  auto pb_set_start = new QPushButton(tr("set start"), g_box);
  auto pb_set_goal = new QPushButton(tr("set goal"), g_box);
  auto pb_set_dim = new QPushButton(tr("set dim"), g_box);
  auto pb_set_wall = new QPushButton(tr("set wall"), g_box);

  connect(pb_set_dim, SIGNAL(clicked(bool)), this, SLOT(pb_set_dim_clicked()));
  connect(pb_load_maze, SIGNAL(clicked(bool)), search_case_,
          SLOT(pb_load_maze_clicked()));

  g_layout->setSpacing(4);
  g_layout->setSizeConstraint(QLayout::SetFixedSize);

  g_layout->addWidget(pb_load_maze, 0, 0);
  g_layout->addWidget(pb_save_maze, 0, 1);
  g_layout->addWidget(pb_set_start, 1, 0);
  g_layout->addWidget(pb_set_goal, 1, 1);
  g_layout->addWidget(pb_set_dim, 2, 0);
  g_layout->addWidget(pb_set_wall, 2, 1);


  g_box->setLayout(g_layout);

  return g_box;
}


void Main_window::closeEvent(QCloseEvent* event)
{
  __LOG("END")
  save_settings();
  QWidget::closeEvent(event);
}

void Main_window::search_mode(int i)
{
  // TODO dummy
  if(i == 0)
    qDebug() << "A*";
  if(i == 1)
    qDebug() << "D*";
}


void Main_window::pb_set_dim_clicked()
{
  dim_dialog_->show();
  dim_dialog_->exec();
}

void Main_window::receive_dim_request(Dim d)
{
  search_case_->resize_map(d);
  set_maze_layout(search_case_->get_maze_layout());
}
