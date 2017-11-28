libecap::Name
Adaptation::Ecap::FirstLineRep::protocol() const
{
    // TODO: optimize?
    switch (theMessage.protocol) {
    case PROTO_HTTP:
        return libecap::protocolHttp;
    case PROTO_HTTPS:
        return libecap::protocolHttps;
    case PROTO_FTP:
        return libecap::protocolFtp;
    case PROTO_GOPHER:
        return libecap::protocolGopher;
    case PROTO_WAIS:
        return libecap::protocolWais;
    case PROTO_WHOIS:
        return libecap::protocolWhois;
    case PROTO_URN:
        return libecap::protocolUrn;
    case PROTO_ICP:
        return protocolIcp;
#if USE_HTCP
    case PROTO_HTCP:
        return protocolHtcp;
#endif
    case PROTO_CACHEOBJ:
        return protocolCacheObj;
    case PROTO_INTERNAL:
        return protocolInternal;
    case PROTO_ICY:
        return Name();
    case PROTO_COAP:
    case PROTO_COAPS: // use 'unknown'/none until libecap supports coap:// and coaps://
    case PROTO_NONE:
        return Name();

    case PROTO_MAX:
        break; // should not happen
        // no default to catch PROTO_ additions
    }
    Must(false); // not reached
    return Name();
}