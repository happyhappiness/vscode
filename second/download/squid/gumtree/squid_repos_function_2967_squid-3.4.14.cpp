bool
HttpRequest::maybeCacheable()
{
    // Intercepted request with Host: header which cannot be trusted.
    // Because it failed verification, or someone bypassed the security tests
    // we cannot cache the reponse for sharing between clients.
    // TODO: update cache to store for particular clients only (going to same Host: and destination IP)
    if (!flags.hostVerified && (flags.intercepted || flags.interceptTproxy))
        return false;

    switch (protocol) {
    case AnyP::PROTO_HTTP:
    case AnyP::PROTO_HTTPS:
        if (!method.respMaybeCacheable())
            return false;

        // XXX: this would seem the correct place to detect request cache-controls
        //      no-store, private and related which block cacheability
        break;

    case AnyP::PROTO_GOPHER:
        if (!gopherCachable(this))
            return false;
        break;

    case AnyP::PROTO_CACHE_OBJECT:
        return false;

        //case AnyP::PROTO_FTP:
    default:
        break;
    }

    return true;
}