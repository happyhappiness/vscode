bool
HttpRequestMethod::purgesOthers() const
{
    if (shouldInvalidate())
        return true;

    switch (theMethod) {
    /* common sense suggests purging is not required? */
    case Http::METHOD_GET:     // XXX: but we do purge HEAD on successful GET
    case Http::METHOD_HEAD:
    case Http::METHOD_NONE:
    case Http::METHOD_CONNECT:
    case Http::METHOD_TRACE:
    case Http::METHOD_OPTIONS:
    case Http::METHOD_PROPFIND:
    case Http::METHOD_COPY:
    case Http::METHOD_LOCK:
    case Http::METHOD_UNLOCK:
    case Http::METHOD_SEARCH:
        return false;

    default:
        return true;
    }
}