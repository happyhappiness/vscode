        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01924)
                    "Bad OCSP responder answer (bad nonce)");
        rc = V_OCSP_CERTSTATUS_UNKNOWN;
    }

    if (rc == V_OCSP_CERTSTATUS_GOOD) {
        /* TODO: allow flags configuration. */
        if (OCSP_basic_verify(basicResponse, NULL, ctx->ctx, 0) != 1) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01925)
                        "failed to verify the OCSP response");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            rc = V_OCSP_CERTSTATUS_UNKNOWN;
        }
    }

    if (rc == V_OCSP_CERTSTATUS_GOOD) {
        int reason = -1, status;
        ASN1_GENERALIZEDTIME *thisup = NULL, *nextup = NULL;
