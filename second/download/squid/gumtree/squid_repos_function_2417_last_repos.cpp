bool
HttpRequest::maybeCacheable()
{
    // Intercepted request with Host: header which cannot be trusted.
    // Because it failed verification, or someone bypassed the security tests
    // we cannot cache the reponse for sharing between clients.
    // TODO: update cache to store for particular clients only (going to same Host: and destination IP)
    if (!flags.hostVerified && (flags.intercepted || flags.interceptTproxy))
        return false;

    switch (url.getScheme()) {
    case AnyP::PROTO_HTTP:
    case AnyP::PROTO_HTTPS:
        if (!method.respMaybeCacheable())
            return false;

        // RFC 7234 section 5.2.1.5:
        // "cache MUST NOT store any part of either this request or any response to it"
        //
        // NP: refresh_pattern ignore-no-store only applies to response messages
        //     this test is handling request message CC header.
        if (!flags.ignoreCc && cache_control && cache_control->hasNoStore())
            return false;
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