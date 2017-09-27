    apr_dbd_prepared_t *statement;

    if (!session_dbd_prepare_fn || !session_dbd_acquire_fn) {
        session_dbd_prepare_fn = APR_RETRIEVE_OPTIONAL_FN(ap_dbd_prepare);
        session_dbd_acquire_fn = APR_RETRIEVE_OPTIONAL_FN(ap_dbd_acquire);
        if (!session_dbd_prepare_fn || !session_dbd_acquire_fn) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01850)
                          "You must load mod_dbd to enable AuthDBD functions");
            return APR_EGENERAL;
        }
    }

    dbd = session_dbd_acquire_fn(r);
    if (!dbd) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01851)
                      "failed to acquire database connection");
        return APR_EGENERAL;
    }

    statement = apr_hash_get(dbd->prepared, query, APR_HASH_KEY_STRING);
    if (!statement) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01852)
                      "failed to find the prepared statement called '%s'", query);
        return APR_EGENERAL;
    }

    *dbdp = dbd;
    *statementp = statement;
