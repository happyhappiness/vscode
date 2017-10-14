ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c,
                  "read from buffered SSL brigade, mode %d, "
                  "%" APR_OFF_T_FMT " bytes",
                  mode, bytes);