    BOOL rv = TRUE;
    const char *ocspuri;
    apr_uri_t uri;

    *prsp = NULL;
    /* Build up OCSP query from server certificate info */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01938)
                 "stapling_renew_response: querying responder");

    req = OCSP_REQUEST_new();
    if (!req)
        goto err;
    id = OCSP_CERTID_dup(cinf->cid);
