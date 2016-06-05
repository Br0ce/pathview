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
  graph_(new Graph(this)) {}

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

  return maze_ad_->make_maze(map_);
}


Dim Search_case::map_size() const
{
  return std::make_pair(map_.rows(), map_.cols());
}


void Search_case::pb_load_maze_clicked()
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

      map_ = m;
      Position::set_dimensions(std::make_pair(rows, cols));
    }
  }
  catch(std::exception& e)
  {
    __LOG(e.what())
  }

  graph_->init_4_neighborhood(map_);
  emit refresh_maze(maze_ad_->make_maze(map_));
}
