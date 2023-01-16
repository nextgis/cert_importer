/******************************************************************************
 * Project: cert_importer
 * Copyright (c) 2023 NextGIS, <info@nextgis.com>
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#include "options.h"
#include <QCommandLineParser>

CommandLine::Options CommandLine::parse(int argc, char **argv)
{
    QStringList arguments;
    for (size_t i = 0; i < argc; ++i)
        arguments.push_back(QString(argv[i]));

    QCommandLineParser parser;
    parser.addOption({ QStringList() << "s" << "silent", "silent mode." });
    parser.addOption({ QStringList() << "t" << "target", "cert.pem <directory>.", "directory" });
    parser.parse(arguments);

    return  { parser.isSet("silent"), parser.value("target") };
}
