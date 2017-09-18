        else {
            /* stale data available */
            if (lookup) {
                return DECLINED;
            }

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache: stale cache - test conditional");
            /* if conditional request */
            if (ap_cache_request_is_conditional(r)) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                             r->server,
                             "cache: conditional - add cache_in filter and "
                             "DECLINE");
                /* Why not add CACHE_CONDITIONAL? */
                ap_add_output_filter("CACHE_IN", NULL, r, r->connection);

                return DECLINED;
            }
            /* else if non-conditional request */
            else {
                /* fudge response into a conditional */
                if (info && info->etag) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                                 r->server,
                                 "cache: nonconditional - fudge conditional "
                                 "by etag");
                    /* if we have a cached etag */
                    apr_table_set(r->headers_in, "If-None-Match", info->etag);
                }
                else if (info && info->lastmods) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                                 r->server,
                                 "cache: nonconditional - fudge conditional "
                                 "by lastmod");
                    /* if we have a cached IMS */
                    apr_table_set(r->headers_in, 
                                  "If-Modified-Since", 
                                  info->lastmods);
                }
                else {
                    /* something else - pretend there was no cache */
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                                 r->server,
                                 "cache: nonconditional - no cached "
                                 "etag/lastmods - add cache_in and DECLINE");

                    ap_add_output_filter("CACHE_IN", NULL, r, r->connection);

                    return DECLINED;
                }
                /* add cache_conditional filter */
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                             r->server,
                             "cache: nonconditional - add cache_conditional and"
                             " DECLINE");
                ap_add_output_filter("CACHE_CONDITIONAL", 
                                     NULL, 
                                     r, 
