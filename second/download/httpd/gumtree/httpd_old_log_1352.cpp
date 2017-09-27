ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "Certificate Verification: "
                     "depth: %d, subject: %s, issuer: %s",
                     errdepth,
                     sname ? sname : "-unknown-",
                     iname ? iname : "-unknown-");