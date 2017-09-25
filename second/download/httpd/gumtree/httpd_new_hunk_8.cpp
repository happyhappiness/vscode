                    /* something else - pretend there was no cache */
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                                 r->server,
                                 "cache: nonconditional - no cached "
                                 "etag/lastmods - add cache_in and DECLINE");

                    ap_add_output_filter_handle(cache_in_filter_handle, NULL,
                                                r, r->connection);

                    return DECLINED;
                }
                /* add cache_conditional filter */
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                             r->server,
                             "cache: nonconditional - add cache_conditional "
                             "and DECLINE");
                ap_add_output_filter_handle(cache_conditional_filter_handle,
                                            NULL, 
                                            r, 
                                            r->connection);

                return DECLINED;
            }
        }
    }
    else {
