
    debugs(4, 3, "errorConvert: %%" << token << " --> '" << p << "'" );

    if (do_quote)
        p = html_quote(p);

    if (building_deny_info_url && !no_urlescape)
        p = rfc1738_escape_part(p);

    return p;
}

void
ErrorState::DenyInfoLocation(const char *name, HttpRequest *aRequest, MemBuf &result)
{
    char const *m = name;
    char const *p = m;
    char const *t;

    if (m[0] == '3')
        m += 4; // skip "3xx:"

    while ((p = strchr(m, '%'))) {
        result.append(m, p - m);       /* copy */
        t = Convert(*++p, true, true);       /* convert */
        result.Printf("%s", t);        /* copy */
        m = p + 1;                     /* advance */
    }

    if (*m)
        result.Printf("%s", m);        /* copy tail */

    assert((size_t)result.contentSize() == strlen(result.content()));
}

HttpReply *
ErrorState::BuildHttpReply()
{
    HttpReply *rep = new HttpReply;
    const char *name = errorPageName(page_id);
    /* no LMT for error pages; error pages expire immediately */

    if (name[0] == '3' || (name[0] != '2' && name[0] != '4' && name[0] != '5' && strchr(name, ':'))) {
        /* Redirection */
        http_status status = HTTP_MOVED_TEMPORARILY;
        // Use configured 3xx reply status if set.
        if (name[0] == '3')
            status = httpStatus;
        else {
            // Use 307 for HTTP/1.1 non-GET/HEAD requests.
            if (request->method != METHOD_GET && request->method != METHOD_HEAD && request->http_ver >= HttpVersion(1,1))
                status = HTTP_TEMPORARY_REDIRECT;
        }

        rep->setHeaders(status, NULL, "text/html", 0, 0, -1);

        if (request) {
            MemBuf redirect_location;
            redirect_location.init();
            DenyInfoLocation(name, request, redirect_location);
            httpHeaderPutStrf(&rep->header, HDR_LOCATION, "%s", redirect_location.content() );
        }

        httpHeaderPutStrf(&rep->header, HDR_X_SQUID_ERROR, "%d %s", httpStatus, "Access Denied");
    } else {
        MemBuf *content = BuildContent();
        rep->setHeaders(httpStatus, NULL, "text/html", content->contentSize(), 0, -1);
