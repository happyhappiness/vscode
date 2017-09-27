ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Negotiation: discovered file(s) matching request: %s"
                      " (None could be negotiated).",
                      r->filename);