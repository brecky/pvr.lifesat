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
#include "lifesatremotehttp.h"
#include "response.h"
#include "request.h"
#include "scheduling.h"
#include "version.h"

/**
  * Default namespace for LifeSat Remote API library.
  */
namespace lifesatremote 
{
  /**
    * A constant integer representing the default buffer size.
    */
  const int LIFESAT_REMOTE_DEFAULT_BUFFER_SIZE = 1024;

  /**
    * A constant char representing the EOF string.
    */
  const char LIFESAT_REMOTE_EOF = '\0';

  /**
    * A constant char representing the newline string.
    */
  const char LIFESAT_REMOTE_NEWLINE = '\n';

  /**
    * A constant string for the scheme used to communicate with LifeSat server.
    */
  const std::string LIFESAT_REMOTE_SERVER_URL_SCHEME = "http";

  /**
    * A constant string for the path specifying how to find the resource where LifeSat Remote API requests should be sent to.
    */
  const std::string LIFESAT_REMOTE_SERVER_URL_PATH = "cs/";

  /**
    * A constant string used to format a LifeSat server URL.
    * The default format is &lt;scheme&gt;://&lt;domain&gt;:&lt;port&gt;/&lt;path&gt;.
    * \remark Parameters will be interpreted in the following order:
    * 1. The value of <tt>LIFESAT_REMOTE_SERVER_URL_SCHEME</tt>.
    * 2. The domain/host address of LifeSat server.
    * 3. The port number specifies the base streaming port of LifeSat server.
    * 4. The value of <tt>LIFESAT_REMOTE_SERVER_URL_PATH</tt>.
    */
  const std::string LIFESAT_REMOTE_SERVER_URL_FORMAT = "%s://%s:%ld/%s";

  /**
    * A constant string representing the HTTP method used to communicate with the LifeSat Remote API.
    */
  const std::string LIFESAT_REMOTE_HTTP_METHOD = lifesatremotehttp::LIFESAT_REMOTE_HTTP_POST_METHOD;
  
  /**
    * A constant string representing the MIME type of the data sent via LifeSat Remote API requests.
    */
  const std::string LIFESAT_REMOTE_HTTP_CONTENT_TYPE = "application/x-www-form-urlencoded; charset=utf-8";

  /**
   * A constant string representing the name of the LifeSat command querystring used for data to be sent in a LifeSat Remote API request.
   */
  const std::string LIFESAT_REMOTE_HTTP_COMMAND_QUERYSTRING = "command";
  
  /**
   * A constant string representing the name of the LifeSat xml data querystring used for data to be sent in a LifeSat Remote API request.
   */
  const std::string LIFESAT_REMOTE_HTTP_XML_PARAM_QUERYSTRING = "xml_param";

  /**
  * A constant string representing the LifeSat command for retrieving channels.
  */
  const std::string LIFESAT_REMOTE_GET_TOKEN_CMD = "oauth/token";

  /**
    * A constant string representing the LifeSat command for retrieving channels. 
    */
  const std::string LIFESAT_REMOTE_GET_CHANNELS_CMD = "get_channels";

  /**
    * A constant string representing the LifeSat command for playing a channel. 
    */
  const std::string LIFESAT_REMOTE_PLAY_CHANNEL_CMD = "play_channel";

  /**
    * A constant string representing the LifeSat command for stopping one or several playing channels. 
    */
  const std::string LIFESAT_REMOTE_STOP_CHANNEL_CMD = "stop_channel";

   /**
    * A constant string representing the LifeSat command for searching the electronic program guide (EPG). 
    */
  const std::string LIFESAT_REMOTE_SEARCH_EPG_CMD = "search_epg";

  /**
    * A constant string representing the LifeSat command for retrieving recordings. 
    */
  const std::string LIFESAT_REMOTE_GET_RECORDINGS_CMD = "get_recordings";

  /**
    * A constant string representing the LifeSat command for adding a recording schedule. 
    */
  const std::string LIFESAT_REMOTE_ADD_SCHEDULE_CMD = "add_schedule";

  /**
    * A constant string representing the LifeSat command for removing a recording schedule. 
    */
  const std::string LIFESAT_REMOTE_REMOVE_SCHEDULE_CMD = "remove_schedule";

  /**
    * A constant string representing the LifeSat command for removing a recording. 
    */
  const std::string LIFESAT_REMOTE_REMOVE_RECORDING_CMD = "remove_recording";

  /**
    * A constant string representing the LifeSat command for setting a parental lock. 
    */
  const std::string LIFESAT_REMOTE_SET_PARENTAL_LOCK_CMD = "set_parental_lock";

  /**
    * A constant string representing the LifeSat command for retrieving parental lock status. 
    */
  const std::string LIFESAT_REMOTE_GET_PARENTAL_STATUS_CMD = "get_parental_status";

  /**
    * A constant string representing the LifeSat command for retrieving schedules. 
    */
  const std::string LIFESAT_REMOTE_GET_SCHEDULES_CMD = "get_schedules";

  /**
    * A constant string representing the LifeSat command for updating a schedule. 
    */
  const std::string LIFESAT_REMOTE_UPDATE_SCHEDULE_CMD = "update_schedule";

  /**
    * A constant string representing the LifeSat command for retrieving a M3U playlist of channels. 
    */
  const std::string LIFESAT_REMOTE_GET_PLAYLIST_M3U_CMD = "get_playlist_m3u";

  /**
    * A constant string representing the LifeSat command for retrieving a playlist object. 
    */
  const std::string LIFESAT_REMOTE_GET_OBJECT_CMD = "get_object";

  /**
    * A constant string representing the LifeSat command for removing a playlist object. 
    */
  const std::string LIFESAT_REMOTE_REMOVE_OBJECT_CMD = "remove_object";

  /**
    * A constant string representing the LifeSat command for stopping an active recording. 
    */
  const std::string LIFESAT_REMOTE_STOP_RECORDING_CMD = "stop_recording";

  /**
    * A constant string representing the LifeSat command for retrieving streaming capabilities. 
    */
  const std::string LIFESAT_REMOTE_GET_STREAMING_CAPABILITIES_CMD = "get_streaming_capabilities";

  /**
    * A constant string representing the LifeSat command for retrieving recording settings. 
    */
  const std::string LIFESAT_REMOTE_GET_RECORDING_SETTINGS_CMD = "get_recording_settings";

  /**
    * A constant string representing the LifeSat command for setting recording settings. 
    */
  const std::string LIFESAT_REMOTE_SET_RECORDING_SETTING_CMD = "set_recording_settings";

  /**
  * A constant string representing the LifeSat command for retrieving channel favorites lists.
  */
  const std::string LIFESAT_REMOTE_GET_FAVORITES_CMD = "get_favorites";

  /**
  * A constant string representing the LifeSat command for retrieving server information.
  */
  const std::string LIFESAT_REMOTE_GET_SERVER_INFO_CMD = "get_server_info";

  /**
    * A constant string representing a Real Time Transport Protocol stream type for Android devices.
    */
  const std::string LIFESAT_REMOTE_STREAM_TYPE_ANDROID = "rtp";

  /**
  * A constant string representing a MP4 stream type.
  */
  const std::string LIFESAT_REMOTE_STREAM_TYPE_MP4 = "mp4";

  /**
  * A constant string representing transport stream, transcoded to use h264 video and aac audio, with timeshifting capabilities.
  */
  const std::string LIFESAT_REMOTE_STREAM_TYPE_H264TS_HTTP_TIMESHIFT = "h264ts_http_timeshift";

  /**
  * A constant string representing transport stream, transcoded to use h264 video and aac audio.
  */
  const std::string LIFESAT_REMOTE_STREAM_TYPE_H264TS = "h264ts";

  /**
    * A constant string representing a Http Live stream type for IOS devices.
    */
  const std::string LIFESAT_REMOTE_STREAM_TYPE_IPHONE = "hls";

  /**
    * A constant string representing a Windows Media stream type for Windows phone devices.
    */
  const std::string LIFESAT_REMOTE_STREAM_TYPE_WINPHONE = "asf";

  /**
    * A constant string representing a Raw HTTP stream type.
    */
  const std::string LIFESAT_REMOTE_STREAM_TYPE_RAW_HTTP = "raw_http";

  /**
    * A constant string representing a Raw HTTP stream type with timeshifting capabilities.
    */
  const std::string LIFESAT_REMOTE_STREAM_TYPE_RAW_HTTP_TIMESHIFT = "raw_http_timeshift";

  /**
    * A constant string representing a Raw UDP stream type.
    */
  const std::string LIFESAT_REMOTE_STREAM_TYPE_RAW_UDP = "raw_udp";

  /**
    * An enum representing the different status codes that LifeSat Remote API request could return.
    */
  enum LifeSatRemoteStatusCode
  {
    LIFESAT_REMOTE_STATUS_OK = 0, /**< LifeSat Remote API command was successful. */ 
    LIFESAT_REMOTE_STATUS_ERROR = 1000, /**< An unspecified error occurred. */ 
    LIFESAT_REMOTE_STATUS_INVALID_DATA = 1001, /**< Invalid request data provided. */ 
    LIFESAT_REMOTE_STATUS_INVALID_PARAM = 1002, /**< Invalid request parameter provided. */ 
    LIFESAT_REMOTE_STATUS_NOT_IMPLEMENTED = 1003, /**< An invalid command was provied to the LifeSat Remote API. */
    LIFESAT_REMOTE_STATUS_MC_NOT_RUNNING = 1005, /**< Windows Media Center is not running. */
    LIFESAT_REMOTE_STATUS_NO_DEFAULT_RECORDER = 1006, /**< No default recorder is configured. */
    LIFESAT_REMOTE_STATUS_MCE_CONNECTION_ERROR = 1008, /**< An error occurred when trying to establish a connection to Windows Media Center. */
    LIFESAT_REMOTE_STATUS_CONNECTION_ERROR = 2000,  /**< An error occurred when trying to connect to the LifeSat Connect! Server. */
    LIFESAT_REMOTE_STATUS_UNAUTHORISED = 2001 /**< An authentication error occurred when trying to establish a connection to the LifeSat Connect! Server. */
  };

  /**
    * A constant string representing a description of the LifeSat Remote API status code <tt>LIFESAT_REMOTE_STATUS_OK</tt>.
    * @see LifeSatRemoteStatusCode
    */
  const std::string LIFESAT_REMOTE_STATUS_DESC_OK = "LifeSat Remote API command was successful";

  /**
    * A constant string representing a description of the LifeSat Remote API status code <tt>LIFESAT_REMOTE_STATUS_ERROR</tt>.
    * @see LifeSatRemoteStatusCode
    */
  const std::string LIFESAT_REMOTE_STATUS_DESC_ERROR = "An unspecified error occurred";

  /**
    * A constant string representing a description of the LifeSat Remote API status code <tt>LIFESAT_REMOTE_STATUS_INVALID_DATA</tt>.
    * @see LifeSatRemoteStatusCode
    */
  const std::string LIFESAT_REMOTE_STATUS_DESC_INVALID_DATA = "Invalid request data provided";

  /**
    * A constant string representing a description of the LifeSat Remote API status code <tt>LIFESAT_REMOTE_STATUS_INVALID_PARAM</tt>.
    * @see LifeSatRemoteStatusCode
    */
  const std::string LIFESAT_REMOTE_STATUS_DESC_INVALID_PARAM = "Invalid request parameter provided";

  /**
    * A constant string representing a description of the LifeSat Remote API status code <tt>LIFESAT_REMOTE_STATUS_NOT_IMPLEMENTED</tt>.
    * @see LifeSatRemoteStatusCode
    */
  const std::string LIFESAT_REMOTE_STATUS_DESC_NOT_IMPLEMENTED = "An invalid command was provided to the LifeSat Remote API";

  /**
    * A constant string representing a description of the LifeSat Remote API status code <tt>LIFESAT_REMOTE_STATUS_MC_NOT_RUNNING</tt>.
    * @see LifeSatRemoteStatusCode
    */
  const std::string LIFESAT_REMOTE_STATUS_DESC_MC_NOT_RUNNING = "Windows Media Center is not running";

  /**
    * A constant string representing a description of the LifeSat Remote API status code <tt>LIFESAT_REMOTE_STATUS_NO_DEFAULT_RECORDER</tt>.
    * @see LifeSatRemoteStatusCode
    */
  const std::string LIFESAT_REMOTE_STATUS_DESC_NO_DEFAULT_RECORDER = "No default recorder is configured";

  /**
    * A constant string representing a description of the LifeSat Remote API status code <tt>LIFESAT_REMOTE_STATUS_MCE_CONNECTION_ERROR</tt>.
    * @see LifeSatRemoteStatusCode
    */
  const std::string LIFESAT_REMOTE_STATUS_DESC_MCE_CONNECTION_ERROR = "An error occurred when trying to establish a connection to Windows Media Center";

  /**
    * A constant string representing a description of the LifeSat Remote API status code <tt>LIFESAT_REMOTE_STATUS_CONNECTION_ERROR</tt>.
    * @see LifeSatRemoteStatusCode
    */
  const std::string LIFESAT_REMOTE_STATUS_DESC_CONNECTION_ERROR = "An error occurred when trying to establish a connection to the LifeSat Connect! Server";

  /**
    * A constant string representing a description of the LifeSat Remote API status code <tt>LIFESAT_REMOTE_STATUS_UNAUTHORISED</tt>.
    * @see LifeSatRemoteStatusCode
    */
  const std::string LIFESAT_REMOTE_STATUS_DESC_UNAUTHORIZED = "An authentication error occurred when trying to establish a connection to the LifeSat Connect! Server";

  /**
    * Interface representing the available LifeSat Remote API methods. 
    * This is the interface for communicating with a LifeSat Connect! server. This 
    * class is abstract.
    */
  class ILifeSatRemoteConnection
  {
  public:
    virtual ~ILifeSatRemoteConnection();
    
    /**
      * Gets a list of all available channels.
      * @param[in]      request   A constant GetChannelsRequest reference representing the get channel request criterias.
      * @param[in,out]  response  A ChannelList reference that will be populated with channels.
      * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode GetChannels(const GetChannelsRequest& request, ChannelList& response, std::string* err_str) = 0;

    /**
      * Search the electronic program guide (EPG).
      * @param[in]      request   A constant GetChannelsRequest reference representing the EPG search request criterias.
      * @param[in,out]  response  A EpgSearchResult reference that will be populated with ChannelEPGData objects.
      * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode SearchEpg(const EpgSearchRequest& request, EpgSearchResult& response, std::string* err_str) = 0;

    /**
      * Start stream of a channel.
      * @param[in]      request   A constant StreamRequest reference representing the stream request criterias.
      * @param[in,out]  response  A Stream reference that will be populated with details of a playing stream.
      * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode PlayChannel(const StreamRequest& request, Stream& response, std::string* err_str) = 0;

    /**
      * Stop a streaming channel or channels.
      * @param[in] request A constant StopStreamRequest reference representing the stop stream request criterias.
      * @return            A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode StopChannel(const StopStreamRequest& request, std::string* err_str) = 0;

    /**
      * Add a schedule.
      * @param[in] request A constant AddScheduleRequest reference representing the add schedule request criterias.
      * @return            A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode AddSchedule(const AddScheduleRequest& request, std::string* err_str) = 0;

    /**
      * Gets a list of all schedules.
      * @param[in]      request   A constant GetSchedulesRequest reference representing the get schedules request criterias.
      * @param[in,out]  response  A ScheduleList reference that will be populated with Schedule objects.
      * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode GetSchedules(const GetSchedulesRequest& request, StoredSchedules& response, std::string* err_str) = 0;
    
    /**
      * Update a schedule.
      * @param[in] request A constant UpdateScheduleReqest reference representing the update schedule request criterias.
      * @return            A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode UpdateSchedule(const UpdateScheduleRequest& request, std::string* err_str) = 0;

    /**
      * Remove a schedule.
      * @param[in] request A constant RemoveScheduleRequest reference representing the remove schedule request criterias.
      * @return            A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode RemoveSchedule(const RemoveScheduleRequest& request, std::string* err_str) = 0;

    /**
      * Gets a list of all recordings.
      * @param[in]      request   A constant GetRecordingsRequest reference representing the get recordings request criterias.
      * @param[in,out]  response  A RecordingList reference that will be populated with Recording objects.
      * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode GetRecordings(const GetRecordingsRequest& request, RecordingList& response, std::string* err_str) = 0;

    /**
      * Removes a recording.
      * @param[in] request A constant RemoveRecordingRequest reference representing the remove recording request criterias.
      * @return            A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode RemoveRecording(const RemoveRecordingRequest& request, std::string* err_str) = 0;

    /**
      * Get parental status.
      * @param[in]      request   A constant GetParentalStatusRequest reference representing the get parental status request criterias.
      * @param[in,out]  response  A ParentalStatus reference that will be populated with parental status details.
      * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode GetParentalStatus(const GetParentalStatusRequest& request, ParentalStatus& response, std::string* err_str) = 0;

    /**
      * Sets the parental lock.
      * @param[in]      request   A constant SetParentalLockRequest reference representing the set parental lock request criterias.
      * @param[in,out]  response  A ParentalStatus reference that will be populated with parental status details.
      * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode SetParentalLock(const SetParentalLockRequest& request, ParentalStatus& response, std::string* err_str) = 0;

    /**
      * Gets a M3U playlist with direct HTTP links to all channels.
      * @param[in]      request   A constant GetM3uPlaylistRequest reference representing the get M3U playlist request criterias.
      * @param[in,out]  response  A M3uPlaylist reference that will be populated with M3U playlist file content.
      * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode GetM3uPlaylist(const GetM3uPlaylistRequest& request, M3uPlaylist& response, std::string* err_str) = 0;

    /**
      * Gets a playback object.
      * @param[in]      request   A constant GetPlaybackObjectRequest reference representing the get playback object request criterias.
      * @param[in,out]  response  A GetObjectResult reference that will be populated with playback object details.
      * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode GetPlaybackObject(const GetPlaybackObjectRequest& request, GetPlaybackObjectResponse& response, std::string* err_str) = 0;
    
    /**
      * Remove a playback object.
      * @param[in] request A constant RemovePlaybackObjectRequest reference representing the remove playback object request criterias.
      * @return            A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode RemovePlaybackObject(const RemovePlaybackObjectRequest& request, std::string* err_str) = 0;

    /**
      * Stops a recording.
      * @param[in] request A constant StopRecordingRequest reference representing the stop recording request criterias.
      * @return            A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode StopRecording(const StopRecordingRequest& request, std::string* err_str) = 0;

    /**
      * Gets streams and protocols actually supported by a given instance of LifeSat server.
      * @param[in]      request   A constant GetStreamingCapabilitiesRequest reference representing the get streaming capabilities request criterias.
      * @param[in,out]  response  A StreamingCapabilities reference that will be populated with streaming capability details.
      * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode GetStreamingCapabilities(const GetStreamingCapabilitiesRequest& request, StreamingCapabilities& response, std::string* err_str) = 0;

    /**
      * Gets recording settings.
      * @param[in]      request   A constant GetRecordingSettingsRequest reference representing the get recording settings request criterias.
      * @param[in,out]  response  A RecordingSettings reference that will be populated with recording settings details.
      * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode GetRecordingSettings(const GetRecordingSettingsRequest& request, RecordingSettings& response, std::string* err_str) = 0;

    /**
      * Sets the recording settings.
      * @param[in] request A constant SetRecordingSettingsRequest reference representing the set recording settings request criterias.
      * @return            A LifeSatRemoteStatusCode representing the status of the executed method.
      */
    virtual LifeSatRemoteStatusCode SetRecordingSettings(const SetRecordingSettingsRequest& request, std::string* err_str) = 0;

    /**
    * Gets favorites lists.
    * @param[in]      request   A constant GetFavoritesRequest reference representing the get favorites request criterias.
    * @param[in,out]  response  A ChannelFavorites reference that will be populated with channel favorites.
    * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
    */
    virtual LifeSatRemoteStatusCode GetFavorites(const GetFavoritesRequest& request, ChannelFavorites& response, std::string* err_str) = 0;

    /**
    * Gets server information - id, version and build number.
    * @param[in]      request   A constant GetServerInfoRequest reference representing the get server info request criterias.
    * @param[in,out]  response  A ServerInfo reference that will be populated with server information.
    * @return                   A LifeSatRemoteStatusCode representing the status of the executed method.
    */
    virtual LifeSatRemoteStatusCode GetServerInfo(const GetServerInfoRequest& request, ServerInfo& response, std::string* err_str) = 0;

    
    virtual LifeSatRemoteStatusCode GetToken(const GetTokenRequest& request, Token& response, std::string* err_str) = 0;

    /**
      * Gets a description of the last occured error.
      * @param[in,out] err A string reference representing the string where the description of the last error will be provided.
      */
    virtual void GetLastError(std::string& err) = 0;
  };


  class LifeSatRemoteLocker
  {
    public:
        LifeSatRemoteLocker() {}
        virtual ~LifeSatRemoteLocker() {}

        virtual void lock() {}
        virtual void unlock() {}
  };

  /**
    * Class used for connecting to a LifeSat Connect! server.
    */
  class LifeSatRemote
  {
  public:
    /**
      * Connect to a LifeSat Connect! server and recieve a ILifeSatRemoteConnection instance for executing LifeSat Remote API methods against it.
      * @param[in] httpClient   A lifesatremotehttp::HttpClient reference to be used for sending and recieving HTTP requests/responses to/from the LifeSat Connect! server.
      * @param[in] hostAddress  A constanst string reference representing the host address of the LifeSat Connect! server.
      * @param[in] port         A constanst long representing the base streaming port of the LifeSat Connect! server.
      */
      static ILifeSatRemoteConnection* Connect(lifesatremotehttp::HttpClient& httpClient, const std::string& hostAddress, const long port, LifeSatRemoteLocker* locker);

    /**
      * Connect to a LifeSat Connect! server and recieve a ILifeSatRemoteConnection instance for executing LifeSat Remote API methods against it.
      * @param[in] httpClient   A lifesatremotehttp::HttpClient reference to be used for sending and recieving HTTP requests/responses to/from the LifeSat Connect! server.
      * @param[in] hostAddress  A constanst string reference representing the host address of the LifeSat Connect! server.
      * @param[in] port         A constanst long representing the base streaming port of the LifeSat Connect! server.
      * @param[in] username     A constanst string reference representing the user name to be used for authentication towards the LifeSat Connect! server.
      * @param[in] password     A constanst string reference representing the password to be used for authentication towards the LifeSat Connect! server.
      */
      static ILifeSatRemoteConnection* Connect(lifesatremotehttp::HttpClient& httpClient, const std::string& hostAddress, const long port, const std::string& username, const std::string& password, const std::string& client_id, const std::string& client_secret, LifeSatRemoteLocker* locker);

    /**
      * Gets the copyright notice of the LifeSat Remote API library.
      * @param[in,out] copyright A string reference representing the string where the copyright notice will be provided.
      */
    static void GetCopyrightNotice(std::string& copyright);

    /**
      * Gets the version information of the LifeSat Remote API library.
      * @param[in,out] version A string reference representing the string where the version information will be provided.
      */
    static void GetVersion(std::string& version);

    /**
      * Gets the version numbers of the LifeSat Remote API library.
      * @param[in,out] major An integer reference representing the integer where the major version information will be provided.
      * @param[in,out] minor An integer reference representing the integer where the minor version information will be provided.
      * @param[in,out] patch An integer reference representing the integer where the patch version information will be provided.
      */
    static void GetVersion(int& major, int& minor, int& patch);
  };
};
