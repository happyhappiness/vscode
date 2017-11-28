HttpRequest *
urlParse(const HttpRequestMethod& method, char *url, HttpRequest *request)
{
    LOCAL_ARRAY(char, proto, MAX_URL);
    LOCAL_ARRAY(char, login, MAX_URL);
    LOCAL_ARRAY(char, host, MAX_URL);
    LOCAL_ARRAY(char, urlpath, MAX_URL);
    char *t = NULL;
    char *q = NULL;
    int port;
    AnyP::ProtocolType protocol = AnyP::PROTO_NONE;
    int l;
    int i;
    const char *src;
    char *dst;
    proto[0] = host[0] = urlpath[0] = login[0] = '\0';

    if ((l = strlen(url)) + Config.appendDomainLen > (MAX_URL - 1)) {
        /* terminate so it doesn't overflow other buffers */
        *(url + (MAX_URL >> 1)) = '\0';
        debugs(23, DBG_IMPORTANT, "urlParse: URL too large (" << l << " bytes)");
        return NULL;
    }
    if (method == Http::METHOD_CONNECT) {
        port = CONNECT_PORT;

        if (sscanf(url, "[%[^]]]:%d", host, &port) < 1)
            if (sscanf(url, "%[^:]:%d", host, &port) < 1)
                return NULL;

    } else if ((method == Http::METHOD_OPTIONS || method == Http::METHOD_TRACE) &&
               strcmp(url, "*") == 0) {
        protocol = AnyP::PROTO_HTTP;
        port = urlDefaultPort(protocol);
        return urlParseFinish(method, protocol, url, host, login, port, request);
    } else if (!strncmp(url, "urn:", 4)) {
        return urnParse(method, url, request);
    } else {
        /* Parse the URL: */
        src = url;
        i = 0;
        /* Find first : - everything before is protocol */
        for (i = 0, dst = proto; i < l && *src != ':'; ++i, ++src, ++dst) {
            *dst = *src;
        }
        if (i >= l)
            return NULL;
        *dst = '\0';

        /* Then its :// */
        if ((i+3) > l || *src != ':' || *(src + 1) != '/' || *(src + 2) != '/')
            return NULL;
        i += 3;
        src += 3;

        /* Then everything until first /; thats host (and port; which we'll look for here later) */
        // bug 1881: If we don't get a "/" then we imply it was there
        // bug 3074: We could just be given a "?" or "#". These also imply "/"
        // bug 3233: whitespace is also a hostname delimiter.
        for (dst = host; i < l && *src != '/' && *src != '?' && *src != '#' && *src != '\0' && !xisspace(*src); ++i, ++src, ++dst) {
            *dst = *src;
        }

        /*
         * We can't check for "i >= l" here because we could be at the end of the line
         * and have a perfectly valid URL w/ no trailing '/'. In this case we assume we've
         * been -given- a valid URL and the path is just '/'.
         */
        if (i > l)
            return NULL;
        *dst = '\0';

        // bug 3074: received 'path' starting with '?', '#', or '\0' implies '/'
        if (*src == '?' || *src == '#' || *src == '\0') {
            urlpath[0] = '/';
            dst = &urlpath[1];
        } else {
            dst = urlpath;
        }
        /* Then everything from / (inclusive) until \r\n or \0 - thats urlpath */
        for (; i < l && *src != '\r' && *src != '\n' && *src != '\0'; ++i, ++src, ++dst) {
            *dst = *src;
        }

        /* We -could- be at the end of the buffer here */
        if (i > l)
            return NULL;
        /* If the URL path is empty we set it to be "/" */
        if (dst == urlpath) {
            *dst = '/';
            ++dst;
        }
        *dst = '\0';

        protocol = urlParseProtocol(proto);
        port = urlDefaultPort(protocol);

        /* Is there any login information? (we should eventually parse it above) */
        t = strrchr(host, '@');
        if (t != NULL) {
            strncpy((char *) login, (char *) host, sizeof(login)-1);
            login[sizeof(login)-1] = '\0';
            t = strrchr(login, '@');
            *t = 0;
            strncpy((char *) host, t + 1, sizeof(host)-1);
            host[sizeof(host)-1] = '\0';
        }

        /* Is there any host information? (we should eventually parse it above) */
        if (*host == '[') {
            /* strip any IPA brackets. valid under IPv6. */
            dst = host;
            /* only for IPv6 sadly, pre-IPv6/URL code can't handle the clean result properly anyway. */
            src = host;
            ++src;
            l = strlen(host);
            i = 1;
            for (; i < l && *src != ']' && *src != '\0'; ++i, ++src, ++dst) {
                *dst = *src;
            }

            /* we moved in-place, so truncate the actual hostname found */
            *dst = '\0';
            ++dst;

            /* skip ahead to either start of port, or original EOS */
            while (*dst != '\0' && *dst != ':')
                ++dst;
            t = dst;
        } else {
            t = strrchr(host, ':');

            if (t != strchr(host,':') ) {
                /* RFC 2732 states IPv6 "SHOULD" be bracketed. allowing for times when its not. */
                /* RFC 3986 'update' simply modifies this to an "is" with no emphasis at all! */
                /* therefore we MUST accept the case where they are not bracketed at all. */
                t = NULL;
            }
        }

        // Bug 3183 sanity check: If scheme is present, host must be too.
        if (protocol != AnyP::PROTO_NONE && host[0] == '\0') {
            debugs(23, DBG_IMPORTANT, "SECURITY ALERT: Missing hostname in URL '" << url << "'. see access.log for details.");
            return NULL;
        }

        if (t && *t == ':') {
            *t = '\0';
            ++t;
            port = atoi(t);
        }
    }

    for (t = host; *t; ++t)
        *t = xtolower(*t);

    if (stringHasWhitespace(host)) {
        if (URI_WHITESPACE_STRIP == Config.uri_whitespace) {
            t = q = host;
            while (*t) {
                if (!xisspace(*t)) {
                    *q = *t;
                    ++q;
                }
                ++t;
            }
            *q = '\0';
        }
    }

    debugs(23, 3, "urlParse: Split URL '" << url << "' into proto='" << proto << "', host='" << host << "', port='" << port << "', path='" << urlpath << "'");

    if (Config.onoff.check_hostnames && strspn(host, Config.onoff.allow_underscore ? valid_hostname_chars_u : valid_hostname_chars) != strlen(host)) {
        debugs(23, DBG_IMPORTANT, "urlParse: Illegal character in hostname '" << host << "'");
        return NULL;
    }

    /* For IPV6 addresses also check for a colon */
    if (Config.appendDomain && !strchr(host, '.') && !strchr(host, ':'))
        strncat(host, Config.appendDomain, SQUIDHOSTNAMELEN - strlen(host) - 1);

    /* remove trailing dots from hostnames */
    while ((l = strlen(host)) > 0 && host[--l] == '.')
        host[l] = '\0';

    /* reject duplicate or leading dots */
    if (strstr(host, "..") || *host == '.') {
        debugs(23, DBG_IMPORTANT, "urlParse: Illegal hostname '" << host << "'");
        return NULL;
    }

    if (port < 1 || port > 65535) {
        debugs(23, 3, "urlParse: Invalid port '" << port << "'");
        return NULL;
    }

#if HARDCODE_DENY_PORTS
    /* These ports are filtered in the default squid.conf, but
     * maybe someone wants them hardcoded... */
    if (port == 7 || port == 9 || port == 19) {
        debugs(23, DBG_CRITICAL, "urlParse: Deny access to port " << port);
        return NULL;
    }
#endif

    if (stringHasWhitespace(urlpath)) {
        debugs(23, 2, "urlParse: URI has whitespace: {" << url << "}");

        switch (Config.uri_whitespace) {

        case URI_WHITESPACE_DENY:
            return NULL;

        case URI_WHITESPACE_ALLOW:
            break;

        case URI_WHITESPACE_ENCODE:
            t = rfc1738_escape_unescaped(urlpath);
            xstrncpy(urlpath, t, MAX_URL);
            break;

        case URI_WHITESPACE_CHOP:
            *(urlpath + strcspn(urlpath, w_space)) = '\0';
            break;

        case URI_WHITESPACE_STRIP:
        default:
            t = q = urlpath;
            while (*t) {
                if (!xisspace(*t)) {
                    *q = *t;
                    ++q;
                }
                ++t;
            }
            *q = '\0';
        }
    }

    return urlParseFinish(method, protocol, urlpath, host, login, port, request);
}