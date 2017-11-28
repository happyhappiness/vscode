int
urlDefaultPort(AnyP::ProtocolType p)
{
    switch (p) {

    case AnyP::PROTO_HTTP:
        return 80;

    case AnyP::PROTO_HTTPS:
        return 443;

    case AnyP::PROTO_FTP:
        return 21;

    case AnyP::PROTO_COAP:
    case AnyP::PROTO_COAPS:
        // coaps:// default is TBA as of draft-ietf-core-coap-08.
        // Assuming IANA policy of allocating same port for base and TLS protocol versions will occur.
        return 5683;

    case AnyP::PROTO_GOPHER:
        return 70;

    case AnyP::PROTO_WAIS:
        return 210;

    case AnyP::PROTO_CACHE_OBJECT:

    case AnyP::PROTO_INTERNAL:
        return CACHE_HTTP_PORT;

    case AnyP::PROTO_WHOIS:
        return 43;

    default:
        return 0;
    }
}