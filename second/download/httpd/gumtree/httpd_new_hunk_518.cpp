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

    url = r->filename + 6;
    p = strchr(url, ':');
    if (p == NULL)
        return HTTP_BAD_REQUEST;

    /* If the host doesn't have a domain name, add one and redirect. */
