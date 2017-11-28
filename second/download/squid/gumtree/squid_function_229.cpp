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
    /* append header terminator */
    mb->append(crlf, 2);
    return mb->size - offset;
}