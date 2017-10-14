ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00877)
                          "read zero bytes, expecting"
                          " %" APR_OFF_T_FMT " bytes",
                          content_length);