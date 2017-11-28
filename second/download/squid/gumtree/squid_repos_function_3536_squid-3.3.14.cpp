static void
prepareTransparentURL(ConnStateData * conn, ClientHttpRequest *http, char *url, const char *req_hdr)
{
    char *host;
    char ipbuf[MAX_IPSTRLEN];

    if (*url != '/')
        return; /* already in good shape */

    /* BUG: Squid cannot deal with '*' URLs (RFC2616 5.1.2) */

    if ((host = mime_get_header(req_hdr, "Host")) != NULL) {
        int url_sz = strlen(url) + 32 + Config.appendDomainLen +
                     strlen(host);
        http->uri = (char *)xcalloc(url_sz, 1);
        snprintf(http->uri, url_sz, "%s://%s%s", conn->port->protocol, host, url);
        debugs(33, 5, "TRANSPARENT HOST REWRITE: '" << http->uri <<"'");
    } else {
        /* Put the local socket IP address as the hostname.  */
        int url_sz = strlen(url) + 32 + Config.appendDomainLen;
        http->uri = (char *)xcalloc(url_sz, 1);
        http->getConn()->clientConnection->local.ToHostname(ipbuf,MAX_IPSTRLEN);
        snprintf(http->uri, url_sz, "%s://%s:%d%s",
                 http->getConn()->port->protocol,
                 ipbuf, http->getConn()->clientConnection->local.GetPort(), url);
        debugs(33, 5, "TRANSPARENT REWRITE: '" << http->uri << "'");
    }
}