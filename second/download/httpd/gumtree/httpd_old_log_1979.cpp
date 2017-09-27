ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                          "proxy: error processing body.%s",
                                          r->connection->aborted ?
                                          " Client aborted connection." : "");