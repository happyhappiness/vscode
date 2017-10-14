ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "bad response from OCSP server: %s",
                      line ? line : "(none)");