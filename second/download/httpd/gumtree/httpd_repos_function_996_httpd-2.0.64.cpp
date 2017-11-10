static void reduce_uri(request_rec *r)
{
    char *cp;
    unsigned short port;
    char *portp;
    char *hostp;
    char *url;
    char c;
    char host[LONG_STRING_LEN];
    char buf[MAX_STRING_LEN];
    char *olduri;
    apr_size_t l;

    cp = (char *)ap_http_method(r);
    l  = strlen(cp);
    if (   strlen(r->filename) > l+3
        && strncasecmp(r->filename, cp, l) == 0
        && r->filename[l]   == ':'
        && r->filename[l+1] == '/'
        && r->filename[l+2] == '/'             ) {
        /* there was really a rewrite to a remote path */

        olduri = apr_pstrdup(r->pool, r->filename); /* save for logging */

        /* cut the hostname and port out of the URI */
        apr_cpystrn(buf, r->filename+(l+3), sizeof(buf));
        hostp = buf;
        for (cp = hostp; *cp != '\0' && *cp != '/' && *cp != ':'; cp++)
            ;
        if (*cp == ':') {
            /* set host */
            *cp++ = '\0';
            apr_cpystrn(host, hostp, sizeof(host));
            /* set port */
            portp = cp;
            for (; *cp != '\0' && *cp != '/'; cp++)
                ;
            c = *cp;
            *cp = '\0';
            port = atoi(portp);
            *cp = c;
            /* set remaining url */
            url = cp;
        }
        else if (*cp == '/') {
            /* set host */
            *cp = '\0';
            apr_cpystrn(host, hostp, sizeof(host));
            *cp = '/';
            /* set port */
            port = ap_default_port(r);
            /* set remaining url */
            url = cp;
        }
        else {
            /* set host */
            apr_cpystrn(host, hostp, sizeof(host));
            /* set port */
            port = ap_default_port(r);
            /* set remaining url */
            url = "/";
        }

        /* now check whether we could reduce it to a local path... */
        if (ap_matches_request_vhost(r, host, port)) {
            /* this is our host, so only the URL remains */
            r->filename = apr_pstrdup(r->pool, url);
            rewritelog(r, 3, "reduce %s -> %s", olduri, r->filename);
        }
    }
    return;
}