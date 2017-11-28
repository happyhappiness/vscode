void
ServerStateData::maybePurgeOthers()
{
    // only some HTTP methods should purge matching cache entries
    if (!request->method.purgesOthers())
        return;

    // and probably only if the response was successful
    if (theFinalReply->sline.status >= 400)
        return;

    // XXX: should we use originalRequest() here?
    const char *reqUrl = urlCanonical(request);
    debugs(88, 5, "maybe purging due to " << RequestMethodStr(request->method) << ' ' << reqUrl);
    purgeEntriesByUrl(request, reqUrl);
    purgeEntriesByHeader(request, reqUrl, theFinalReply, HDR_LOCATION);
    purgeEntriesByHeader(request, reqUrl, theFinalReply, HDR_CONTENT_LOCATION);
}