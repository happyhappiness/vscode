
    rv = fetch_dbm_value(conf->dbmtype, conf->pwfile,
                         apr_pstrcat(r->pool, user, ":", realm, NULL),
                         &dbm_hash, r->pool);

    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01755)
                      "Could not open dbm (type %s) hash file: %s",
                      conf->dbmtype, conf->pwfile);
        return AUTH_GENERAL_ERROR;
    }

    if (!dbm_hash) {
