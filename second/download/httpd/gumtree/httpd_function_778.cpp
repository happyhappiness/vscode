static int proxy_handler(request_rec *r)
{
    char *uri, *scheme, *p;
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
    proxy_balancer *balancer = NULL;
    proxy_worker *worker = NULL;
    int attempts = 0, max_attempts = 0;
    struct dirconn_entry *list = (struct dirconn_entry *)conf->dirconn->elts;

    /* is this for us? */
    if (!r->proxyreq || !r->filename || strncmp(r->filename, "proxy:", 6) != 0)
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

    if (r->method_number == M_TRACE) {
        core_server_config *coreconf = (core_server_config *)
                            ap_get_module_config(sconf, &core_module);

        if (coreconf->trace_enable == AP_TRACE_DISABLE)
        {
            /* Allow "error-notes" string to be printed by ap_send_error_response()
             * Note; this goes nowhere, canned error response need an overhaul.
             */
            apr_table_setn(r->notes, "error-notes",
                           "TRACE forbidden by server configuration");
            apr_table_setn(r->notes, "verbose-error-to", "*");
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "proxy: TRACE forbidden by server configuration");
            return HTTP_FORBIDDEN;
        }

        /* Can't test ap_should_client_block, we aren't ready to send
         * the client a 100 Continue response till the connection has
         * been established
         */
        if (coreconf->trace_enable != AP_TRACE_EXTENDED
            && (r->read_length || r->read_chunked || r->remaining))
        {
            /* Allow "error-notes" string to be printed by ap_send_error_response()
             * Note; this goes nowhere, canned error response need an overhaul.
             */
            apr_table_setn(r->notes, "error-notes",
                           "TRACE with request body is not allowed");
            apr_table_setn(r->notes, "verbose-error-to", "*");
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "proxy: TRACE with request body is not allowed");
            return HTTP_REQUEST_ENTITY_TOO_LARGE;
        }
    }

    uri = r->filename + 6;
    p = strchr(uri, ':');
    if (p == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "proxy_handler no URL in %s", r->filename);
        return HTTP_BAD_REQUEST;
    }

    /* If the host doesn't have a domain name, add one and redirect. */
    if (conf->domain != NULL) {
        rc = proxy_needsdomain(r, uri, conf->domain);
        if (ap_is_HTTP_REDIRECT(rc))
            return HTTP_MOVED_PERMANENTLY;
    }

    scheme = apr_pstrndup(r->pool, uri, p - uri);
    /* Check URI's destination host against NoProxy hosts */
    /* Bypass ProxyRemote server lookup if configured as NoProxy */
    for (direct_connect = i = 0; i < conf->dirconn->nelts &&
                                        !direct_connect; i++) {
        direct_connect = list[i].matcher(&list[i], r);
    }
#if DEBUGGING
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                (direct_connect) ? "NoProxy for %s" : "UseProxy for %s",
                r->uri);
#endif

    do {
        char *url = uri;
        /* Try to obtain the most suitable worker */
        access_status = ap_proxy_pre_request(&worker, &balancer, r, conf, &url);
        if (access_status != OK) {
            /*
             * Only return if access_status is not HTTP_SERVICE_UNAVAILABLE
             * This gives other modules the chance to hook into the
             * request_status hook and decide what to do in this situation.
             */
            if (access_status != HTTP_SERVICE_UNAVAILABLE)
                return access_status;
            /*
             * Ensure that balancer is NULL if worker is NULL to prevent
             * potential problems in the post_request hook.
             */
            if (!worker)
                balancer = NULL;
            goto cleanup;
        }
        if (balancer && balancer->max_attempts_set && !max_attempts)
            max_attempts = balancer->max_attempts;
        /* firstly, try a proxy, unless a NoProxy directive is active */
        if (!direct_connect) {
            for (i = 0; i < proxies->nelts; i++) {
                p2 = ap_strchr_c(ents[i].scheme, ':');  /* is it a partial URL? */
                if (strcmp(ents[i].scheme, "*") == 0 ||
                    (ents[i].use_regex &&
                     ap_regexec(ents[i].regexp, url, 0, NULL, 0) == 0) ||
                    (p2 == NULL && strcasecmp(scheme, ents[i].scheme) == 0) ||
                    (p2 != NULL &&
                    strncasecmp(url, ents[i].scheme,
                                strlen(ents[i].scheme)) == 0)) {

                    /* handle the scheme */
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                 "Trying to run scheme_handler against proxy");
                    access_status = proxy_run_scheme_handler(r, worker,
                                                             conf, url,
                                                             ents[i].hostname,
                                                             ents[i].port);

                    /* an error or success */
                    if (access_status != DECLINED &&
                        access_status != HTTP_BAD_GATEWAY) {
                        goto cleanup;
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
                     "Running scheme %s handler (attempt %d)",
                     scheme, attempts);
        access_status = proxy_run_scheme_handler(r, worker, conf,
                                                 url, NULL, 0);
        if (access_status == OK)
            break;
        else if (access_status == HTTP_INTERNAL_SERVER_ERROR) {
            /* Unrecoverable server error.
             * We can not failover to another worker.
             * Mark the worker as unusable if member of load balancer
             */
            if (balancer)
                worker->s->status |= PROXY_WORKER_IN_ERROR;
            break;
        }
        else if (access_status == HTTP_SERVICE_UNAVAILABLE) {
            /* Recoverable server error.
             * We can failover to another worker
             * Mark the worker as unusable if member of load balancer
             */
            if (balancer) {
                worker->s->status |= PROXY_WORKER_IN_ERROR;
            }
        }
        else {
            /* Unrecoverable error.
             * Return the origin status code to the client.
             */
            break;
        }
        /* Try again if the worker is unusable and the service is
         * unavailable.
         */
    } while (!PROXY_WORKER_IS_USABLE(worker) &&
             max_attempts > attempts++);

    if (DECLINED == access_status) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                    "proxy: No protocol handler was valid for the URL %s. "
                    "If you are using a DSO version of mod_proxy, make sure "
                    "the proxy submodules are included in the configuration "
                    "using LoadModule.", r->uri);
        access_status = HTTP_FORBIDDEN;
        goto cleanup;
    }
cleanup:
    if (balancer) {
        int post_status = proxy_run_post_request(worker, balancer, r, conf);
        if (post_status == DECLINED) {
            post_status = OK; /* no post_request handler available */
            /* TODO: recycle direct worker */
        }
    }

    proxy_run_request_status(&access_status, r);

    return access_status;
}