static int sc_for_req_header(const char *header_name)
{
    char header[16];
    apr_size_t len = strlen(header_name);
    const char *p = header_name;
    int i = 0;

    /* ACCEPT-LANGUAGE is the longest headeer
     * that is of interest.
     */
    if (len < 4 || len > 15)
        return UNKNOWN_METHOD;

    while (*p)
        header[i++] = apr_toupper(*p++);
    header[i] = '\0';
    p = &header[1];

    switch (header[0]) {
        case 'A':
            if (memcmp(p, "CCEPT", 5) == 0) {
                if (!header[6])
                    return SC_ACCEPT;
                else if (header[6] == '-') {
                    p += 6;
                    if (memcmp(p, "CHARSET", 7) == 0)
                        return SC_ACCEPT_CHARSET;
                    else if (memcmp(p,  "ENCODING", 8) == 0)
                        return SC_ACCEPT_ENCODING;
                    else if (memcmp(p, "LANGUAGE", 8) == 0)
                        return SC_ACCEPT_LANGUAGE;
                    else
                        return UNKNOWN_METHOD;
                }
                else
                    return UNKNOWN_METHOD;
            }
            else if (memcmp(p, "UTHORIZATION", 12) == 0)
                return SC_AUTHORIZATION;
            else
                return UNKNOWN_METHOD;
        break;
        case 'C':
            if (memcmp(p, "OOKIE", 5) == 0)
                return SC_COOKIE;
            else if(memcmp(p, "ONNECTION", 9) == 0)
                return SC_CONNECTION;
            else if(memcmp(p, "ONTENT-TYPE", 11) == 0)
                return SC_CONTENT_TYPE;
            else if(memcmp(p, "ONTENT-LENGTH", 13) == 0)
                return SC_CONTENT_LENGTH;
            else if(memcmp(p, "OOKIE2", 6) == 0)
                return SC_COOKIE2;
            else
                return UNKNOWN_METHOD;
        break;
        case 'H':
            if(memcmp(p, "OST", 3) == 0)
                return SC_HOST;
            else
                return UNKNOWN_METHOD;
        break;
        case 'P':
            if(memcmp(p, "RAGMA", 5) == 0)
                return SC_PRAGMA;
            else
                return UNKNOWN_METHOD;
        break;
        case 'R':
            if(memcmp(p, "EFERER", 6) == 0)
                return SC_REFERER;
            else
                return UNKNOWN_METHOD;
        break;
        case 'U':
            if(memcmp(p, "SER-AGENT", 9) == 0)
                return SC_USER_AGENT;
            else
                return UNKNOWN_METHOD;
        break;
        default:
            return UNKNOWN_METHOD;
    }

    /* NOTREACHED */
}