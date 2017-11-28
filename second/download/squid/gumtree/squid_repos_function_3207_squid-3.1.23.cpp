char *
urlMakeAbsolute(const HttpRequest * req, const char *relUrl)
{

    if (req->method.id() == METHOD_CONNECT) {
        return (NULL);
    }

    char *urlbuf = (char *)xmalloc(MAX_URL * sizeof(char));

    if (req->protocol == PROTO_URN) {
        snprintf(urlbuf, MAX_URL, "urn:" SQUIDSTRINGPH,
                 SQUIDSTRINGPRINT(req->urlpath));
        return (urlbuf);
    }

    size_t urllen;

    if (req->port != urlDefaultPort(req->protocol)) {
        urllen = snprintf(urlbuf, MAX_URL, "%s://%s%s%s:%d",
                          ProtocolStr[req->protocol],
                          req->login,
                          *req->login ? "@" : null_string,
                          req->GetHost(),
                          req->port
                         );
    } else {
        urllen = snprintf(urlbuf, MAX_URL, "%s://%s%s%s",
                          ProtocolStr[req->protocol],
                          req->login,
                          *req->login ? "@" : null_string,
                          req->GetHost()
                         );
    }

    if (relUrl[0] == '/') {
        strncpy(&urlbuf[urllen], relUrl, MAX_URL - urllen - 1);
    } else {
        const char *path = req->urlpath.termedBuf();
        const char *last_slash = strrchr(path, '/');

        if (last_slash == NULL) {
            urlbuf[urllen++] = '/';
            strncpy(&urlbuf[urllen], relUrl, MAX_URL - urllen - 1);
        } else {
            last_slash++;
            size_t pathlen = last_slash - path;
            if (pathlen > MAX_URL - urllen - 1) {
                pathlen = MAX_URL - urllen - 1;
            }
            strncpy(&urlbuf[urllen], path, pathlen);
            urllen += pathlen;
            if (urllen + 1 < MAX_URL) {
                strncpy(&urlbuf[urllen], relUrl, MAX_URL - urllen - 1);
            }
        }
    }

    return (urlbuf);
}