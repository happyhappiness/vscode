     *    - reply will be cachable
     * (If the reply will be uncachable we have to throw it away after
     *  serving this request, so it is better to forward ranges to
     *  the server and fetch only the requested content)
     */

    int64_t roffLimit = request->getRangeOffsetLimit();

    if (NULL == request->range || !request->flags.cachable
            || request->range->offsetLimitExceeded(roffLimit) || request->flags.connection_auth)
        result = false;

    debugs(11, 8, "decideIfWeDoRanges: range specs: " <<
           request->range << ", cachable: " <<
           request->flags.cachable << "; we_do_ranges: " << result);

    return result;
}

/* build request prefix and append it to a given MemBuf;
 * return the length of the prefix */
mb_size_t
HttpStateData::buildRequestPrefix(MemBuf * mb)
{
    const int offset = mb->size;
    HttpVersion httpver(1,1);
    const char * url;
    if (_peer && !_peer->options.originserver)
        url = entry->url();
    else
        url = request->urlpath.termedBuf();
    mb->Printf("%s %s %s/%d.%d\r\n",
               RequestMethodStr(request->method),
               url && *url ? url : "/",
               AnyP::ProtocolType_str[httpver.protocol],
               httpver.major,httpver.minor);
    /* build and pack headers */
    {
        HttpHeader hdr(hoRequest);
        Packer p;
        httpBuildRequestHeader(request, entry, fwd->al, &hdr, flags);

        if (request->flags.pinned && request->flags.connection_auth)
            request->flags.auth_sent = 1;
        else if (hdr.has(HDR_AUTHORIZATION))
            request->flags.auth_sent = 1;

        packerToMemInit(&p, mb);
        hdr.packInto(&p);
        hdr.clean();
        packerClean(&p);
    }
