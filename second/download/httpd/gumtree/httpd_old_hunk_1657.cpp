            /* it should be go on as an internal proxy request */

            /* check if the proxy module is enabled, so
             * we can actually use it!
             */
            if (!proxy_available) {
                ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                             "attempt to make remote request from mod_rewrite "
                             "without proxy enabled: %s", r->filename);
                return FORBIDDEN;
            }

            /* make sure the QUERY_STRING and
