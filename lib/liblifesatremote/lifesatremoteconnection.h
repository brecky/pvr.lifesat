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

#pragma once

#include <string>
#include "lifesatremote.h"
#include "lifesatremotehttp.h"
#include "response.h"
#include "request.h"

namespace lifesatremote 
{

  #ifndef _MSC_VER
  #define vsprintf_s vsprintf
  #define _snprintf_s(a,b,c,...) snprintf(a,b,__VA_ARGS__)
  #endif


  class LifeSatRemoteCommunication : public ILifeSatRemoteConnection
  {
  public:
      LifeSatRemoteCommunication(lifesatremotehttp::HttpClient& httpClient, const std::string& hostAddress, const long port, LifeSatRemoteLocker* locker);
      LifeSatRemoteCommunication(lifesatremotehttp::HttpClient& httpClient, const std::string& hostAddress, const long port, const std::string& username, const std::string& password, const std::string& client_id, const std::string& client_secret, LifeSatRemoteLocker* locker);
       
      virtual ~LifeSatRemoteCommunication();

    LifeSatRemoteStatusCode GetChannels(const GetChannelsRequest& request, ChannelList& response, std::string* err_str);
    LifeSatRemoteStatusCode SearchEpg(const EpgSearchRequest& request, EpgSearchResult& response, std::string* err_str);
    LifeSatRemoteStatusCode PlayChannel(const StreamRequest& request, Stream& response, std::string* err_str);
    LifeSatRemoteStatusCode StopChannel(const StopStreamRequest& request, std::string* err_str);
    LifeSatRemoteStatusCode GetRecordings(const GetRecordingsRequest& request, RecordingList& response, std::string* err_str);
    LifeSatRemoteStatusCode RemoveRecording(const RemoveRecordingRequest& request, std::string* err_str);
    LifeSatRemoteStatusCode AddSchedule(const AddScheduleRequest& request, std::string* err_str);
    LifeSatRemoteStatusCode GetSchedules(const GetSchedulesRequest& request, StoredSchedules& response, std::string* err_str);
    LifeSatRemoteStatusCode UpdateSchedule(const UpdateScheduleRequest& request, std::string* err_str);
    LifeSatRemoteStatusCode RemoveSchedule(const RemoveScheduleRequest& request, std::string* err_str);
    LifeSatRemoteStatusCode GetParentalStatus(const GetParentalStatusRequest& request, ParentalStatus& response, std::string* err_str);
    LifeSatRemoteStatusCode SetParentalLock(const SetParentalLockRequest& request, ParentalStatus& response, std::string* err_str);
    LifeSatRemoteStatusCode GetM3uPlaylist(const GetM3uPlaylistRequest& request, M3uPlaylist& response, std::string* err_str);
    LifeSatRemoteStatusCode GetPlaybackObject(const GetPlaybackObjectRequest& request, GetPlaybackObjectResponse& response, std::string* err_str);
    LifeSatRemoteStatusCode RemovePlaybackObject(const RemovePlaybackObjectRequest& request, std::string* err_str);
    LifeSatRemoteStatusCode StopRecording(const StopRecordingRequest& request, std::string* err_str);
    LifeSatRemoteStatusCode GetStreamingCapabilities(const GetStreamingCapabilitiesRequest& request, StreamingCapabilities& response, std::string* err_str);
    LifeSatRemoteStatusCode GetRecordingSettings(const GetRecordingSettingsRequest& request, RecordingSettings& response, std::string* err_str);
    LifeSatRemoteStatusCode SetRecordingSettings(const SetRecordingSettingsRequest& request, std::string* err_str);
    LifeSatRemoteStatusCode GetFavorites(const GetFavoritesRequest& request, ChannelFavorites& response, std::string* err_str);
    LifeSatRemoteStatusCode GetServerInfo(const GetServerInfoRequest& request, ServerInfo& response, std::string* err_str);
    LifeSatRemoteStatusCode GetToken(const GetTokenRequest& request, Token& response, std::string* err_str);

  private:
    lifesatremotehttp::HttpClient& m_httpClient;
    std::string m_hostAddress;
    long m_port;
    std::string m_username;
    std::string m_password;
    std::string m_client_id;
    std::string m_client_secret;
    char m_errorBuffer[lifesatremote::LIFESAT_REMOTE_DEFAULT_BUFFER_SIZE];
    LifeSatRemoteLocker* m_locker;

    LifeSatRemoteStatusCode GetData(const std::string& command, const Request& request, Response& response, std::string* err_str);
    LifeSatRemoteStatusCode SerializeRequestObject(const std::string& command, const Request& request, std::string& requestXmlData);
    LifeSatRemoteStatusCode DeserializeResponseData(const std::string& command, const std::string& responseData, Response& responseObject);
    std::string GetUrl();
    std::string CreateRequestDataParameter(const std::string& command, const std::string& xmlData);
    std::string CreateRequestApiDataParameter(const std::string& command, const std::string& apiData);

    std::string GetStatusCodeDescription(LifeSatRemoteStatusCode status);
    void WriteError(const char* format, ...);
    void ClearErrorBuffer();
    void GetLastError(std::string& err);
  };
};
