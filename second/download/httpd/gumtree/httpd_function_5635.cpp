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
    apr_int64_t maxfwd;
    proxy_balancer *balancer = NULL;
    proxy_worker *worker = NULL;
    int attempts = 0, max_attempts = 0;
    struct dirconn_entry *list = (struct dirconn_entry *)conf->dirconn->elts;
    int saved_status;

    /* is this for us? */
    if (!r->filename) {
        return DECLINED;
    }

    if (!r->proxyreq) {
        /* We may have forced the proxy handler via config or .htaccess */
        if (r->handler &&
            strncmp(r->handler, "proxy:", 6) == 0 &&
            strncmp(r->filename, "proxy:", 6) != 0) {
            r->proxyreq = PROXYREQ_REVERSE;
            r->filename = apr_pstrcat(r->pool, r->handler, r->filename, NULL);
        }
        else {
            return DECLINED;
        }
    } else if (strncmp(r->filename, "proxy:", 6) != 0) {
        return DECLINED;
    }

    /* handle max-forwards / OPTIONS / TRACE */
    if ((str = apr_table_get(r->headers_in, "Max-Forwards"))) {
        char *end;
        maxfwd = apr_strtoi64(str, &end, 10);
        if (maxfwd < 0 || maxfwd == APR_INT64_MAX || *end) {
            return ap_proxyerror(r, HTTP_BAD_REQUEST,
                    apr_psprintf(r->pool,
                            "Max-Forwards value '%s' could not be parsed", str));
        }
        else if (maxfwd == 0) {
            switch (r->method_number) {
            case M_TRACE: {
                int access_status;
                r->proxyreq = PROXYREQ_NONE;
                access_status = ap_send_http_trace(r);
                ap_die(access_status, r);
                return OK;
            }
            case M_OPTIONS: {
                int access_status;
                r->proxyreq = PROXYREQ_NONE;
                access_status = ap_send_http_options(r);
                ap_die(access_status, r);
                return OK;
            }
            default: {
                return ap_proxyerror(r, HTTP_BAD_REQUEST,
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
    if (maxfwd >= 0) {
        apr_table_setn(r->headers_in, "Max-Forwards",
                       apr_psprintf(r->pool, "%" APR_INT64_T_FMT, maxfwd));
    }

    if (r->method_number == M_TRACE) {
        core_server_config *coreconf = (core_server_config *)
                                       ap_get_core_module_config(sconf);

        if (coreconf->trace_enable == AP_TRACE_DISABLE)
        {
            /* Allow "error-notes" string to be printed by ap_send_error_response()
             * Note; this goes nowhere, canned error response need an overhaul.
             */
            apr_table_setn(r->notes, "error-notes",
                           "TRACE forbidden by server configuration");
            apr_table_setn(r->notes, "verbose-error-to", "*");
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01139)
                          "TRACE forbidden by server configuration");
            return HTTP_METHOD_NOT_ALLOWED;
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
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01140)
                          "TRACE with request body is not allowed");
            return HTTP_REQUEST_ENTITY_TOO_LARGE;
        }
    }

    uri = r->filename + 6;
    p = strchr(uri, ':');
    if (p == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01141)
                      "proxy_handler no URL in %s", r->filename);
        return HTTP_BAD_REQUEST;
    }

    /* If the host doesn't have a domain name, add one and redirect. */
    if (conf->domain != NULL) {
        rc = proxy_needsdomain(r, uri, conf->domain);
        if (ap_is_HTTP_REDIRECT(rc))
            return HTTP_MOVED_PERMANENTLY;
    }

    scheme = apr_pstrmemdup(r->pool, uri, p - uri);
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

        /* Initialise worker if needed, note the shared area must be initialized by the balancer logic */
        if (balancer) {
            ap_proxy_initialize_worker(worker, r->server, conf->pool);
        }

        if (balancer && balancer->s->max_attempts_set && !max_attempts)
            max_attempts = balancer->s->max_attempts;
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
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01142)
                                  "Trying to run scheme_handler against proxy");
                    access_status = proxy_run_scheme_handler(r, worker,
                                                             conf, url,
                                                             ents[i].hostname,
                                                             ents[i].port);

                    /* Did the scheme handler process the request? */
                    if (access_status != DECLINED) {
                        const char *cl_a;
                        char *end;
                        apr_off_t cl;

                        /*
                         * An fatal error or success, so no point in
                         * retrying with a direct connection.
                         */
                        if (access_status != HTTP_BAD_GATEWAY) {
                            goto cleanup;
                        }
                        cl_a = apr_table_get(r->headers_in, "Content-Length");
                        if (cl_a) {
                            apr_strtoff(&cl, cl_a, &end, 10);
                            /*
                             * The request body is of length > 0. We cannot
                             * retry with a direct connection since we already
                             * sent (parts of) the request body to the proxy
                             * and do not have any longer.
                             */
                            if (cl > 0) {
                                goto cleanup;
                            }
                        }
                        /*
                         * Transfer-Encoding was set as input header, so we had
                         * a request body. We cannot retry with a direct
                         * connection for the same reason as above.
                         */
                        if (apr_table_get(r->headers_in, "Transfer-Encoding")) {
                            goto cleanup;
                        }
                    }
                }
            }
        }

        /* otherwise, try it direct */
        /* N.B. what if we're behind a firewall, where we must use a proxy or
        * give up??
        */

        /* handle the scheme */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01143)
                      "Running scheme %s handler (attempt %d)",
                      scheme, attempts);
        AP_PROXY_RUN(r, worker, conf, url, attempts);
        access_status = proxy_run_scheme_handler(r, worker, conf,
                                                 url, NULL, 0);
        if (access_status == OK
                || apr_table_get(r->notes, "proxy-error-override"))
            break;
        else if (access_status == HTTP_INTERNAL_SERVER_ERROR) {
            /* Unrecoverable server error.
             * We can not failover to another worker.
             * Mark the worker as unusable if member of load balancer
             */
            if (balancer) {
                worker->s->status |= PROXY_WORKER_IN_ERROR;
                worker->s->error_time = apr_time_now();
            }
            break;
        }
        else if (access_status == HTTP_SERVICE_UNAVAILABLE) {
            /* Recoverable server error.
             * We can failover to another worker
             * Mark the worker as unusable if member of load balancer
             */
            if (balancer) {
                worker->s->status |= PROXY_WORKER_IN_ERROR;
                worker->s->error_time = apr_time_now();
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
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01144)
                      "No protocol handler was valid for the URL %s. "
                      "If you are using a DSO version of mod_proxy, make sure "
                      "the proxy submodules are included in the configuration "
                      "using LoadModule.", r->uri);
        access_status = HTTP_INTERNAL_SERVER_ERROR;
        goto cleanup;
    }
cleanup:
    /*
     * Save current r->status and set it to the value of access_status which
     * might be different (e.g. r->status could be HTTP_OK if e.g. we override
     * the error page on the proxy or if the error was not generated by the
     * backend itself but by the proxy e.g. a bad gateway) in order to give
     * ap_proxy_post_request a chance to act correctly on the status code.
     */
    saved_status = r->status;
    r->status = access_status;
    ap_proxy_post_request(worker, balancer, r, conf);
    /*
     * Only restore r->status if it has not been changed by
     * ap_proxy_post_request as we assume that this change was intentional.
     */
    if (r->status == access_status) {
        r->status = saved_status;
    }

    proxy_run_request_status(&access_status, r);
    AP_PROXY_RUN_FINISHED(r, attempts, access_status);

    return access_status;
}