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

#include <QDebug>
#include "certimporter.h"
#include "console.h"
#include "options.h"

int main(int argc, char **argv)
{
    CommandLine::Options options = CommandLine::parse(argc, argv);

    if (!options.silentMode)
        Console::Open();

    qInfo() << "***********************************************************************";
    qInfo() << "*** NextGIS tools *****************************************************";
    qInfo() << "*** Utility to Imports system certificates to OpenSSL PEM CA bundle ***";
    qInfo() << "***********************************************************************\n";

    CertImporter::import(options.targetPath);

    if (!options.silentMode)
        Console::Close();
}
