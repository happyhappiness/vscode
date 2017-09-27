             * behaviour here might break something.
             *
             * So let's make it configurable.
             */
            const char *policy = apr_table_get(r->subprocess_env,
                                               "proxy-interim-response");
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                         "proxy: HTTP: received interim %d response",
                         r->status);
            if (!policy || !strcasecmp(policy, "RFC")) {
                ap_send_interim_response(r, 1);
            }
            /* FIXME: refine this to be able to specify per-response-status
             * policies and maybe also add option to bail out with 502
             */
            else if (strcasecmp(policy, "Suppress")) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                             "undefined proxy interim response policy");
            }
        }
        /* Moved the fixups of Date headers and those affected by
         * ProxyPassReverse/etc from here to ap_proxy_read_headers
         */
