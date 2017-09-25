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
                             "cache: nonconditional - add cache_conditional "
                             "and DECLINE");
                ap_add_output_filter("CACHE_CONDITIONAL", 
                                     NULL, 
                                     r, 
                                     r->connection);

                return DECLINED;
            }
        }
    }
    else {
