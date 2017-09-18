
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
