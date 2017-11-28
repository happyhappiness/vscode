bool
HttpRequestMethod::isCacheble() const
{
    // TODO: optimize the lookup with a precomputed flags array
    // XXX: the list seems wrong; e.g., Is METHOD_DELETE really cachable?
    // see also http.cc::httpCachable()

    if (theMethod == METHOD_CONNECT)
        return false;

    if (theMethod == METHOD_TRACE)
        return false;

    if (theMethod == METHOD_PUT)
        return false;

    if (theMethod == METHOD_POST)
        return false;

    if (theMethod == METHOD_OTHER)
        return false;

    return true;
}