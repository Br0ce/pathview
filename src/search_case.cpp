/** @file maze_admin.h
 *
 * @brief
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


#include "search_case.h"


Search_case::Search_case(Maze_admin* maze_ad, QWidget* parent) :
  QWidget(parent),
  maze_ad_(maze_ad),
  graph_(new Graph(this)),
  status_(2, false) // 0=start, 1=goal
{
  connect(maze_ad_, SIGNAL(publish_start(Position)),
          this, SLOT(start_request(Position)));

  connect(maze_ad_, SIGNAL(publish_goal(Position)),
          this, SLOT(goal_request(Position)));

  connect(maze_ad_, SIGNAL(publish_wall(Position)),
          this, SLOT(wall_request(Position)));

  connect(maze_ad_, SIGNAL(publish_unset_wall(Position)),
          this, SLOT(unset_wall_request(Position)));

  connect(this, SIGNAL(unset(Position)),
          maze_ad_, SLOT(set_space(Position)));

  connect(graph_, SIGNAL(update_state(Index)),
          maze_ad_, SLOT(update_field(Index)));
}

/*
void Search_case::resize_map(const Dim& d)
{
  Position::set_dimensions(d);
  map_.resize(d.first, d.second);
}

void Search_case::resize_map(Dim&& d)
{
  Position::set_dimensions(d);
  map_.resize(d.first, d.second);
}
*/


QGridLayout* Search_case::get_maze_layout()
{
  map_.setZero();
  graph_->init_4_neighborhood(map_);

  auto tmp = maze_ad_->make_maze(map_);
  maze_ad_->link_states(graph_->get_states());

  return tmp;
}


Dim Search_case::map_size() const
{
  return std::make_pair(map_.rows(), map_.cols());
}


void Search_case::load_maze() // TODO split and unset set_start etc.
{
  try
  {
    QString q_form = QFileDialog::getOpenFileName(this, tr("Load Map"));

    std::ifstream f(q_form.toStdString());

    if(f.is_open())
    {
      std::string tmp;
      std::getline(f, tmp);
      int rows = std::stoi(tmp);
      std::getline(f, tmp);
      int cols = std::stoi(tmp);

      if((rows < 1) || (rows > 25))
        throw Pathview_error("rows are not in range");
      if((cols < 1) || (cols > 25))
        throw Pathview_error("cols are not in range");

      Eigen::MatrixXi m(rows, cols);
      std::istream_iterator<int> ii{f};
      std::istream_iterator<int> eos{};
      std::vector<int> v{ii, eos};

      // TODO check num of elements in v to fit with rows*cols

      f.close();

      int k = 0;
      for(auto i = 0; i < m.rows(); ++i)
        for(auto j = 0; j < m.cols(); ++j)
          m(i, j) = v.at(k++);

      map_ = std::move(m);
      Position::set_dimensions(std::make_pair(rows, cols));


      graph_->init_4_neighborhood(map_);

      emit refresh_maze(maze_ad_->make_maze(map_));

      maze_ad_->link_states(graph_->get_states());
    }
  }
  catch(std::exception& e)
  {
    __LOG(e.what())
  }
}


void Search_case::save_maze()
{
  try
  {
    QString q_form = QFileDialog::getSaveFileName(this, tr("Save Map"));

    std::ofstream target(q_form.toStdString(), std::ios::trunc);

    if(target.fail())
      throw Pathview_error("cannot save map");

    target << map_.rows() << "\n";
    target << map_.cols() << "\n";

    for(int i = 0; i < map_.rows(); ++i)
    {
      for(int j = 0; j < map_.cols(); ++j)
      {
        target << map_(i, j) << " ";
      }
      target << "\n";
    }
    target.close();
  }
  catch(std::exception& e)
  {
    __LOG(e.what());
  }
}


void Search_case::start_request(Position p)
{
  if(start_status())
  {
    if(p == get_goal())
      set_goal_status(false);

    emit unset(start_);
  }
  else
    set_start_status(true);

  start_ = p;
}

void Search_case::goal_request(Position p)
{
  if(goal_status())
  {
    if(p == get_start())
      set_start_status(false);

    emit unset(goal_);
  }
  else
    set_goal_status(true);

  goal_ = p;
}


void Search_case::wall_request(Position p)
{
  map_(p.pos().first, p.pos().second) = MAX_WEIGHT;
  graph_->add_wall(p);
}


void Search_case::unset_wall_request(Position p)
{
  map_(p.pos().first, p.pos().second) = 0;
  graph_->remove_wall(p);
}

Position Search_case::get_start() const { return start_; }

Position Search_case::get_goal() const { return goal_; }


bool Search_case::start_status() const { return status_.at(0); }

bool Search_case::goal_status() const { return status_.at(1); }


void Search_case::set_start_status(bool b) { status_.at(0) = b; }

void Search_case::set_goal_status(bool b) { status_.at(1) = b; }

/*
void Search_case::link_states()
{
  for(const auto& s : graph_->get_states())
  {
    connect(s, SIGNAL(g_changed(double)),
            maze_ad_, SLOT(publish_g_change(double)));

    connect(s, SIGNAL(h_changed(double)),
            maze_ad_, SLOT(publish_h_change(double)));

    connect(s, SIGNAL(f_changed(double)),
            maze_ad_, SLOT(publish_f_change(double)));
  }
}
*/