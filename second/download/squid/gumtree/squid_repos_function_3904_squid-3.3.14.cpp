libecap::Name
Adaptation::Ecap::FirstLineRep::protocol() const
{
    // TODO: optimize?
    switch (theMessage.protocol) {
    case AnyP::PROTO_HTTP:
        return libecap::protocolHttp;
    case AnyP::PROTO_HTTPS:
        return libecap::protocolHttps;
    case AnyP::PROTO_FTP:
        return libecap::protocolFtp;
    case AnyP::PROTO_GOPHER:
        return libecap::protocolGopher;
    case AnyP::PROTO_WAIS:
        return libecap::protocolWais;
    case AnyP::PROTO_WHOIS:
        return libecap::protocolWhois;
    case AnyP::PROTO_URN:
        return libecap::protocolUrn;
    case AnyP::PROTO_ICP:
        return protocolIcp;
#if USE_HTCP
    case AnyP::PROTO_HTCP:
        return protocolHtcp;
#endif
    case AnyP::PROTO_CACHE_OBJECT:
        return protocolCacheObj;
    case AnyP::PROTO_INTERNAL:
        return protocolInternal;
    case AnyP::PROTO_ICY:
        return protocolIcy;
    case AnyP::PROTO_COAP:
    case AnyP::PROTO_COAPS: // use 'unknown' until libecap supports coap:// and coaps://
    case AnyP::PROTO_UNKNOWN:
        return protocolUnknown; // until we remember the protocol image
    case AnyP::PROTO_NONE:
        return Name();

    case AnyP::PROTO_MAX:
        break; // should not happen
        // no default to catch AnyP::PROTO_ additions
    }
    Must(false); // not reached
    return Name();
}