    char *colon_pw;

    rv = fetch_dbm_value(conf->dbmtype, conf->pwfile, user, &dbm_password,
                         r->pool);

    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01754)
                      "could not open dbm (type %s) auth file: %s",
                      conf->dbmtype, conf->pwfile);
        return AUTH_GENERAL_ERROR;
    }

    if (!dbm_password) {
