int
HttpParser::parseRequestFirstLine()
{
    int second_word = -1; // track the suspected URI start
    int first_whitespace = -1, last_whitespace = -1; // track the first and last SP byte
    int line_end = -1; // tracks the last byte BEFORE terminal \r\n or \n sequence

    debugs(74, 5, HERE << "parsing possible request: " << buf);

    // Single-pass parse: (provided we have the whole line anyways)

    req_start = 0;
    if (Config.onoff.relaxed_header_parser) {
        if (Config.onoff.relaxed_header_parser < 0 && buf[req_start] == ' ')
            debugs(74, DBG_IMPORTANT, "WARNING: Invalid HTTP Request: " <<
                   "Whitespace bytes received ahead of method. " <<
                   "Ignored due to relaxed_header_parser.");
        // Be tolerant of prefix spaces (other bytes are valid method values)
        for (; req_start < bufsiz && buf[req_start] == ' '; req_start++);
    }
    req_end = -1;
    for (int i = 0; i < bufsiz; i++) {
        // track first and last whitespace (SP only)
        if (buf[i] == ' ') {
            last_whitespace = i;
            if (first_whitespace < req_start)
                first_whitespace = i;
        }

        // track next non-SP/non-HT byte after first_whitespace
        if (second_word < first_whitespace && buf[i] != ' ' && buf[i] != '\t') {
            second_word = i;
        }

        // locate line terminator
        if (buf[i] == '\n') {
            req_end = i;
            line_end = i - 1;
            break;
        }
        if (i < bufsiz - 1 && buf[i] == '\r') {
            if (Config.onoff.relaxed_header_parser) {
                if (Config.onoff.relaxed_header_parser < 0 && buf[i + 1] == '\r')
                    debugs(74, DBG_IMPORTANT, "WARNING: Invalid HTTP Request: " <<
                           "Series of carriage-return bytes received prior to line terminator. " <<
                           "Ignored due to relaxed_header_parser.");

                // Be tolerant of invalid multiple \r prior to terminal \n
                if (buf[i + 1] == '\n' || buf[i + 1] == '\r')
                    line_end = i - 1;
                while (i < bufsiz - 1 && buf[i + 1] == '\r')
                    i++;

                if (buf[i + 1] == '\n') {
                    req_end = i + 1;
                    break;
                }
            } else {
                if (buf[i + 1] == '\n') {
                    req_end = i + 1;
                    line_end = i - 1;
                    break;
                }
            }

            // RFC 2616 section 5.1
            // "No CR or LF is allowed except in the final CRLF sequence"
            return -1;
        }
    }
    if (req_end == -1) {
        debugs(74, 5, "Parser: retval 0: from " << req_start <<
               "->" << req_end << ": needs more data to complete first line.");
        return 0;
    }

    // NP: we have now seen EOL, more-data (0) cannot occur.
    //     From here on any failure is -1, success is 1


    // Input Validation:

    // Process what we now know about the line structure into field offsets
    // generating HTTP status for any aborts as we go.

    // First non-whitespace = beginning of method
    if (req_start > line_end) {
        return -1;
    }
    m_start = req_start;

    // First whitespace = end of method
    if (first_whitespace > line_end || first_whitespace < req_start) {
        return -1;
    }
    m_end = first_whitespace - 1;
    if (m_end < m_start) {
        return -1;
    }

    // First non-whitespace after first SP = beginning of URL+Version
    if (second_word > line_end || second_word < req_start) {
        return -1;
    }
    u_start = second_word;

    // RFC 1945: SP and version following URI are optional, marking version 0.9
    // we identify this by the last whitespace being earlier than URI start
    if (last_whitespace < second_word && last_whitespace >= req_start) {
        v_maj = 0;
        v_min = 9;
        u_end = line_end;
        return 1;
    } else {
        // otherwise last whitespace is somewhere after end of URI.
        u_end = last_whitespace;
        // crop any trailing whitespace in the area we think of as URI
        for (; u_end >= u_start && xisspace(buf[u_end]); u_end--);
    }
    if (u_end < u_start) {
        return -1;
    }

    // Last whitespace SP = before start of protocol/version
    if (last_whitespace >= line_end) {
        return -1;
    }
    v_start = last_whitespace + 1;
    v_end = line_end;

    // We only accept HTTP protocol requests right now.
    // TODO: accept other protocols; RFC 2326 (RTSP protocol) etc
    if ((v_end - v_start +1) < 5 || strncasecmp(&buf[v_start], "HTTP/", 5) != 0) {
#if USE_HTTP_VIOLATIONS
        // being lax; old parser accepted strange versions
        // there is a LOT of cases which are ambiguous, therefore we cannot use relaxed_header_parser here.
        v_maj = 0;
        v_min = 9;
        u_end = line_end;
        return 1;
#else
        return -1;
#endif
    }

    int i = v_start + sizeof("HTTP/") -1;

    /* next should be 1 or more digits */
    if (!isdigit(buf[i])) {
        return -1;
    }
    int maj = 0;
    for (; i <= line_end && (isdigit(buf[i])) && maj < 65536; i++) {
        maj = maj * 10;
        maj = maj + (buf[i]) - '0';
    }
    // catch too-big values or missing remainders
    if (maj >= 65536 || i > line_end) {
        return -1;
    }
    v_maj = maj;

    /* next should be .; we -have- to have this as we have a whole line.. */
    if (buf[i] != '.') {
        return -1;
    }
    // catch missing minor part
    if (++i > line_end) {
        return -1;
    }

    /* next should be one or more digits */
    if (!isdigit(buf[i])) {
        return -1;
    }
    int min = 0;
    for (; i <= line_end && (isdigit(buf[i])) && min < 65536; i++) {
        min = min * 10;
        min = min + (buf[i]) - '0';
    }
    // catch too-big values or trailing garbage
    if (min >= 65536 || i < line_end) {
        return -1;
    }
    v_min = min;

    /*
     * Rightio - we have all the schtuff. Return true; we've got enough.
     */
    return 1;
}