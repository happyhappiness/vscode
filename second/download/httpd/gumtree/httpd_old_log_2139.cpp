ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, conn,
                      "Certificate Verification: "
                      "depth: %d, subject: %s, issuer: %s",
                      errdepth,
                      sname ? sname : "-unknown-",
                      iname ? iname : "-unknown-");