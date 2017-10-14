ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                  "read from buffered SSL brigade, mode %d, "
                  "%" APR_OFF_T_FMT " bytes",
                  mode, bytes);