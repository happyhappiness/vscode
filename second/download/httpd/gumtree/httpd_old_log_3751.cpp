ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
                              "can't open translation %s->%s",
                              dc->charset_source, dc->charset_default);