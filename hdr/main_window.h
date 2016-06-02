/** @file main_window.h
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


#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


// #include <QMainWindow> //TODO WIDGHETS
#include <QtWidgets>
#include <QSettings>
#include <QDockWidget>
#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>


#include "defines.h"
#include "field.h"
#include "graph.h"
#include "position.h"


class Main_window : public QMainWindow
{

  Q_OBJECT

public:


  explicit Main_window(QWidget* parent = 0);
  virtual ~Main_window() = default;

  void read_settings();
  void save_settings();
  void init_gui();

  QGroupBox* make_search_group(QWidget* parent);
  QGroupBox* make_stats_group(QWidget* parent);
  QGroupBox* make_field_settings_group(QWidget* parent);
  QGroupBox* make_maze_group(QWidget* parent);

  void build_grid(dim d);

protected:

  void closeEvent(QCloseEvent* event) override;

private slots:

  void search_mode(int i);

private:

  QSettings settings_;

  QWidget* main_widget_;
  QDockWidget* dock_widget_;

  QFrame* grid_frame_;
  QGridLayout* grid_layout_;

  QFrame* dock_frame_;
  QVBoxLayout* dock_layout_;

  dim maze_dim_;
  Graph graph_;
};

#endif // MAIN_WINDOW_H
