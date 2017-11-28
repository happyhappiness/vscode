bool
Downloader::buildRequest()
{
    const HttpRequestMethod method = Http::METHOD_GET;

    char *uri = xstrdup(url_.c_str());
    HttpRequest *const request = HttpRequest::CreateFromUrl(uri, method);
    if (!request) {
        debugs(33, 5, "Invalid URI: " << url_);
        xfree(uri);
        return false; //earlyError(...)
    }
    request->http_ver = Http::ProtocolVersion();
    request->header.putStr(Http::HdrType::HOST, request->url.host());
    request->header.putTime(Http::HdrType::DATE, squid_curtime);
    request->flags.internalClient = true;
    request->client_addr.setNoAddr();
#if FOLLOW_X_FORWARDED_FOR
    request->indirect_client_addr.setNoAddr();
#endif /* FOLLOW_X_FORWARDED_FOR */
    request->my_addr.setNoAddr();   /* undefined for internal requests */
    request->my_addr.port(0);
