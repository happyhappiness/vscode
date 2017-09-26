    if (dbd == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Error looking up %s in database", user);
        return AUTH_GENERAL_ERROR;
    }
    if (conf->realm == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "No AuthDBDUserRealmQuery has been specified.");
        return AUTH_GENERAL_ERROR;
    }
    statement = apr_hash_get(dbd->prepared, conf->realm, APR_HASH_KEY_STRING);
    if (statement == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "A prepared statement could not be found for AuthDBDUserRealmQuery, key '%s'.", conf->realm);
        return AUTH_GENERAL_ERROR;
    }
    if (apr_dbd_pvselect(dbd->driver, r->pool, dbd->handle, &res, statement,
                              0, user, realm, NULL) != 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Error looking up %s:%s in database", user, realm);
