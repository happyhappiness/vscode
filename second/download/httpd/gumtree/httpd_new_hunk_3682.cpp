        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01660)
                      "A prepared statement could not be found for "
                      "AuthDBDUserRealmQuery with the key '%s'", conf->realm);
        return AUTH_GENERAL_ERROR;
    }
    if ((ret = apr_dbd_pvselect(dbd->driver, r->pool, dbd->handle, &res,
                                statement, 0, user, realm, NULL)) != 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01661)
                      "Query execution error looking up '%s:%s' "
                      "in database [%s]",
                      user, realm,
                      apr_dbd_error(dbd->driver, dbd->handle, ret));
        return AUTH_GENERAL_ERROR;
