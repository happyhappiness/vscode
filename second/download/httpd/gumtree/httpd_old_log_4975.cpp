ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "could not read response headers from OCSP server, "
                      "exceeded maximum count (%u)", MAX_HEADERS);