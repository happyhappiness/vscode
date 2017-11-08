static BOOL stapling_renew_response(server_rec *s, modssl_ctx_t *mctx, SSL *ssl,
                                    certinfo *cinf, OCSP_RESPONSE **prsp,
                                    apr_pool_t *pool)
{
    conn_rec *conn      = (conn_rec *)SSL_get_app_data(ssl);
    apr_pool_t *vpool;
    OCSP_REQUEST *req = NULL;
    OCSP_CERTID *id = NULL;
    STACK_OF(X509_EXTENSION) *exts;
    int i;
    BOOL ok = FALSE;
    BOOL rv = TRUE;
    const char *ocspuri;
    apr_uri_t uri;

    *prsp = NULL;
    /* Build up OCSP query from server certificate info */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "stapling_renew_response: querying responder");

    req = OCSP_REQUEST_new();
    if (!req)
        goto err;
    id = OCSP_CERTID_dup(cinf->cid);
    if (!id)
        goto err;
    if (!OCSP_request_add0_id(req, id))
        goto err;
    id = NULL;
    /* Add any extensions to the request */
    SSL_get_tlsext_status_exts(ssl, &exts);
    for (i = 0; i < sk_X509_EXTENSION_num(exts); i++) {
        X509_EXTENSION *ext = sk_X509_EXTENSION_value(exts, i);
        if (!OCSP_REQUEST_add_ext(req, ext, -1))
            goto err;
    }

    if (mctx->stapling_force_url)
        ocspuri = mctx->stapling_force_url;
    else
        ocspuri = cinf->uri;

    /* Create a temporary pool to constrain memory use */
    apr_pool_create(&vpool, conn->pool);

    ok = apr_uri_parse(vpool, ocspuri, &uri);
    if (ok != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "stapling_renew_response: Error parsing uri %s",
                      ocspuri);
        rv = FALSE;
        goto done;
    } 
    else if (strcmp(uri.scheme, "http")) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "stapling_renew_response: Unsupported uri %s", ocspuri);
        rv = FALSE;
        goto done;
    }

    if (!uri.port) {
        uri.port = apr_uri_port_of_scheme(uri.scheme);
    }

    *prsp = modssl_dispatch_ocsp_request(&uri, mctx->stapling_responder_timeout,
                                         req, conn, vpool);

    apr_pool_destroy(vpool);

    if (!*prsp) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "stapling_renew_response: responder error");
        if (mctx->stapling_fake_trylater) {
            *prsp = OCSP_response_create(OCSP_RESPONSE_STATUS_TRYLATER, NULL);
        }
        else {
            goto done;
        }
    } 
    else {
        int response_status = OCSP_response_status(*prsp);

        if (response_status == OCSP_RESPONSE_STATUS_SUCCESSFUL) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                        "stapling_renew_response: query response received");
            stapling_check_response(s, mctx, cinf, *prsp, &ok);
            if (ok == FALSE) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "stapling_renew_response: error in retreived response!");
            }
        } 
        else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "stapling_renew_response: responder error %s",
                         OCSP_response_status_str(response_status));
        }
    }
    if (stapling_cache_response(s, mctx, *prsp, cinf, ok, pool) == FALSE) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "stapling_renew_response: error caching response!");
    }

done:
    if (id)
        OCSP_CERTID_free(id);
    if (req)
        OCSP_REQUEST_free(req);
    return rv;
err:
    rv = FALSE;
    goto done;
}