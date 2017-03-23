/***************************************************************************
 * Copyright (C) 2012 Marcus Efraimsson.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *
 ***************************************************************************/

#include "lifesatremote.h"
#include "lifesatremoteconnection.h"

using namespace lifesatremote;

ILifeSatRemoteConnection::~ILifeSatRemoteConnection()
{
}

ILifeSatRemoteConnection* LifeSatRemote::Connect(lifesatremotehttp::HttpClient& httpClient, const std::string& hostAddress, const long port, LifeSatRemoteLocker* locker)
{
    return new LifeSatRemoteCommunication(httpClient, hostAddress, port, locker);
}

ILifeSatRemoteConnection* LifeSatRemote::Connect(lifesatremotehttp::HttpClient& httpClient, const std::string& hostAddress, const long port, const std::string& username, const std::string& password, LifeSatRemoteLocker* locker)
{
    return new LifeSatRemoteCommunication(httpClient, hostAddress, port, username, password, locker);
}

void LifeSatRemote::GetCopyrightNotice(std::string& copyright) 
{
  copyright.assign(LIBDVBLINKREMOTE_COPYRIGHT);
}

void LifeSatRemote::GetVersion(std::string& version)
{
  version.assign(LIBDVBLINKREMOTE_VERSION);
}

void LifeSatRemote::GetVersion(int& major, int& minor, int& patch)
{
  major = LIBDVBLINKREMOTE_VERSION_MAJOR;
  minor = LIBDVBLINKREMOTE_VERSION_MINOR;
  patch = LIBDVBLINKREMOTE_VERSION_PATCH;
}
