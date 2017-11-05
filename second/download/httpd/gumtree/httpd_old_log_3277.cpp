ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, intern->r, "missing "
                          "directive name in parsed document %s",
                          intern->r->filename);