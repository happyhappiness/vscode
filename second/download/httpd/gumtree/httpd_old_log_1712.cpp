ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "SSL Re-negotiation in conjunction "
                     "with POST method not supported!\n"
                     "hint: try SSLOptions +OptRenegotiate");