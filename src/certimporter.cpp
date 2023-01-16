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

#include "certimporter.h"

#include <QDir>
#include <QSslCertificate>
#include <QSslConfiguration>

void CertImporter::import(const QString &target)
{
    qInfo() << "Importing system certificates";

    QString certFilePath = getCertFilePath(target);
    if (certFilePath.isEmpty())
        return;

    QByteArray certificates;
    for (const QSslCertificate &certificate : QSslConfiguration::systemCaCertificates())
        certificates += certificate.toPem();

    if (!certificates.isEmpty())
    {
        QFile certFile(certFilePath);
        if (certFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            const auto bytes = certFile.write(certificates);
            certFile.close();

            if (bytes < 0)
                qInfo() << "FAILED. Cannot write to file:" << certFile.fileName() << "error message:" << certFile.errorString();
            else
                qInfo() << "OK. System certificates successfully imported";
        }
        else
            qInfo() << "FAILED. Cannot open file:" << certFile.fileName() << "error message:" << certFile.errorString();
    }
    else
        qInfo() << "FAILED. Cannot find certificates in system CA database";
}

QString CertImporter::getCertFilePath(const QString &target)
{ 
    QString result;
    const QString certFileName = "cert.pem";

    if (target.isEmpty())
    {
        if (QDir::current().dirName() == "bin")
            result = QString("%1/../share/ssl/certs/%2").arg(QDir::currentPath(), certFileName);
        else
            result = QString("%1/share/ssl/certs/%2").arg(QDir::currentPath(), certFileName);
    }
    else
    { 
        QDir dir(target);
        if (!dir.exists())
        {
            if (!dir.mkdir("."))
                qInfo() << "FAILED. The specified path does not exist:" << target;
            else
                result = QString("%1/%2").arg(dir.path(), certFileName);
        }
        else
            result = QString("%1/%2").arg(dir.path(), certFileName);
    }

    return result;
}
