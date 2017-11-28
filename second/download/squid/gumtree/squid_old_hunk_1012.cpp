        break;
        }
    }
}

static void
prepareAcceleratedURL(ConnStateData * conn, ClientHttpRequest *http, char *url, const char *req_hdr)
{
    int vhost = conn->port->vhost;
    int vport = conn->port->vport;
    char *host;
    char ipbuf[MAX_IPSTRLEN];

    http->flags.accel = true;

    /* BUG: Squid cannot deal with '*' URLs (RFC2616 5.1.2) */

    if (strncasecmp(url, "cache_object://", 15) == 0)
        return; /* already in good shape */

    if (*url != '/') {
        if (conn->port->vhost)
            return; /* already in good shape */

        /* else we need to ignore the host name */
        url = strstr(url, "//");

#if SHOULD_REJECT_UNKNOWN_URLS

        if (!url) {
            hp->request_parse_status = Http::scBadRequest;
            return conn->abortRequestParsing("error:invalid-request");
        }
#endif

        if (url)
            url = strchr(url + 2, '/');

        if (!url)
            url = (char *) "/";
    }

    if (vport < 0)
        vport = http->getConn()->clientConnection->local.port();

    const bool switchedToHttps = conn->switchedToHttps();
    const bool tryHostHeader = vhost || switchedToHttps;
    if (tryHostHeader && (host = mime_get_header(req_hdr, "Host")) != NULL) {
        debugs(33, 5, "ACCEL VHOST REWRITE: vhost=" << host << " + vport=" << vport);
        char thost[256];
        if (vport > 0) {
            thost[0] = '\0';
            char *t = NULL;
            if (host[strlen(host)] != ']' && (t = strrchr(host,':')) != NULL) {
