
    if (cfg->query == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01642)
                      "No query configured for %s!", action);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if (dbd == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02902)
                      "No db handle available for %s! "
                      "Check your database access",
                      action);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    query = apr_hash_get(dbd->prepared, cfg->query, APR_HASH_KEY_STRING);
    if (query == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01643)
                      "Error retrieving Query for %s!", action);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
