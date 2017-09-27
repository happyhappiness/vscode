ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, 
                              "Reuse %s LDC %pp", 
                              l->bound ? "bound" : "unbound", l);