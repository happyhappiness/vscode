static void
prepareTransparentURL(ConnStateData * conn, ClientHttpRequest *http, const Http1::RequestParserPointer &hp)
{
    // TODO Must() on URI !empty when the parser supports throw. For now avoid assert().
    if (!hp->requestUri().isEmpty() && hp->requestUri()[0] != '/')
        return; /* already in good shape */

    /* BUG: Squid cannot deal with '*' URLs (RFC2616 5.1.2) */

    if (const char *host = hp->getHeaderField("Host")) {
        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen +
                           strlen(host);
        http->uri = (char *)xcalloc(url_sz, 1);
        const SBuf &scheme = AnyP::UriScheme(conn->transferProtocol.protocol).image();
        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s" SQUIDSBUFPH,
                 SQUIDSBUFPRINT(scheme), host, SQUIDSBUFPRINT(hp->requestUri()));
        debugs(33, 5, "TRANSPARENT HOST REWRITE: " << http->uri);
    } else {
        /* Put the local socket IP address as the hostname.  */
        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen;
        http->uri = (char *)xcalloc(url_sz, 1);
        static char ipbuf[MAX_IPSTRLEN];
        http->getConn()->clientConnection->local.toHostStr(ipbuf,MAX_IPSTRLEN);
        const SBuf &scheme = AnyP::UriScheme(http->getConn()->transferProtocol.protocol).image();
        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s:%d" SQUIDSBUFPH,
                 SQUIDSBUFPRINT(scheme),
                 ipbuf, http->getConn()->clientConnection->local.port(), SQUIDSBUFPRINT(hp->requestUri()));
        debugs(33, 5, "TRANSPARENT REWRITE: " << http->uri);
    }
}