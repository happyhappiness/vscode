ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "h2_h2, process_conn, "
                          "new connection using protocol '%s', direct=%d, "
                          "tls acceptable=%d", proto, h2_allows_h2_direct(c), 
                          h2_is_acceptable_connection(c, 1));