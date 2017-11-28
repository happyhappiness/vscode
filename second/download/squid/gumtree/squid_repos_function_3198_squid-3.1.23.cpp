protocol_t
urlParseProtocol(const char *b, const char *e)
{
    /*
     * if e is NULL, b must be NULL terminated and we
     * make e point to the first whitespace character
     * after b.
     */

    if (NULL == e)
        e = b + strcspn(b, ":");

    int len = e - b;

    /* test common stuff first */

    if (strncasecmp(b, "http", len) == 0)
        return PROTO_HTTP;

    if (strncasecmp(b, "ftp", len) == 0)
        return PROTO_FTP;

    if (strncasecmp(b, "https", len) == 0)
        return PROTO_HTTPS;

    if (strncasecmp(b, "file", len) == 0)
        return PROTO_FTP;

    if (strncasecmp(b, "coap", len) == 0)
        return PROTO_COAP;

    if (strncasecmp(b, "coaps", len) == 0)
        return PROTO_COAPS;

    if (strncasecmp(b, "gopher", len) == 0)
        return PROTO_GOPHER;

    if (strncasecmp(b, "wais", len) == 0)
        return PROTO_WAIS;

    if (strncasecmp(b, "cache_object", len) == 0)
        return PROTO_CACHEOBJ;

    if (strncasecmp(b, "urn", len) == 0)
        return PROTO_URN;

    if (strncasecmp(b, "whois", len) == 0)
        return PROTO_WHOIS;

    if (strncasecmp(b, "internal", len) == 0)
        return PROTO_INTERNAL;

    return PROTO_NONE;
}