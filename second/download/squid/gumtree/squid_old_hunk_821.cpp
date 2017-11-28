    Http::ProtocolVersion httpver(1,1);
    const char * url;
    if (_peer && !_peer->options.originserver)
        url = urlCanonical(request);
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
