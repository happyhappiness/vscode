/*
 * Copyright (C) 1996-2017 The Squid Software Foundation and contributors
 *
 * Squid software is distributed under GPLv2+ license and includes
 * contributions from numerous individuals and organizations.
 * Please see the COPYING and CONTRIBUTORS files for details.
 */

#include "squid.h"
#include "cache_cf.h"
#include "ConfigParser.h"
#include "Debug.h"
#include "fatal.h"
#include "globals.h"

bool ConfigParser::RecognizeQuotedValues = true;
bool ConfigParser::StrictMode = true;
std::stack<ConfigParser::CfgFile *> ConfigParser::CfgFiles;
ConfigParser::TokenType ConfigParser::LastTokenType = ConfigParser::SimpleToken;
const char *ConfigParser::CfgLine = NULL;
const char *ConfigParser::CfgPos = NULL;
std::queue<char *> ConfigParser::CfgLineTokens_;
std::queue<std::string> ConfigParser::Undo_;
bool ConfigParser::AllowMacros_ = false;
bool ConfigParser::ParseQuotedOrToEol_ = false;
bool ConfigParser::RecognizeQuotedPair_ = false;
bool ConfigParser::PreviewMode_ = false;

static const char *SQUID_ERROR_TOKEN = "[invalid token]";

void
ConfigParser::destruct()
{
    shutting_down = 1;
    if (!CfgFiles.empty()) {
        std::ostringstream message;
        CfgFile *f = CfgFiles.top();
        message << "Bungled " << f->filePath << " line " << f->lineNo <<
                ": " << f->currentLine << std::endl;
        CfgFiles.pop();
        delete f;
        while (!CfgFiles.empty()) {
            f = CfgFiles.top();
            message << " included from " << f->filePath << " line " <<
                    f->lineNo << ": " << f->currentLine << std::endl;
            CfgFiles.pop();
            delete f;
        }
        message << " included from " <<  cfg_filename << " line " <<
                config_lineno << ": " << config_input_line << std::endl;
        std::string msg = message.str();
        fatalf("%s", msg.c_str());
    } else
        fatalf("Bungled %s line %d: %s",
               cfg_filename, config_lineno, config_input_line);
}

void
ConfigParser::TokenPutBack(const char *tok)
{
    assert(tok);
    Undo_.push(tok);
}

char *
ConfigParser::Undo()
{
    LOCAL_ARRAY(char, undoToken, CONFIG_LINE_LIMIT);
    if (!Undo_.empty()) {
        strncpy(undoToken, Undo_.front().c_str(), sizeof(undoToken));
        undoToken[sizeof(undoToken) - 1] = '\0';
        if (!PreviewMode_)
            Undo_.pop();
        return undoToken;
    }
    return NULL;
}

char *
ConfigParser::strtokFile()
{
    if (RecognizeQuotedValues)
        return ConfigParser::NextToken();

    static int fromFile = 0;
    static FILE *wordFile = NULL;

    char *t;
    LOCAL_ARRAY(char, buf, CONFIG_LINE_LIMIT);

    if ((t = ConfigParser::Undo()))
        return t;

    do {

        if (!fromFile) {
            ConfigParser::TokenType tokenType;
            t = ConfigParser::NextElement(tokenType);
            if (!t) {
                return NULL;
            } else if (*t == '\"' || *t == '\'') {
                /* quote found, start reading from file */
                debugs(3, 8,"Quoted token found : " << t);
                char *fn = ++t;

                while (*t && *t != '\"' && *t != '\'')
                    ++t;

                *t = '\0';

                if ((wordFile = fopen(fn, "r")) == NULL) {
                    debugs(3, DBG_CRITICAL, "ERROR: Can not open file " << fn << " for reading");
                    return NULL;
                }

#if _SQUID_WINDOWS_
                setmode(fileno(wordFile), O_TEXT);
#endif

                fromFile = 1;
            } else {
                return t;
            }
        }

        /* fromFile */
        if (fgets(buf, CONFIG_LINE_LIMIT, wordFile) == NULL) {
            /* stop reading from file */
