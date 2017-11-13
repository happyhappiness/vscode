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

    request = create_request(ctx, cert, &certID, s, pool);
    if (request) {
        /* Use default I/O timeout for the server. */
        response = modssl_dispatch_ocsp_request(ruri, 
                                                mySrvFromConn(c)->timeout,
                                                request, c, pool);
    }

    if (!request || !response) {
        rc = V_OCSP_CERTSTATUS_UNKNOWN;
    }
    
    if (rc == V_OCSP_CERTSTATUS_GOOD) {
        int r = OCSP_response_status(response);

        if (r != OCSP_RESPONSE_STATUS_SUCCESSFUL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                         "OCSP response not successful: %d", rc);
            rc = V_OCSP_CERTSTATUS_UNKNOWN;
        }
    }
    
    if (rc == V_OCSP_CERTSTATUS_GOOD) {
        basicResponse = OCSP_response_get1_basic(response);
        if (!basicResponse) {
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                          "could not retrieve OCSP basic response");
            rc = V_OCSP_CERTSTATUS_UNKNOWN;
        }
    }
    
    if (rc == V_OCSP_CERTSTATUS_GOOD) {
        if (OCSP_check_nonce(request, basicResponse) != 1) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                        "Bad OCSP responder answer (bad nonce)");
            rc = V_OCSP_CERTSTATUS_UNKNOWN;
        }
    }
    
    if (rc == V_OCSP_CERTSTATUS_GOOD) {
        /* TODO: allow flags configuration. */
        if (OCSP_basic_verify(basicResponse, NULL, ctx->ctx, 0) != 1) {
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                        "failed to verify the OCSP response");
            rc = V_OCSP_CERTSTATUS_UNKNOWN;
        }
    }
    
    if (rc == V_OCSP_CERTSTATUS_GOOD) {
        int reason = -1, status;
        ASN1_GENERALIZEDTIME *thisup = NULL, *nextup = NULL;

        rc = OCSP_resp_find_status(basicResponse, certID, &status,
                                   &reason, NULL, &thisup, &nextup);
        if (rc != 1) {
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            ssl_log_cxerror(SSLLOG_MARK, APLOG_ERR, 0, c, cert,
                            "failed to retrieve OCSP response status");
            rc = V_OCSP_CERTSTATUS_UNKNOWN;
        }
        else {
            rc = status;
        }

        /* TODO: make these configurable. */
#define MAX_SKEW (60)
#define MAX_AGE (360)

        /* Check whether the response is inside the defined validity
         * period; otherwise fail.  */
        if (rc != V_OCSP_CERTSTATUS_UNKNOWN) {
            int vrc  = OCSP_check_validity(thisup, nextup, MAX_SKEW, MAX_AGE);
            
            if (vrc != 1) {
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
                ssl_log_cxerror(SSLLOG_MARK, APLOG_ERR, 0, c, cert,
                                "OCSP response outside validity period");
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