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

#pragma once

#include <QString>

class CertImporter
{
public:
    static void import(const QString &target);
private:
    static QString getCertFilePath(const QString &target);
    static bool isAlreadyImported(const QString &certFilePath);
    static QByteArray getSystemCertificates();
    static void writeCertificatesToFile(const QByteArray &certificates, const QString &certFilePath);

    friend class CertFilePathTests;
};
