    apr_dbd_row_t *row = NULL;

    authn_dbd_conf *conf = ap_get_module_config(r->per_dir_config,
                                                &authn_dbd_module);
    ap_dbd_t *dbd = authn_dbd_acquire_fn(r);
    if (dbd == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Failed to acquire database connection to look up "
                      "user '%s'", user);
        return AUTH_GENERAL_ERROR;
    }

    if (conf->user == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "No AuthDBDUserPWQuery has been specified");
        return AUTH_GENERAL_ERROR;
    }

    statement = apr_hash_get(dbd->prepared, conf->user, APR_HASH_KEY_STRING);
    if (statement == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "A prepared statement could not be found for "
                      "AuthDBDUserPWQuery with the key '%s'", conf->user);
        return AUTH_GENERAL_ERROR;
    }
    if (apr_dbd_pvselect(dbd->driver, r->pool, dbd->handle, &res, statement,
                              0, user, NULL) != 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Query execution error looking up '%s' "
                      "in database", user);
        return AUTH_GENERAL_ERROR;
    }
    for (rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1);
         rv != -1;
         rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1)) {
        if (rv != 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "Error retrieving results while looking up '%s' "
                          "in database", user);
            return AUTH_GENERAL_ERROR;
        }
        if (dbd_password == NULL) {
#if APU_MAJOR_VERSION > 1 || (APU_MAJOR_VERSION == 1 && APU_MINOR_VERSION >= 3)
