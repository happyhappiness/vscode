static int proxy_handler(request_rec *r)
{
    char *url, *scheme, *p;
    const char *p2;
    void *sconf = r->server->module_config;
    proxy_server_conf *conf = (proxy_server_conf *)
        ap_get_module_config(sconf, &proxy_module);
    apr_array_header_t *proxies = conf->proxies;
    struct proxy_remote *ents = (struct proxy_remote *) proxies->elts;
    int i, rc, access_status;
    int direct_connect = 0;
    const char *str;
    long maxfwd;

    /* is this for us? */
    if (!r->proxyreq || strncmp(r->filename, "proxy:", 6) != 0)
        return DECLINED;

    /* handle max-forwards / OPTIONS / TRACE */
    if ((str = apr_table_get(r->headers_in, "Max-Forwards"))) {
        maxfwd = strtol(str, NULL, 10);
        if (maxfwd < 1) {
            switch (r->method_number) {
            case M_TRACE: {
                int access_status;
                r->proxyreq = PROXYREQ_NONE;
                if ((access_status = ap_send_http_trace(r)))
                    ap_die(access_status, r);
                else
                    ap_finalize_request_protocol(r);
                return OK;
            }
            case M_OPTIONS: {
                int access_status;
                r->proxyreq = PROXYREQ_NONE;
                if ((access_status = ap_send_http_options(r)))
                    ap_die(access_status, r);
                else
                    ap_finalize_request_protocol(r);
                return OK;
            }
            default: {
                return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                                     "Max-Forwards has reached zero - proxy loop?");
            }
            }
        }
        maxfwd = (maxfwd > 0) ? maxfwd - 1 : 0;
    }
    else {
        /* set configured max-forwards */
        maxfwd = conf->maxfwd;
    }
    apr_table_set(r->headers_in, "Max-Forwards", 
                  apr_psprintf(r->pool, "%ld", (maxfwd > 0) ? maxfwd : 0));

    url = r->filename + 6;
    p = strchr(url, ':');
    if (p == NULL)
        return HTTP_BAD_REQUEST;

    /* If the host doesn't have a domain name, add one and redirect. */
    if (conf->domain != NULL) {
        rc = proxy_needsdomain(r, url, conf->domain);
        if (ap_is_HTTP_REDIRECT(rc))
            return HTTP_MOVED_PERMANENTLY;
    }

    *p = '\0';
    scheme = apr_pstrdup(r->pool, url);
    *p = ':';

    /* Check URI's destination host against NoProxy hosts */
    /* Bypass ProxyRemote server lookup if configured as NoProxy */
    /* we only know how to handle communication to a proxy via http */
    /*if (strcasecmp(scheme, "http") == 0) */
    {
        int ii;
        struct dirconn_entry *list = (struct dirconn_entry *) conf->dirconn->elts;

        for (direct_connect = ii = 0; ii < conf->dirconn->nelts && !direct_connect; ii++) {
            direct_connect = list[ii].matcher(&list[ii], r);
        }
#if DEBUGGING
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      (direct_connect) ? "NoProxy for %s" : "UseProxy for %s",
                      r->uri);
#endif
    }

    /* firstly, try a proxy, unless a NoProxy directive is active */
    if (!direct_connect) {
        for (i = 0; i < proxies->nelts; i++) {
            p2 = ap_strchr_c(ents[i].scheme, ':');  /* is it a partial URL? */
            if (strcmp(ents[i].scheme, "*") == 0 ||
                (ents[i].use_regex && ap_regexec(ents[i].regexp, url, 0,NULL, 0)) ||
                (p2 == NULL && strcasecmp(scheme, ents[i].scheme) == 0) ||
                (p2 != NULL &&
                 strncasecmp(url, ents[i].scheme, strlen(ents[i].scheme)) == 0)) {

                /* handle the scheme */
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "Trying to run scheme_handler against proxy");
                access_status = proxy_run_scheme_handler(r, conf, url, ents[i].hostname, ents[i].port);

                /* an error or success */
                if (access_status != DECLINED && access_status != HTTP_BAD_GATEWAY) {
                    return access_status;
                }
              