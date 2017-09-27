                      APLOGrtrace4(r) ? ", headers:" : "");

        /*
         * Date and Server are less interesting, use TRACE5 for them while
         * using TRACE4 for the other headers.
         */
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "  Date: %s",
                      proxy_date ? proxy_date : date );
        if (server)
            ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "  Server: %s",
                          server);
    }


    /* unset so we don't send them again */
    apr_table_unset(r->headers_out, "Date");        /* Avoid bogosity */
