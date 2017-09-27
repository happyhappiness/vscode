ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02255)
                              "Changed client verification type will force "
                              "%srenegotiation",
                              renegotiate_quick ? "quick " : "");