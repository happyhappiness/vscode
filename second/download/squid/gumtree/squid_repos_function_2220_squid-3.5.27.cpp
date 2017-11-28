mb_size_t
HttpStateData::buildRequestPrefix(MemBuf * mb)
{
    const int offset = mb->size;
    /* Uses a local httpver variable to print the HTTP/1.1 label
     * since the HttpRequest may have an older version label.
     * XXX: This could create protocol bugs as the headers sent and
     * flow control should all be based on the HttpRequest version
     * not the one we are sending. Needs checking.
     */
    Http::ProtocolVersion httpver(1,1);
    const char * url;
    if (_peer && !_peer->options.originserver)
        url = urlCanonical(request);
    else
        url = request->urlpath.termedBuf();
    mb->Printf(SQUIDSBUFPH " %s %s/%d.%d\r\n",
               SQUIDSBUFPRINT(request->method.image()),
               url && *url ? url : "/",
               AnyP::ProtocolType_str[httpver.protocol],
               httpver.major,httpver.minor);
    /* build and pack headers */
    {
        HttpHeader hdr(hoRequest);
        Packer p;
        httpBuildRequestHeader(request, entry, fwd->al, &hdr, flags);

        if (request->flags.pinned && request->flags.connectionAuth)
            request->flags.authSent = true;
        else if (hdr.has(HDR_AUTHORIZATION))
            request->flags.authSent = true;

        packerToMemInit(&p, mb);
        hdr.packInto(&p);
        hdr.clean();
        packerClean(&p);
    }
    /* append header terminator */
    mb->append(crlf, 2);
    return mb->size - offset;
}