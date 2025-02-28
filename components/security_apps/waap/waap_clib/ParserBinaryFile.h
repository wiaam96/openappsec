// Copyright (C) 2022 Check Point Software Technologies Ltd. All rights reserved.

// Licensed under the Apache License, Version 2.0 (the "License");
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __PARSER_BINARY_FILE_H__
#define __PARSER_BINARY_FILE_H__

#include "ParserBase.h"
#include "Waf2Util.h"
#include <string.h>

#define MIN_HEADER_LOOKUP 16
#define MAX_HEADER_LOOKUP 64
#define MAX_TAIL_LOOKUP 5

class ParserBinaryFile : public ParserBase {
public:
    static Waap::Util::BinaryFileType detectBinaryFileHeader(const std::string &buf);

    ParserBinaryFile(
        IParserStreamReceiver &receiver,
        size_t parser_depth,
        bool is_base64,
        Waap::Util::BinaryFileType file_type);
    virtual ~ParserBinaryFile();
    virtual size_t push(const char *buf, size_t len);
    virtual void finish();
    virtual const std::string &name() const;
    virtual bool error() const;
    virtual size_t depth() { return 1; }

private:
    enum state {
        s_start,
        s_body,
        s_end,
        s_error
    };

    IParserStreamReceiver &m_receiver;
    enum state m_state;
    static const std::string m_parserName;
    size_t m_parser_depth;
    bool m_is_base64;
    Waap::Util::BinaryFileType m_file_type;
};

#endif // __PARSER_BINARY_FILE_H__
