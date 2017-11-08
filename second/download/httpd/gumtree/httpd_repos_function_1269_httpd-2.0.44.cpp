static int proxy_fixup(request_rec *r)
{
    char *url, *p;
    int access_status;

    if (!r->proxyreq || strncmp(r->filename, "proxy:", 6) != 0)
        return DECLINED;

    /* XXX: Shouldn't we try this before we run the proxy_walk? */
    url = &r->filename[6];

    /* canonicalise each specific scheme */
    if ((access_status = proxy_run_canon_handler(r, url))) {
        return access_status;
    }

    p = strchr(url, ':');
    if (p == NULL || p == url)
        return HTTP_BAD_REQUEST;

    return OK;		/* otherwise; we've done the best we can */
}