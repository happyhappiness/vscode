ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                              "SSL Proxy: Peer certificate CN mismatch:"
                              " Certificate CN: %s Requested hostname: %s",
                              hostname, hostname_note);