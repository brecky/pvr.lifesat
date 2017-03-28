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

#include <cstdarg>
#include "lifesatremoteconnection.h"
#include "xml_object_serializer.h"
#include "generic_response.h"
#include "json_adapter.h"
#include "json_reader.h"
#include "json_writer.h"


using namespace lifesatremote;
using namespace lifesatremoteserialization;

//struct mytoken {
//    std::string token_type;
//    int expires_in;
//    std::string access_token;
//    std::string refresh_token;
//};
//
//void from_json(const json& j, mytoken& p) {
//    p.token_type = j["token_type"].get<std::string>();
//    p.expires_in = j["expires_in"].get<int>();
//    p.access_token = j["access_token"].get<std::string>();
//    p.refresh_token = j["refresh_token"].get<std::string>();
//}


class JSONExample
{
public:
    // to be JSON'ised
    std::string text;
public:
    // each class requires a public serialize function
    void serialize(JSON::Adapter& adapter)
    {
        // this pattern is required 
        JSON::Class root(adapter, "JSONExample");
        // this is the last member variable we serialize so use the _T variant
        JSON_T(adapter, text);
    }
};

LifeSatRemoteCommunication::LifeSatRemoteCommunication(lifesatremotehttp::HttpClient& httpClient, const std::string& hostAddress, const long port, LifeSatRemoteLocker* locker)
    : m_httpClient(httpClient),
    m_hostAddress(hostAddress),
    m_port(port),
    m_locker(locker)
    
{
  m_username = "";
  m_password = "";

}

LifeSatRemoteCommunication::LifeSatRemoteCommunication(lifesatremotehttp::HttpClient& httpClient, const std::string& hostAddress, const long port, const std::string& username, const std::string& password, LifeSatRemoteLocker* locker)
    : m_httpClient(httpClient),
    m_hostAddress(hostAddress),
    m_port(port),
    m_username(username),
    m_password(password),
    m_locker(locker)
{ 
  
}

lifesatremote::LifeSatRemoteCommunication::LifeSatRemoteCommunication(lifesatremotehttp::HttpClient & httpClient, const std::string & hostAddress, const long port, const std::string & access_token, LifeSatRemoteLocker * locker)
    : m_httpClient(httpClient),
    m_hostAddress(hostAddress),
    m_port(port),
    m_access_token(access_token),
    m_locker(locker)
{
}


LifeSatRemoteCommunication::~LifeSatRemoteCommunication() 
{
}

std::string LifeSatRemoteCommunication::GetStatusCodeDescription(LifeSatRemoteStatusCode status) 
{
  std::string str = "";

  switch (status)
  {
  case LIFESAT_REMOTE_STATUS_OK:
    str = LIFESAT_REMOTE_STATUS_DESC_OK;
    break;
  case LIFESAT_REMOTE_STATUS_ERROR:
    str = LIFESAT_REMOTE_STATUS_DESC_ERROR;
    break;
  case LIFESAT_REMOTE_STATUS_INVALID_DATA:
    str = LIFESAT_REMOTE_STATUS_DESC_INVALID_DATA;
    break;
  case LIFESAT_REMOTE_STATUS_INVALID_PARAM:
    str = LIFESAT_REMOTE_STATUS_DESC_INVALID_PARAM;
    break;
  case LIFESAT_REMOTE_STATUS_NOT_IMPLEMENTED:
    str = LIFESAT_REMOTE_STATUS_DESC_NOT_IMPLEMENTED;
    break;
  case LIFESAT_REMOTE_STATUS_MC_NOT_RUNNING:
    str = LIFESAT_REMOTE_STATUS_DESC_MC_NOT_RUNNING;
    break;
  case LIFESAT_REMOTE_STATUS_NO_DEFAULT_RECORDER:
    str = LIFESAT_REMOTE_STATUS_DESC_NO_DEFAULT_RECORDER;
    break;
  case LIFESAT_REMOTE_STATUS_MCE_CONNECTION_ERROR:
    str = LIFESAT_REMOTE_STATUS_DESC_MCE_CONNECTION_ERROR;
    break;
  case LIFESAT_REMOTE_STATUS_CONNECTION_ERROR:
    str = LIFESAT_REMOTE_STATUS_DESC_CONNECTION_ERROR;
    break;
  case LIFESAT_REMOTE_STATUS_UNAUTHORISED:
    str = LIFESAT_REMOTE_STATUS_DESC_UNAUTHORIZED;
    break;
  }

  return str;
}

void LifeSatRemoteCommunication::GetLastError(std::string& err)
{
  m_errorBuffer[lifesatremote::LIFESAT_REMOTE_DEFAULT_BUFFER_SIZE - 1] = lifesatremote::LIFESAT_REMOTE_EOF;
  err.assign(m_errorBuffer);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetChannels(const GetChannelsRequest& request, ChannelList& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_GET_CHANNELS_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::SearchEpg(const EpgSearchRequest& request, EpgSearchResult& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_SEARCH_EPG_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::PlayChannel(const StreamRequest& request, Stream& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_PLAY_CHANNEL_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::StopChannel(const StopStreamRequest& request, std::string* err_str)
{
  Response* response = new Response();
  LifeSatRemoteStatusCode status = GetData(LIFESAT_REMOTE_STOP_CHANNEL_CMD, request, *response, err_str);
  delete response;

  return status;
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetRecordings(const GetRecordingsRequest& request, RecordingList& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_GET_RECORDINGS_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::RemoveRecording(const RemoveRecordingRequest& request, std::string* err_str)
{
  Response* response = new Response();
  LifeSatRemoteStatusCode status = GetData(LIFESAT_REMOTE_REMOVE_RECORDING_CMD, request, *response, err_str);
  delete response;

  return status;
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::AddSchedule(const AddScheduleRequest& request, std::string* err_str)
{
  Response* response = new Response();
  LifeSatRemoteStatusCode status = GetData(LIFESAT_REMOTE_ADD_SCHEDULE_CMD, request, *response, err_str);
  delete response;

  return status;
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetSchedules(const GetSchedulesRequest& request, StoredSchedules& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_GET_SCHEDULES_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::UpdateSchedule(const UpdateScheduleRequest& request, std::string* err_str)
{
  Response* response = new Response();
  LifeSatRemoteStatusCode status = GetData(LIFESAT_REMOTE_UPDATE_SCHEDULE_CMD, request, *response, err_str);
  delete response;

  return status;
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::RemoveSchedule(const RemoveScheduleRequest& request, std::string* err_str)
{
  Response* response = new Response();
  LifeSatRemoteStatusCode status = GetData(LIFESAT_REMOTE_REMOVE_SCHEDULE_CMD, request, *response, err_str);
  delete response;

  return status;
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetParentalStatus(const GetParentalStatusRequest& request, ParentalStatus& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_GET_PARENTAL_STATUS_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::SetParentalLock(const SetParentalLockRequest& request, ParentalStatus& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_SET_PARENTAL_LOCK_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetPlaybackObject(const GetPlaybackObjectRequest& request, GetPlaybackObjectResponse& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_GET_OBJECT_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::RemovePlaybackObject(const RemovePlaybackObjectRequest& request, std::string* err_str)
{
  Response* response = new Response();
  LifeSatRemoteStatusCode status = GetData(LIFESAT_REMOTE_REMOVE_OBJECT_CMD, request, *response, err_str);
  delete response;

  return status;
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::StopRecording(const StopRecordingRequest& request, std::string* err_str)
{
  Response* response = new Response();
  LifeSatRemoteStatusCode status = GetData(LIFESAT_REMOTE_STOP_RECORDING_CMD, request, *response, err_str);
  delete response;

  return status;
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetStreamingCapabilities(const GetStreamingCapabilitiesRequest& request, StreamingCapabilities& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_GET_STREAMING_CAPABILITIES_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetRecordingSettings(const GetRecordingSettingsRequest& request, RecordingSettings& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_GET_RECORDING_SETTINGS_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::SetRecordingSettings(const SetRecordingSettingsRequest& request, std::string* err_str)
{
  Response* response = new Response();
  LifeSatRemoteStatusCode status = GetData(LIFESAT_REMOTE_SET_RECORDING_SETTING_CMD, request, *response, err_str);
  delete response;

  return status;
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetM3uPlaylist(const GetM3uPlaylistRequest& request, M3uPlaylist& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_GET_PLAYLIST_M3U_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetFavorites(const GetFavoritesRequest& request, ChannelFavorites& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_GET_FAVORITES_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetServerInfo(const GetServerInfoRequest& request, ServerInfo& response, std::string* err_str)
{
    return GetData(LIFESAT_REMOTE_GET_SERVER_INFO_CMD, request, response, err_str);
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetToken(std::string * err_str)
{
    return GetMyToken(err_str);
}

std::string LifeSatRemoteCommunication::GetUrl()
{
  char buffer[2000];
  int length = _snprintf_s(buffer, sizeof(buffer), 2000, LIFESAT_REMOTE_SERVER_URL_FORMAT.c_str(), LIFESAT_REMOTE_SERVER_URL_SCHEME.c_str(), m_hostAddress.c_str(), m_port, LIFESAT_REMOTE_SERVER_URL_PATH.c_str());
  std::string url(buffer, length);
  return url;
}

std::string LifeSatRemoteCommunication::CreateRequestDataParameter(const std::string& command, const std::string& xmlData)
{
  std::string encodedCommand = "";
  std::string encodedXmlData = "";

  m_httpClient.UrlEncode(command, encodedCommand);
  m_httpClient.UrlEncode(xmlData, encodedXmlData);

  std::string data = LIFESAT_REMOTE_HTTP_COMMAND_QUERYSTRING + "=";
  data.append(encodedCommand);
  data.append("&" + LIFESAT_REMOTE_HTTP_XML_PARAM_QUERYSTRING + "=");
  data.append(encodedXmlData);

  return data;
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetData(const std::string& command, const Request& request, Response& responseObject, std::string* err_str)
{
  LifeSatRemoteStatusCode status;
  std::string xmlData;
  std::string test = m_access_token;

  if (m_locker != NULL)
      m_locker->lock();

  ClearErrorBuffer();
        if ((status = SerializeRequestObject(command, request, xmlData)) != LIFESAT_REMOTE_STATUS_OK) {
          WriteError("Serialization of request object failed with error code %d (%s).\n", status, GetStatusCodeDescription(status).c_str());
          return status;
      }


      std::string requestData = CreateRequestDataParameter(command, xmlData);

      lifesatremotehttp::HttpWebRequest* httpRequest = new lifesatremotehttp::HttpWebRequest(GetUrl());
      httpRequest->Method = LIFESAT_REMOTE_HTTP_METHOD;
      httpRequest->Accept = LIFESAT_REMOTE_HTTP_ACCEPT;
      httpRequest->ContentLength = requestData.length();
      httpRequest->Authorization = "Bearer " + m_access_token;
      httpRequest->SetRequestData(requestData);
      if (!m_httpClient.SendApiRequest(*httpRequest)) {
          status = LIFESAT_REMOTE_STATUS_CONNECTION_ERROR;
          WriteError("HTTP request failed with error code %d (%s).\n", status, GetStatusCodeDescription(status).c_str());
      }
      else {
          lifesatremotehttp::HttpWebResponse* httpResponse = m_httpClient.GetResponse();

          if (httpResponse->GetStatusCode() == 401) {
              status = LIFESAT_REMOTE_STATUS_UNAUTHORISED;
              WriteError("HTTP response returned status code %d (%s).\n", httpResponse->GetStatusCode(), GetStatusCodeDescription(status).c_str());
          }
          else if (httpResponse->GetStatusCode() != 200) {
              status = LIFESAT_REMOTE_STATUS_ERROR;
              WriteError("HTTP response returned status code %d.\n", httpResponse->GetStatusCode());
          }
          else {
              std::string responseData = httpResponse->GetResponseData();

              if ((status = DeserializeResponseData(command, responseData, responseObject)) != LIFESAT_REMOTE_STATUS_OK) {
                  WriteError("Deserialization of response data failed with error code %d (%s).\n", status, GetStatusCodeDescription(status).c_str());
              }
          }

          delete httpResponse;
      }

      delete httpRequest;
      if (err_str != NULL)
          GetLastError(*err_str);

      if (m_locker != NULL)
          m_locker->unlock();

      return status;
  }


LifeSatRemoteStatusCode LifeSatRemoteCommunication::GetMyToken(std::string* err_str)
{
    LifeSatRemoteStatusCode status = LIFESAT_REMOTE_STATUS_OK;
    
    if (m_locker != NULL)
        m_locker->lock();

    ClearErrorBuffer();
       
    lifesatremotehttp::HttpWebRequest* httpRequest = new lifesatremotehttp::HttpWebRequest(GetUrl());
       
    if (!m_httpClient.SendRequest(*httpRequest)) {
        status = LIFESAT_REMOTE_STATUS_CONNECTION_ERROR;
        WriteError("HTTP request failed with error code %d (%s).\n", status, GetStatusCodeDescription(status).c_str());
    }
    else {
        lifesatremotehttp::HttpWebResponse* httpResponse = m_httpClient.GetResponse();

        if (httpResponse->GetStatusCode() == 401) {
            status = LIFESAT_REMOTE_STATUS_UNAUTHORISED;
            WriteError("HTTP response returned status code %d (%s).\n", httpResponse->GetStatusCode(), GetStatusCodeDescription(status).c_str());
        }
        else if (httpResponse->GetStatusCode() != 200) {
            status = LIFESAT_REMOTE_STATUS_ERROR;
            WriteError("HTTP response returned status code %d.\n", httpResponse->GetStatusCode());
        }
        else {
            std::string responseData = httpResponse->GetResponseData();
            
            JSONExample source;
            source.text = "Hello JSON World";
            // create JSON from a producer
            std::string json = JSON::producer<JSONExample>::convert(source);
            // and then create a new instance from a consumer ...
            JSONExample sink = JSON::consumer<JSONExample>::convert(json);
            // we are done ...
            //json j3 = json::parse(responseData.c_str());
            // range-based for
            //mytoken m3 = j3;
            m_access_token = "NEM DOLGOZIK";
            
            // ns::from_json(j3, t2);
            //ns::mytoken t3 = j3;
            
           
                        

            

            //m_reader.parse(std::string(responseData), m_root);
        }

        delete httpResponse;
    }

    delete httpRequest;


    if (err_str != NULL)
    GetLastError(*err_str);

    if (m_locker != NULL)
    m_locker->unlock();

    return status;
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::SerializeRequestObject(const std::string& command, const Request& request, std::string& serializedXmlData)
{
  LifeSatRemoteStatusCode status = LIFESAT_REMOTE_STATUS_OK;

  if (!XmlObjectSerializerFactory::Serialize(command, request, serializedXmlData)) {
    status = LIFESAT_REMOTE_STATUS_INVALID_DATA;
  }

  return status;
}

LifeSatRemoteStatusCode LifeSatRemoteCommunication::DeserializeResponseData(const std::string& command, const std::string& responseData, Response& responseObject)
{
  LifeSatRemoteStatusCode status = LIFESAT_REMOTE_STATUS_OK;

  if (command == LIFESAT_REMOTE_GET_PLAYLIST_M3U_CMD) 
  {
    ((M3uPlaylist&)responseObject).FileContent.assign(responseData);
  }
  else
  {
    GenericResponseSerializer* genericResponseSerializer = new GenericResponseSerializer();
    GenericResponse* genericResponse = new GenericResponse();
    
    if (genericResponseSerializer->ReadObject(*genericResponse, responseData)) {
      if ((status = (LifeSatRemoteStatusCode)genericResponse->GetStatusCode()) == LIFESAT_REMOTE_STATUS_OK) {
        if (!XmlObjectSerializerFactory::Deserialize(command, genericResponse->GetXmlResult(), responseObject)) {
          status = LIFESAT_REMOTE_STATUS_INVALID_DATA;
        }
      }
    }

    delete genericResponse;
    delete genericResponseSerializer;
  }

  return status;
}

void LifeSatRemoteCommunication::WriteError(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  vsprintf_s(m_errorBuffer, format, args);
  va_end(args);
}

void LifeSatRemoteCommunication::ClearErrorBuffer()
{
  memset(m_errorBuffer, 0, lifesatremote::LIFESAT_REMOTE_EOF);
}
