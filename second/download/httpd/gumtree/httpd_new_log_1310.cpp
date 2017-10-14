ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "Changed client verification type will force "
                              "%srenegotiation",
                              renegotiate_quick ? "quick " : "");