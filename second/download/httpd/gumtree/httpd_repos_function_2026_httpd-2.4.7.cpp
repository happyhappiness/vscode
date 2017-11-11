static int sc_for_req_header(const char *header_name)
{
    char header[16];
    apr_size_t len = strlen(header_name);
    const char *p = header_name;
    int i = 0;

    /* ACCEPT-LANGUAGE is the longest header
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
                    if (strcmp(p, "CHARSET") == 0)
                        return SC_ACCEPT_CHARSET;
                    else if (strcmp(p,  "ENCODING") == 0)
                        return SC_ACCEPT_ENCODING;
                    else if (strcmp(p, "LANGUAGE") == 0)
                        return SC_ACCEPT_LANGUAGE;
                    else
                        return UNKNOWN_METHOD;
                }
                else
                    return UNKNOWN_METHOD;
            }
            else if (strcmp(p, "UTHORIZATION") == 0)
                return SC_AUTHORIZATION;
            else
                return UNKNOWN_METHOD;
        break;
        case 'C':
            if(strcmp(p, "OOKIE2") == 0)
                return SC_COOKIE2;
            else if (strcmp(p, "OOKIE") == 0)
                return SC_COOKIE;
            else if(strcmp(p, "ONNECTION") == 0)
                return SC_CONNECTION;
            else if(strcmp(p, "ONTENT-TYPE") == 0)
                return SC_CONTENT_TYPE;
            else if(strcmp(p, "ONTENT-LENGTH") == 0)
                return SC_CONTENT_LENGTH;
            else
                return UNKNOWN_METHOD;
        break;
        case 'H':
            if(strcmp(p, "OST") == 0)
                return SC_HOST;
            else
                return UNKNOWN_METHOD;
        break;
        case 'P':
            if(strcmp(p, "RAGMA") == 0)
                return SC_PRAGMA;
            else
                return UNKNOWN_METHOD;
        break;
        case 'R':
            if(strcmp(p, "EFERER") == 0)
                return SC_REFERER;
            else
                return UNKNOWN_METHOD;
        break;
        case 'U':
            if(strcmp(p, "SER-AGENT") == 0)
                return SC_USER_AGENT;
            else
                return UNKNOWN_METHOD;
        break;
        default:
            return UNKNOWN_METHOD;
    }

    /* NOTREACHED */
}