void
HttpRequest::packFirstLineInto(Packable * p, bool full_uri) const
{
    const SBuf tmp(full_uri ? effectiveRequestUri() : url.path());

    // form HTTP request-line
    p->appendf(SQUIDSBUFPH " " SQUIDSBUFPH " HTTP/%d.%d\r\n",
               SQUIDSBUFPRINT(method.image()),
               SQUIDSBUFPRINT(tmp),
               http_ver.major, http_ver.minor);
}