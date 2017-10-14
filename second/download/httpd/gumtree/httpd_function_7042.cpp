static authn_status authn_dbd_password(request_rec *r, const char *user,
                                       const char *password)
{
    apr_status_t rv;
    const char *dbd_password = NULL;
    apr_dbd_prepared_t *statement;
    apr_dbd_results_t *res = NULL;
    apr_dbd_row_t *row = NULL;

    authn_dbd_conf *conf = ap_get_module_config(r->per_dir_config,
                                                &authn_dbd_module);
    ap_dbd_t *dbd = authn_dbd_acquire_fn(r);
    if (dbd == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01653)
                      "Failed to acquire database connection to look up "
                      "user '%s'", user);
        return AUTH_GENERAL_ERROR;
    }

    if (conf->user == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01654)
                      "No AuthDBDUserPWQuery has been specified");
        return AUTH_GENERAL_ERROR;
    }

    statement = apr_hash_get(dbd->prepared, conf->user, APR_HASH_KEY_STRING);
    if (statement == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01655)
                      "A prepared statement could not be found for "
                      "AuthDBDUserPWQuery with the key '%s'", conf->user);
        return AUTH_GENERAL_ERROR;
    }
    if (apr_dbd_pvselect(dbd->driver, r->pool, dbd->handle, &res, statement,
                              0, user, NULL) != 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01656)
                      "Query execution error looking up '%s' "
                      "in database", user);
        return AUTH_GENERAL_ERROR;
    }
    for (rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1);
         rv != -1;
         rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1)) {
        if (rv != 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01657)
                          "Error retrieving results while looking up '%s' "
                          "in database", user);
            return AUTH_GENERAL_ERROR;
        }
        if (dbd_password == NULL) {
#if APU_MAJOR_VERSION > 1 || (APU_MAJOR_VERSION == 1 && APU_MINOR_VERSION >= 3)
            /* add the rest of the columns to the environment */
            int i = 1;
            const char *name;
            for (name = apr_dbd_get_name(dbd->driver, res, i);
                 name != NULL;
                 name = apr_dbd_get_name(dbd->driver, res, i)) {

                char *str = apr_pstrcat(r->pool, AUTHN_PREFIX,
                                        name,
                                        NULL);
                int j = sizeof(AUTHN_PREFIX)-1; /* string length of "AUTHENTICATE_", excluding the trailing NIL */
                while (str[j]) {
                    if (!apr_isalnum(str[j])) {
                        str[j] = '_';
                    }
                    else {
                        str[j] = apr_toupper(str[j]);
                    }
                    j++;
                }
                apr_table_set(r->subprocess_env, str,
                              apr_dbd_get_entry(dbd->driver, row, i));
                i++;
            }
#endif
            dbd_password = apr_dbd_get_entry(dbd->driver, row, 0);
        }
        /* we can't break out here or row won't get cleaned up */
    }

    if (!dbd_password) {
        return AUTH_USER_NOT_FOUND;
    }
    AUTHN_CACHE_STORE(r, user, NULL, dbd_password);

    rv = apr_password_validate(password, dbd_password);

    if (rv != APR_SUCCESS) {
        return AUTH_DENIED;
    }

    return AUTH_GRANTED;
}