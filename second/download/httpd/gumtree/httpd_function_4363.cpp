static int stapling_check_response(server_rec *s, modssl_ctx_t *mctx,
                                   certinfo *cinf, OCSP_RESPONSE *rsp,
                                   BOOL *pok)
{
    int status, reason;
    OCSP_BASICRESP *bs = NULL;
    ASN1_GENERALIZEDTIME *rev, *thisupd, *nextupd;
    int response_status = OCSP_response_status(rsp);

    if (pok)
        *pok = FALSE;
    /* Check to see if response is an error. If so we automatically accept
     * it because it would have expired from the cache if it was time to
     * retry.
     */
    if (response_status != OCSP_RESPONSE_STATUS_SUCCESSFUL) {
        if (mctx->stapling_return_errors)
            return SSL_TLSEXT_ERR_OK;
        else
            return SSL_TLSEXT_ERR_NOACK;
    }

    bs = OCSP_response_get1_basic(rsp);
    if (bs == NULL) {
        /* If we can't parse response just pass it to client */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "stapling_check_response: Error Parsing Response!");
        return SSL_TLSEXT_ERR_OK;
    }

    if (!OCSP_resp_find_status(bs, cinf->cid, &status, &reason, &rev,
                               &thisupd, &nextupd)) {
        /* If ID not present just pass back to client */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "stapling_check_response: certificate ID not present in response!");
    } 
    else {
        if (OCSP_check_validity(thisupd, nextupd,
                                mctx->stapling_resptime_skew,
                                mctx->stapling_resp_maxage)) {
            if (pok)
                *pok = TRUE;
        }
        else {
            /* If pok is not NULL response was direct from a responder and
             * the times should be valide. If pok is NULL the response was
             * retrieved from cache and it is expected to subsequently expire
             */
            if (pok) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "stapling_check_response: response times invalid");
            } 
            else {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                             "stapling_check_response: cached response expired");
            }

            OCSP_BASICRESP_free(bs);
            return SSL_TLSEXT_ERR_NOACK;
        }
    }

    OCSP_BASICRESP_free(bs);

    return SSL_TLSEXT_ERR_OK;
}