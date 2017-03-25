#pragma once
#include "request.h"
#include "response.h"
#include "xml_object_serializer.h"
using namespace lifesatremote;
using namespace lifesatremoteserialization;

GetTokenRequest::GetTokenRequest()
{

}

GetTokenRequest::~GetTokenRequest()
{

}

Token::Token()
{
  
}

Token::~Token()
{
    
}


Token::Token(Token& token)
{
    m_access_token = token.m_access_token;
    m_expiried = token.m_expiried;
    m_refress_token = token.m_refress_token;
}

std::string& Token::GetAccessToken()
{
    return  m_access_token;
}

long Token::GetExpiried()
{
    return  m_expiried;
}

std::string& Token::GetRefressToken()
{
    return m_refress_token;
}

