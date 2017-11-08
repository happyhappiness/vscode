static void reduce_uri(request_rec *r)
{
    char *cp;
    apr_size_t l;

    cp = (char *)ap_http_scheme(r);
    l  = strlen(cp);
    if (   strlen(r->filename) > l+3
        && strncasecmp(r->filename, cp, l) == 0
        && r->filename[l]   == ':'
        && r->filename[l+1] == '/'
        && r->filename[l+2] == '/' ) {

        unsigned short port;
        char *portp, *host, *url, *scratch;

        scratch = apr_pstrdup(r->pool, r->filename); /* our scratchpad */

        /* cut the hostname and port out of the URI */
        cp = host = scratch + l + 3;    /* 3 == strlen("://") */
        while (*cp && *cp != '/' && *cp != ':') {
            ++cp;
        }

        if (*cp == ':') {      /* additional port given */
            *cp++ = '\0';
            portp = cp;
            while (*cp && *cp != '/') {
                ++cp;
            }
            *cp = '\0';

            port = atoi(portp);
            url = r->filename + (cp - scratch);
            if (!*url) {
                url = "/";
            }
        }
        else if (*cp == '/') { /* default port */
            *cp = '\0';

            port = ap_default_port(r);
            url = r->filename + (cp - scratch);
        }
        else {
            port = ap_default_port(r);
            url = "/";
        }

        /* now check whether we could reduce it to a local path... */
        if (ap_matches_request_vhost(r, host, port)) {
            rewritelog((r, 3, NULL, "reduce %s -> %s", r->filename, url));
            r->filename = apr_pstrdup(r->pool, url);
        }
    }

    return;
}