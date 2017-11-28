void
clientReplyContext::purgeAllCached()
{
    // XXX: performance regression, c_str() reallocates
    SBuf url(http->request->effectiveRequestUri());
    purgeEntriesByUrl(http->request, url.c_str());
}