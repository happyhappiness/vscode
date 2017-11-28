bool
Downloader::buildRequest()
{
    const HttpRequestMethod method = Http::METHOD_GET;

    char *uri = xstrdup(url_.c_str());
    const MasterXaction::Pointer mx = new MasterXaction(initiator_);
    HttpRequest *const request = HttpRequest::FromUrl(uri, mx, method);
    if (!request) {
        debugs(33, 5, "Invalid URI: " << url_);
        xfree(uri);
        return false; //earlyError(...)
    }
    request->http_ver = Http::ProtocolVersion();
    request->header.putStr(Http::HdrType::HOST, request->url.host());
    request->header.putTime(Http::HdrType::DATE, squid_curtime);
    request->client_addr.setNoAddr();
#if FOLLOW_X_FORWARDED_FOR
    request->indirect_client_addr.setNoAddr();
#endif /* FOLLOW_X_FORWARDED_FOR */
    request->my_addr.setNoAddr();   /* undefined for internal requests */
    request->my_addr.port(0);
    request->downloader = this;

    debugs(11, 2, "HTTP Client Downloader " << this << "/" << id);
    debugs(11, 2, "HTTP Client REQUEST:\n---------\n" <<
           request->method << " " << url_ << " " << request->http_ver << "\n" <<
           "\n----------");

    ClientHttpRequest *const http = new ClientHttpRequest(nullptr);
    http->request = request;
    HTTPMSGLOCK(http->request);
    http->req_sz = 0;
    http->uri = uri;
    setLogUri (http, urlCanonicalClean(request));

    context_ = new DownloaderContext(this, http);
    StoreIOBuffer tempBuffer;
    tempBuffer.data = context_->requestBuffer;
    tempBuffer.length = HTTP_REQBUF_SZ;

    ClientStreamData newServer = new clientReplyContext(http);
    ClientStreamData newClient = context_.getRaw();
    clientStreamInit(&http->client_stream, clientGetMoreData, clientReplyDetach,
                     clientReplyStatus, newServer, downloaderRecipient,
                     downloaderDetach, newClient, tempBuffer);

    // Build a ClientRequestContext to start doCallouts
    http->calloutContext = new ClientRequestContext(http);
    http->doCallouts();
    return true;
}