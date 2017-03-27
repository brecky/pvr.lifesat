PROJECT(lifesatremote)

ENABLE_LANGUAGE(CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(SOURCES channel.cpp
            lifesatremoteconnection.h
            lifesatremotecommunication.cpp
            lifesatremote.h
            lifesatremote.cpp
            lifesatremotehttp.h
            lifesatremotehttp.cpp
            epg.cpp
            favorites.cpp
            generic_response.h
            generic_response.cpp
            item_metadata.cpp
            m3u_playlist.cpp
            parental_lock.cpp
            playback_container.cpp
            playback_item.cpp
            playback_object.cpp
            program.cpp
            recording.cpp
            recording_settings.cpp
            remove_playback_object_request.cpp
            server_info.cpp
            scheduling.h
            scheduling.cpp
            stop_stream_request.cpp
            stream.cpp
            streaming_capabilities.cpp
            stream_request.cpp
            transcoded_video_stream_request.cpp
            transcoding_options.cpp
            util.h
            util.cpp
            xml_object_serializer.h
            xml_object_serializer_factory.cpp
            lifesatremoteserialization.h
            request.h
            version.h
            response.h
            response.cpp)

if(NOT WIN32)
  add_options(ALL_LANGUAGES ALL_BUILDS "-fPIC")
endif()
ADD_LIBRARY(lifesatremote STATIC ${SOURCES})

if(WIN32)
  target_link_libraries(lifesatremote ws2_32)
endif()
