void
clientReplyContext::purgeAllCached()
{
    const char *url = urlCanonical(http->request);
    purgeEntriesByUrl(http->request, url);
}