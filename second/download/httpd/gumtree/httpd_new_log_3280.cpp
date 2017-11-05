ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01371)
                                  "unknown directive \"%s\" in parsed doc %s",
                                  apr_pstrmemdup(r->pool, intern->directive,
                                                 intern->directive_len),
                                                 r->filename);