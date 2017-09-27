
    if (cfg->query == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01649)
                      "No query configured for dbd-group!");
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if (dbd == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02903)
                      "No db handle available for dbd-query! "
                      "Check your database access");
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    query = apr_hash_get(dbd->prepared, cfg->query, APR_HASH_KEY_STRING);
    if (query == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01650)
                      "Error retrieving query for dbd-group!");
        return HTTP_INTERNAL_SERVER_ERROR;
    }
