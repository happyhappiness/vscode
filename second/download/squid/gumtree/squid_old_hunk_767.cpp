
/*
 *
 * SQUID Web Proxy Cache          http://www.squid-cache.org/
 * ----------------------------------------------------------
 *
 *  Squid is the result of efforts by numerous individuals from
 *  the Internet community; see the CONTRIBUTORS file for full
 *  details.   Many organizations have provided support for Squid's
 *  development; see the SPONSORS file for full details.  Squid is
 *  Copyrighted (C) 2001 by the Regents of the University of
 *  California; see the COPYRIGHT file for full details.  Squid
 *  incorporates software developed and/or copyrighted by other
 *  sources; see the CREDITS file for full details.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 *
 * Copyright (c) 2003, Robert Collins <robertc@squid-cache.org>
 */

#include "squid.h"
#include "cache_cf.h"
#include "ConfigParser.h"
#include "Debug.h"
#include "fatal.h"
#include "globals.h"

char *ConfigParser::lastToken = NULL;
std::queue<std::string> ConfigParser::undo;

int ConfigParser::RecognizeQuotedValues = true;

void
ConfigParser::destruct()
{
    shutting_down = 1;
    fatalf("Bungled %s line %d: %s",
           cfg_filename, config_lineno, config_input_line);
}

void
ConfigParser::strtokFileUndo()
{
    assert(lastToken);
    undo.push(lastToken);
}

void
ConfigParser::strtokFilePutBack(const char *tok)
{
    assert(tok);
    undo.push(tok);
}

char *
xstrtok(char *str, const char *delimiters)
{
    assert(!str); // we are parsing the configuration file
    // no support unless enabled in the configuration and
    // no support for other delimiters (they may need to be eradicated!)
    return (ConfigParser::RecognizeQuotedValues &&
            strcmp(delimiters, " \t\n\r") == 0) ?
           ConfigParser::NextToken() : ::strtok(str, delimiters);
}

char *
ConfigParser::strtokFile(void)
{
    static int fromFile = 0;
    static FILE *wordFile = NULL;
    LOCAL_ARRAY(char, undoToken, CONFIG_LINE_LIMIT);

    char *t, *fn;
    LOCAL_ARRAY(char, buf, CONFIG_LINE_LIMIT);

    if (!undo.empty()) {
        strncpy(undoToken, undo.front().c_str(), sizeof(undoToken));
        undoToken[sizeof(undoToken) - 1] = '\0';
        undo.pop();
        return lastToken = undoToken;
    }

    if (RecognizeQuotedValues)
        return lastToken = ConfigParser::NextToken();

    lastToken = NULL;
    do {

        if (!fromFile) {
            t = (strtok(NULL, w_space));

            if (!t || *t == '#') {
                return NULL;
            } else if (*t == '\"' || *t == '\'') {
                /* quote found, start reading from file */
                fn = ++t;

                while (*t && *t != '\"' && *t != '\'')
                    ++t;

                *t = '\0';

                if ((wordFile = fopen(fn, "r")) == NULL) {
                    debugs(28, DBG_CRITICAL, "strtokFile: " << fn << " not found");
                    return (NULL);
                }

#if _SQUID_WINDOWS_
                setmode(fileno(wordFile), O_TEXT);
#endif

                fromFile = 1;
            } else {
                return lastToken = t;
            }
        }

        /* fromFile */
        if (fgets(buf, CONFIG_LINE_LIMIT, wordFile) == NULL) {
            /* stop reading from file */
