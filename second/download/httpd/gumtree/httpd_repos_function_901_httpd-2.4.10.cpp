static int verify_ocsp_status(X509 *cert, X509_STORE_CTX *ctx, conn_rec *c,
                              SSLSrvConfigRec *sc, server_rec *s,
                              apr_pool_t *pool)
{
    int rc = V_OCSP_CERTSTATUS_GOOD;
    OCSP_RESPONSE *response = NULL;
    OCSP_BASICRESP *basicResponse = NULL;
    OCSP_REQUEST *request = NULL;
    OCSP_CERTID *certID = NULL;
    apr_uri_t *ruri;

    ruri = determine_responder_uri(sc, cert, c, pool);
    if (!ruri) {
        return V_OCSP_CERTSTATUS_UNKNOWN;
    }

    request = create_request(ctx, cert, &certID, s, pool, sc);
    if (request) {
        apr_interval_time_t to = sc->server->ocsp_responder_timeout == UNSET ?
                                 apr_time_from_sec(DEFAULT_OCSP_TIMEOUT) :
                                 sc->server->ocsp_responder_timeout;
        response = modssl_dispatch_ocsp_request(ruri, to, request, c, pool);
    }

    if (!request || !response) {
        rc = V_OCSP_CERTSTATUS_UNKNOWN;
    }

    if (rc == V_OCSP_CERTSTATUS_GOOD) {
        int r = OCSP_response_status(response);

        if (r != OCSP_RESPONSE_STATUS_SUCCESSFUL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01922)
                         "OCSP response not successful: %d", rc);
            rc = V_OCSP_CERTSTATUS_UNKNOWN;
        }
    }

    if (rc == V_OCSP_CERTSTATUS_GOOD) {
        basicResponse = OCSP_response_get1_basic(response);
        if (!basicResponse) {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(01923)
                          "could not retrieve OCSP basic response");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            rc = V_OCSP_CERTSTATUS_UNKNOWN;
        }
    }

    if (rc == V_OCSP_CERTSTATUS_GOOD &&
            sc->server->ocsp_use_request_nonce != FALSE &&
            OCSP_check_nonce(request, basicResponse) != 1) {
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

        rc = OCSP_resp_find_status(basicResponse, certID, &status,
                                   &reason, NULL, &thisup, &nextup);
        if (rc != 1) {
            ssl_log_cxerror(SSLLOG_MARK, APLOG_ERR, 0, c, cert, APLOGNO(02272)
                            "failed to retrieve OCSP response status");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            rc = V_OCSP_CERTSTATUS_UNKNOWN;
        }
        else {
            rc = status;
        }

        /* Check whether the response is inside the defined validity
         * period; otherwise fail.  */
        if (rc != V_OCSP_CERTSTATUS_UNKNOWN) {
            long resptime_skew = sc->server->ocsp_resptime_skew == UNSET ?
                                 DEFAULT_OCSP_MAX_SKEW : sc->server->ocsp_resptime_skew;
            /* oscp_resp_maxage can be passed verbatim - UNSET (-1) means
             * that responses can be of any age as long as nextup is in the
             * future. */
            int vrc  = OCSP_check_validity(thisup, nextup, resptime_skew,
                                           sc->server->ocsp_resp_maxage);
            if (vrc != 1) {
                ssl_log_cxerror(SSLLOG_MARK, APLOG_ERR, 0, c, cert, APLOGNO(02273)
                                "OCSP response outside validity period");
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
                rc = V_OCSP_CERTSTATUS_UNKNOWN;
            }
        }

        {
            int level =
                (status == V_OCSP_CERTSTATUS_GOOD) ? APLOG_INFO : APLOG_ERR;
            const char *result =
                status == V_OCSP_CERTSTATUS_GOOD ? "good" :
                (status == V_OCSP_CERTSTATUS_REVOKED ? "revoked" : "unknown");

            ssl_log_cxerror(SSLLOG_MARK, level, 0, c, cert,
                            "OCSP validation completed, "
                            "certificate status: %s (%d, %d)",
                            result, status, reason);
        }
    }

    if (request) OCSP_REQUEST_free(request);
    if (response) OCSP_RESPONSE_free(response);
    if (basicResponse) OCSP_BASICRESP_free(basicResponse);
    /* certID is freed when the request is freed */

    return rc;
}