//
// Created by lezenn on 31/05/2020.
//

#ifndef SPECTRAL_HTTPPARSER_H
#define SPECTRAL_HTTPPARSER_H

#include <string>
#include "HTTPMethod.h"

namespace queries {
    class HTTPParser
    {
    public:
        explicit HTTPParser(std::string request);
        ~HTTPParser();

        HTTPMethod getMethod() const;
        std::string getPath() const;

        std::string to_string() const;
    private:
        HTTPMethod m_method;
        std::string m_path;
    };
}

#endif //SPECTRAL_HTTPPARSER_H
