        thisport = buf;
    }
    thisurl = apr_table_get(r->subprocess_env, ENVVAR_SCRIPT_URL);

    /* set the variable */
    var = apr_pstrcat(r->pool, ap_http_method(r), "://", thisserver, thisport,
                      thisurl, NULL);
    apr_table_setn(r->subprocess_env, ENVVAR_SCRIPT_URI, var);

    if (!(saved_rulestatus = apr_table_get(r->notes,"mod_rewrite_rewritten"))) {
        /* if filename was not initially set,
         * we start with the requested URI
         */
        if (r->filename == NULL) {
            r->filename = apr_pstrdup(r->pool, r->uri);
            rewritelog(r, 2, "init rewrite engine with requested uri %s",
                       r->filename);
        }
        else {
            rewritelog(r, 2, "init rewrite engine with passed filename %s."
                       " Original uri = %s", r->filename, r->uri);
        }

        /*
         *  now apply the rules ...
         */
        rulestatus = apply_rewrite_list(r, conf->rewriterules, NULL);
        apr_table_set(r->notes,"mod_rewrite_rewritten",
                      apr_psprintf(r->pool,"%d",rulestatus));
    }
    else {
        rewritelog(r, 2,
                   "uri already rewritten. Status %s, Uri %s, r->filename %s",
                   saved_rulestatus, r->uri, r->filename);
        rulestatus = atoi(saved_rulestatus);
    }

    if (rulestatus) {
        unsigned skip;

        if (strlen(r->filename) > 6 &&
            strncmp(r->filename, "proxy:", 6) == 0) {
            /* it should be go on as an internal proxy request */

            /* check if the proxy module is enabled, so
             * we can actually use it!
             */
            if (!proxy_available) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "attempt to make remote request from mod_rewrite "
                              "without proxy enabled: %s", r->filename);
                return HTTP_FORBIDDEN;
            }

            /* make sure the QUERY_STRING and
             * PATH_INFO parts get incorporated
             */
            if (r->path_info != NULL) {
                r->filename = apr_pstrcat(r->pool, r->filename,
                                          r->path_info, NULL);
            }
            if (r->args != NULL &&
                r->uri == r->unparsed_uri) {
                /* see proxy_http:proxy_http_canon() */
                r->filename = apr_pstrcat(r->pool, r->filename,
                                          "?", r->args, NULL);
            }

            /* now make sure the request gets handled by the proxy handler */
            if (PROXYREQ_NONE == r->proxyreq) {
                r->proxyreq = PROXYREQ_REVERSE;
            }
            r->handler  = "proxy-server";

            rewritelog(r, 1, "go-ahead with proxy request %s [OK]",
                       r->filename);
            return OK;
        }
        else if ((skip = is_absolute_uri(r->filename)) > 0) {
            /* it was finally rewritten to a remote URL */

            if (rulestatus != ACTION_NOESCAPE) {
                rewritelog(r, 1, "escaping %s for redirect", r->filename);
                r->filename = escape_absolute_uri(r->pool, r->filename, skip);
            }

            /* append the QUERY_STRING part */
            if (r->args) {
                r->filename = apr_pstrcat(r->pool, r->filename, "?",
                                          (rulestatus == ACTION_NOESCAPE)
                                            ? r->args
                                            : ap_escape_uri(r->pool, r->args),
                                          NULL);
            }

            /* determine HTTP redirect response code */
            if (ap_is_HTTP_REDIRECT(r->status)) {
                n = r->status;
                r->status = HTTP_OK; /* make Apache kernel happy */
