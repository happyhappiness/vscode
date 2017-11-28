void
setLogUri(ClientHttpRequest * http, char const *uri, bool cleanUrl)
{
    safe_free(http->log_uri);

    if (!cleanUrl)
        // The uri is already clean just dump it.
        http->log_uri = xstrndup(uri, MAX_URL);
    else {
        int flags = 0;
        switch (Config.uri_whitespace) {
        case URI_WHITESPACE_ALLOW:
            flags |= RFC1738_ESCAPE_NOSPACE;

        case URI_WHITESPACE_ENCODE:
            flags |= RFC1738_ESCAPE_UNESCAPED;
            http->log_uri = xstrndup(rfc1738_do_escape(uri, flags), MAX_URL);
            break;

        case URI_WHITESPACE_CHOP: {
            flags |= RFC1738_ESCAPE_NOSPACE;
            flags |= RFC1738_ESCAPE_UNESCAPED;
            http->log_uri = xstrndup(rfc1738_do_escape(uri, flags), MAX_URL);
            int pos = strcspn(http->log_uri, w_space);
            http->log_uri[pos] = '\0';
        }
        break;

        case URI_WHITESPACE_DENY:
        case URI_WHITESPACE_STRIP:
        default: {
            const char *t;
            char *tmp_uri = static_cast<char*>(xmalloc(strlen(uri) + 1));
            char *q = tmp_uri;
            t = uri;
            while (*t) {
                if (!xisspace(*t))
                    *q++ = *t;
                t++;
            }
            *q = '\0';
            http->log_uri = xstrndup(rfc1738_escape_unescaped(tmp_uri), MAX_URL);
            xfree(tmp_uri);
        }
        break;
        }
    }
}