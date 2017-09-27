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

            if (rulestatus == ACTION_NOESCAPE) {
