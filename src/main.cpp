/** @file main.cpp
 *
 * @brief Main to pathview
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



#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

#include "main_window.h"



#ifdef QT_VERSION_5_4_REACHED // QtInfoMsg is defined QT_Version >= 5.4

/**
  * @brief redirect debug-messages to file: /log/debug_log.txt
  *
  * @param type QtMsgType
  * @param con QMessageLogContext -- not used
  * @param msg QString
  * @return void
  */
void log_to_file(QtMsgType type, const QMessageLogContext& con, const
                 QString& msg)
{
  QString txt;
  QString header = QDateTime::currentDateTime().toString();

  switch(type)
  {
  case QtDebugMsg:
    txt = "Debug: " + header + " " + msg;
    break;

  case QtInfoMsg:
    txt = "Info: " + header + " " + msg;
    break;

  case QtWarningMsg:
    txt = "Warning: " + header + " " + msg;
    break;

  case QtCriticalMsg:
    txt = "Critical: " + header + " " + msg;
    break;

  case QtFatalMsg:
    txt = "Fatal: " + header + " " + msg;
    abort();
  }

  QFile f(QDir::currentPath() + "/log/debug_msg.log");

  if(f.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
  {
    QTextStream ts(&f);
    ts << txt << endl;
  }
}


#endif

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  #ifdef QT_VERSION_5_4_REACHED
  qInstallMessageHandler(log_to_file);
  #endif

  Main_window main_window;
  main_window.show();

  return app.exec();
}