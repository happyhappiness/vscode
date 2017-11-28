
    debugs(4, 3, "errorConvert: %%" << token << " --> '" << p << "'" );

    if (do_quote)
        p = html_quote(p);

    return p;
}

HttpReply *
ErrorState::BuildHttpReply()
{
    HttpReply *rep = new HttpReply;
    const char *name = errorPageName(page_id);
    /* no LMT for error pages; error pages expire immediately */

    if (strchr(name, ':')) {
        /* Redirection */
        if (request->method != METHOD_GET && request->method != METHOD_HEAD && request->http_ver >= HttpVersion(1,1))
            rep->setHeaders(HTTP_TEMPORARY_REDIRECT, NULL, "text/html", 0, 0, -1);
        else
            rep->setHeaders(HTTP_MOVED_TEMPORARILY, NULL, "text/html", 0, 0, -1);

        if (request) {
            char *quoted_url = rfc1738_escape_part(urlCanonical(request));
            httpHeaderPutStrf(&rep->header, HDR_LOCATION, name, quoted_url);
        }

        httpHeaderPutStrf(&rep->header, HDR_X_SQUID_ERROR, "%d %s", httpStatus, "Access Denied");
    } else {
        MemBuf *content = BuildContent();
        rep->setHeaders(httpStatus, NULL, "text/html", content->contentSize(), 0, -1);
