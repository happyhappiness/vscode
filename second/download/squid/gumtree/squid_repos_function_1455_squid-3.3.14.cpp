bool
HttpRequestMethod::purgesOthers() const
{
    // TODO: optimize the lookup with a precomputed flags array

    switch (theMethod) {
        /* common sense suggests purging is not required? */
    case METHOD_GET:     // XXX: but we do purge HEAD on successful GET
    case METHOD_HEAD:
    case METHOD_NONE:
    case METHOD_CONNECT:
    case METHOD_TRACE:
    case METHOD_OPTIONS:
    case METHOD_PROPFIND:
    case METHOD_BPROPFIND:
    case METHOD_COPY:
    case METHOD_BCOPY:
    case METHOD_LOCK:
    case METHOD_UNLOCK:
    case METHOD_SEARCH:
        return false;

        /* purging mandated by RFC 2616 */
    case METHOD_POST:
    case METHOD_PUT:
    case METHOD_DELETE:
        return true;

        /* purging suggested by common sense */
    case METHOD_PURGE:
        return true;

        /*
         * RFC 2616 sayeth, in section 13.10, final paragraph:
         * A cache that passes through requests for methods it does not
         * understand SHOULD invalidate any entities referred to by the
         * Request-URI.
         */
    case METHOD_OTHER:
    default:
        return true;
    }

    return true; // not reached, but just in case
}