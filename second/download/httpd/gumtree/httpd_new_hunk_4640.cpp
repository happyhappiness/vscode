        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01924)
                    "Bad OCSP responder answer (bad nonce)");
        rc = V_OCSP_CERTSTATUS_UNKNOWN;
    }

    if (rc == V_OCSP_CERTSTATUS_GOOD) {
        /* Check if OCSP certificate verification required */
        if (sc->server->ocsp_noverify != TRUE) {
            /* Modify OCSP response verification to include OCSP Responder cert */
            if (OCSP_basic_verify(basicResponse, sc->server->ocsp_certs, X509_STORE_CTX_get0_store(ctx),
                                  sc->server->ocsp_verify_flags) != 1) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01925)
                            "failed to verify the OCSP response");
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
                rc = V_OCSP_CERTSTATUS_UNKNOWN;
            }
        }
    }

    if (rc == V_OCSP_CERTSTATUS_GOOD) {
        int reason = -1, status;
        ASN1_GENERALIZEDTIME *thisup = NULL, *nextup = NULL;
