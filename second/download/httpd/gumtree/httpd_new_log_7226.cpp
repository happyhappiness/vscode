ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01656)
                      "Query execution error looking up '%s' "
                      "in database [%s]",
                      user, apr_dbd_error(dbd->driver, dbd->handle, ret));