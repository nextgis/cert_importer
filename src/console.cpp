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

#include "console.h"
#include <QDebug>
#ifdef Q_OS_WIN
#   include <Windows.h>
#endif

void Console::Open()
{
#ifdef Q_OS_WIN
    if (AllocConsole())
    {
        freopen_s(reinterpret_cast<FILE **>(stdout), "CONOUT$", "w", stdout);
        freopen_s(reinterpret_cast<FILE **>(stdout), "CONOUT$", "w", stderr);
        freopen_s(reinterpret_cast<FILE **>(stdin), "CONIN$", "r", stdin);
    }
#endif
}

void Console::Close()
{
#ifdef Q_OS_WIN
    qInfo() << "\nPress any key to close";

    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    if (handle)
    {
        SetConsoleMode(handle, ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
        TCHAR c = 0; DWORD cc;
        ReadConsole(handle, &c, 1, &cc, NULL);
    }
    FreeConsole();
#endif
}
