ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, io->connection,
                      "h2_conn_io: writing %ld bytes to brigade", (long)length);