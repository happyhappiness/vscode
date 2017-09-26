            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "proxy: TRACE with request body is not allowed");
            return HTTP_REQUEST_ENTITY_TOO_LARGE;
        }
    }

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
                (ents[i].use_regex && 
                 ap_regexec(ents[i].regexp, url, 0,NULL, 0) == 0) ||
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
                /* we failed to talk to the upstream proxy */
            }
        }
    }

    /* otherwise, try it direct */
    /* N.B. what if we're behind a firewall, where we must use a proxy or
     * give up??
     */

    /* handle the scheme */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "Trying to run scheme_handler");
    access_status = proxy_run_scheme_handler(r, conf, url, NULL, 0);
    if (DECLINED == access_status) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                    "proxy: No protocol handler was valid for the URL %s. "
                    "If you are using a DSO version of mod_proxy, make sure "
                    "the proxy submodules are included in the configuration "
                    "using LoadModule.", r->uri);
        return HTTP_FORBIDDEN;
    }
    return access_status;
}

/* -------------------------------------------------------------- */
/* Setup configurable data */

