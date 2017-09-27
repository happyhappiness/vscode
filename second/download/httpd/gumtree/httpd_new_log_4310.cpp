ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00887)
                                              "error processing body.%s",
                                              r->connection->aborted ?
                                              " Client aborted connection." : "");