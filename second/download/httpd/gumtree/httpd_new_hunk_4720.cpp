    if (statement == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01655)
                      "A prepared statement could not be found for "
                      "AuthDBDUserPWQuery with the key '%s'", conf->user);
        return AUTH_GENERAL_ERROR;
    }
    if ((ret = apr_dbd_pvselect(dbd->driver, r->pool, dbd->handle, &res,
                                statement, 0, user, NULL) != 0)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01656)
                      "Query execution error looking up '%s' "
                      "in database [%s]",
                      user, apr_dbd_error(dbd->driver, dbd->handle, ret));
        return AUTH_GENERAL_ERROR;
    }
    for (rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1);
         rv != -1;
         rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1)) {
        if (rv != 0) {
