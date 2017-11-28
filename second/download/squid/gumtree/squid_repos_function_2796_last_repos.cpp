char *
urlMakeAbsolute(const HttpRequest * req, const char *relUrl)
{

    if (req->method.id() == Http::METHOD_CONNECT) {
        return (NULL);
    }

    char *urlbuf = (char *)xmalloc(MAX_URL * sizeof(char));

    if (req->url.getScheme() == AnyP::PROTO_URN) {
        // XXX: this is what the original code did, but it seems to break the
        // intended behaviour of this function. It returns the stored URN path,
        // not converting the given one into a URN...
        snprintf(urlbuf, MAX_URL, SQUIDSBUFPH, SQUIDSBUFPRINT(req->url.absolute()));
        return (urlbuf);
    }

    SBuf authorityForm = req->url.authority(); // host[:port]
    const SBuf &scheme = req->url.getScheme().image();
    size_t urllen = snprintf(urlbuf, MAX_URL, SQUIDSBUFPH "://" SQUIDSBUFPH "%s" SQUIDSBUFPH,
                             SQUIDSBUFPRINT(scheme),
                             SQUIDSBUFPRINT(req->url.userInfo()),
                             !req->url.userInfo().isEmpty() ? "@" : "",
                             SQUIDSBUFPRINT(authorityForm));

    // if the first char is '/' assume its a relative path
    // XXX: this breaks on scheme-relative URLs,
    // but we should not see those outside ESI, and rarely there.
    // XXX: also breaks on any URL containing a '/' in the query-string portion
    if (relUrl[0] == '/') {
        xstrncpy(&urlbuf[urllen], relUrl, MAX_URL - urllen - 1);
    } else {
        SBuf path = req->url.path();
        SBuf::size_type lastSlashPos = path.rfind('/');

        if (lastSlashPos == SBuf::npos) {
            // replace the whole path with the given bit(s)
            urlbuf[urllen] = '/';
            ++urllen;
            xstrncpy(&urlbuf[urllen], relUrl, MAX_URL - urllen - 1);
        } else {
            // replace only the last (file?) segment with the given bit(s)
            ++lastSlashPos;
            if (lastSlashPos > MAX_URL - urllen - 1) {
                // XXX: crops bits in the middle of the combined URL.
                lastSlashPos = MAX_URL - urllen - 1;
            }
            SBufToCstring(&urlbuf[urllen], path.substr(0,lastSlashPos));
            urllen += lastSlashPos;
            if (urllen + 1 < MAX_URL) {
                xstrncpy(&urlbuf[urllen], relUrl, MAX_URL - urllen - 1);
            }
        }
    }

    return (urlbuf);
}