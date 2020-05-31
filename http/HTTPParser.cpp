//
// Created by lezenn on 31/05/2020.
//

#include <iostream>
#include "HTTPParser.h"

queries::HTTPParser::HTTPParser(std::string request)
{
    int first_space = request.find(' ');
    if (request.substr(0, first_space) == "GET")
        m_method = HTTPMethod::GET;
    else if (request.substr(0, first_space) == "POST")
        m_method = HTTPMethod::POST;
    else
    {
        std::cerr << "Failed to parse Method of : \n" << request << std::endl;
    }

    std::string next = request.substr(first_space + 1);
    first_space = next.find(' ');
    m_path = next.substr(0, first_space);
}

queries::HTTPParser::~HTTPParser()
{}

queries::HTTPMethod queries::HTTPParser::getMethod() const
{
    return m_method;
}

std::string queries::HTTPParser::getPath() const
{
    return m_path;
}

std::string queries::HTTPParser::to_string() const
{
    std::string method = "";
    if (m_method == HTTPMethod::GET)
        method = "GET";
    else if (m_method == HTTPMethod::POST)
        method = "POST";

    return "REQUEST : " + method + " :: " + m_path;
}
