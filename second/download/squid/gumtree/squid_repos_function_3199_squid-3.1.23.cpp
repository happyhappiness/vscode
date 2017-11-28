int
urlDefaultPort(protocol_t p)
{
    switch (p) {

    case PROTO_HTTP:
        return 80;

    case PROTO_HTTPS:
        return 443;

    case PROTO_FTP:
        return 21;

    case PROTO_COAP:
    case PROTO_COAPS:
        // coaps:// default is TBA as of draft-ietf-core-coap-08.
        // Assuming IANA policy of allocating same port for base and TLS protocol versions will occur.
        return 5683;

    case PROTO_GOPHER:
        return 70;

    case PROTO_WAIS:
        return 210;

    case PROTO_CACHEOBJ:

    case PROTO_INTERNAL:
        return CACHE_HTTP_PORT;

    case PROTO_WHOIS:
        return 43;

    default:
        return 0;
    }
}