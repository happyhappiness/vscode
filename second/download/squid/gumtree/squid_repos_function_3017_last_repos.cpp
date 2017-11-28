static void
prepareAcceleratedURL(ConnStateData * conn, ClientHttpRequest *http, const Http1::RequestParserPointer &hp)
{
    int vhost = conn->port->vhost;
    int vport = conn->port->vport;
    static char ipbuf[MAX_IPSTRLEN];

    http->flags.accel = true;

    /* BUG: Squid cannot deal with '*' URLs (RFC2616 5.1.2) */

    static const SBuf cache_object("cache_object://");
    if (hp->requestUri().startsWith(cache_object))
        return; /* already in good shape */

    // XXX: re-use proper URL parser for this
    SBuf url = hp->requestUri(); // use full provided URI if we abort
    do { // use a loop so we can break out of it
        ::Parser::Tokenizer tok(url);
        if (tok.skip('/')) // origin-form URL already.
            break;

        if (conn->port->vhost)
            return; /* already in good shape */

        // skip the URI scheme
        static const CharacterSet uriScheme = CharacterSet("URI-scheme","+-.") + CharacterSet::ALPHA + CharacterSet::DIGIT;
        static const SBuf uriSchemeEnd("://");
        if (!tok.skipAll(uriScheme) || !tok.skip(uriSchemeEnd))
            break;

        // skip the authority segment
        // RFC 3986 complex nested ABNF for "authority" boils down to this:
        static const CharacterSet authority = CharacterSet("authority","-._~%:@[]!$&'()*+,;=") +
                                              CharacterSet::HEXDIG + CharacterSet::ALPHA + CharacterSet::DIGIT;
        if (!tok.skipAll(authority))
            break;

        static const SBuf slashUri("/");
        const SBuf t = tok.remaining();
        if (t.isEmpty())
            url = slashUri;
        else if (t[0]=='/') // looks like path
            url = t;
        else if (t[0]=='?' || t[0]=='#') { // looks like query or fragment. fix '/'
            url = slashUri;
            url.append(t);
        } // else do nothing. invalid path

    } while(false);

#if SHOULD_REJECT_UNKNOWN_URLS
    // reject URI which are not well-formed even after the processing above
    if (url.isEmpty() || url[0] != '/') {
        hp->parseStatusCode = Http::scBadRequest;
        return conn->abortRequestParsing("error:invalid-request");
    }
#endif

    if (vport < 0)
        vport = http->getConn()->clientConnection->local.port();

    const bool switchedToHttps = conn->switchedToHttps();
    const bool tryHostHeader = vhost || switchedToHttps;
    char *host = NULL;
    if (tryHostHeader && (host = hp->getHeaderField("Host"))) {
        debugs(33, 5, "ACCEL VHOST REWRITE: vhost=" << host << " + vport=" << vport);
        char thost[256];
        if (vport > 0) {
            thost[0] = '\0';
            char *t = NULL;
            if (host[strlen(host)] != ']' && (t = strrchr(host,':')) != NULL) {
                strncpy(thost, host, (t-host));
                snprintf(thost+(t-host), sizeof(thost)-(t-host), ":%d", vport);
                host = thost;
            } else if (!t) {
                snprintf(thost, sizeof(thost), "%s:%d",host, vport);
                host = thost;
            }
        } // else nothing to alter port-wise.
        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen + strlen(host);
        http->uri = (char *)xcalloc(url_sz, 1);
        const SBuf &scheme = AnyP::UriScheme(conn->transferProtocol.protocol).image();
        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s" SQUIDSBUFPH, SQUIDSBUFPRINT(scheme), host, SQUIDSBUFPRINT(url));
        debugs(33, 5, "ACCEL VHOST REWRITE: " << http->uri);
    } else if (conn->port->defaultsite /* && !vhost */) {
        debugs(33, 5, "ACCEL DEFAULTSITE REWRITE: defaultsite=" << conn->port->defaultsite << " + vport=" << vport);
        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen +
                           strlen(conn->port->defaultsite);
        http->uri = (char *)xcalloc(url_sz, 1);
        char vportStr[32];
        vportStr[0] = '\0';
        if (vport > 0) {
            snprintf(vportStr, sizeof(vportStr),":%d",vport);
        }
        const SBuf &scheme = AnyP::UriScheme(conn->transferProtocol.protocol).image();
        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s%s" SQUIDSBUFPH,
                 SQUIDSBUFPRINT(scheme), conn->port->defaultsite, vportStr, SQUIDSBUFPRINT(url));
        debugs(33, 5, "ACCEL DEFAULTSITE REWRITE: " << http->uri);
    } else if (vport > 0 /* && (!vhost || no Host:) */) {
        debugs(33, 5, "ACCEL VPORT REWRITE: *_port IP + vport=" << vport);
        /* Put the local socket IP address as the hostname, with whatever vport we found  */
        const int url_sz = hp->requestUri().length() + 32 + Config.appendDomainLen;
        http->uri = (char *)xcalloc(url_sz, 1);
        http->getConn()->clientConnection->local.toHostStr(ipbuf,MAX_IPSTRLEN);
        const SBuf &scheme = AnyP::UriScheme(conn->transferProtocol.protocol).image();
        snprintf(http->uri, url_sz, SQUIDSBUFPH "://%s:%d" SQUIDSBUFPH,
                 SQUIDSBUFPRINT(scheme), ipbuf, vport, SQUIDSBUFPRINT(url));
        debugs(33, 5, "ACCEL VPORT REWRITE: " << http->uri);
    }
}