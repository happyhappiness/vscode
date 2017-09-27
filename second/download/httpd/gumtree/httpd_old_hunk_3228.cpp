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
