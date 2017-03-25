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

    class LifesatRemoteApiCommunication
    {
    public:


    };
}
