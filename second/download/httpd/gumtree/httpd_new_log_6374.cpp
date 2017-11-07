ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01661)
                      "Query execution error looking up '%s:%s' "
                      "in database [%s]",
                      user, realm,
                      apr_dbd_error(dbd->driver, dbd->handle, ret));