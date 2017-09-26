ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, intern->r, "missing "
                          "argument name for value to tag %s in %s",
                          apr_pstrmemdup(intern->r->pool, intern->directive,
                                         intern->directive_len),
                                         intern->r->filename);