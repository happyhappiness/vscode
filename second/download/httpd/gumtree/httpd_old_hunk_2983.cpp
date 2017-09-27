    }
    else {
        /* set configured max-forwards */
        maxfwd = conf->maxfwd;
    }
    if (maxfwd >= 0) {
        apr_table_set(r->headers_in, "Max-Forwards",
                      apr_psprintf(r->pool, "%ld", maxfwd));
    }

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
            return HTTP_METHOD_NOT_ALLOWED;
        }

        /* Can't test ap_should_client_block, we aren't ready to send
         * the client a 100 Continue response till the connection has
         * been established
