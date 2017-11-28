AnyP::ProtocolType
urlParseProtocol(const char *b)
{
    // make e point to the ':' character
    const char *e = b + strcspn(b, ":");
    int len = e - b;

    /* test common stuff first */

    if (strncasecmp(b, "http", len) == 0)
        return AnyP::PROTO_HTTP;

    if (strncasecmp(b, "ftp", len) == 0)
        return AnyP::PROTO_FTP;

    if (strncasecmp(b, "https", len) == 0)
        return AnyP::PROTO_HTTPS;

    if (strncasecmp(b, "file", len) == 0)
        return AnyP::PROTO_FTP;

    if (strncasecmp(b, "coap", len) == 0)
        return AnyP::PROTO_COAP;

    if (strncasecmp(b, "coaps", len) == 0)
        return AnyP::PROTO_COAPS;

    if (strncasecmp(b, "gopher", len) == 0)
        return AnyP::PROTO_GOPHER;

    if (strncasecmp(b, "wais", len) == 0)
        return AnyP::PROTO_WAIS;

    if (strncasecmp(b, "cache_object", len) == 0)
        return AnyP::PROTO_CACHE_OBJECT;

    if (strncasecmp(b, "urn", len) == 0)
        return AnyP::PROTO_URN;

    if (strncasecmp(b, "whois", len) == 0)
        return AnyP::PROTO_WHOIS;

    if (len > 0)
        return AnyP::PROTO_UNKNOWN;

    return AnyP::PROTO_NONE;
}