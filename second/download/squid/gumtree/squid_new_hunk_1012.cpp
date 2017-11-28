        break;
        }
    }
}

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
