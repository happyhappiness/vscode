                                            r, r->connection);

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
