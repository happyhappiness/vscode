static int stapling_check_response(server_rec *s, modssl_ctx_t *mctx,
                                   certinfo *cinf, OCSP_RESPONSE *rsp,
                                   BOOL *pok)
{
    int status = V_OCSP_CERTSTATUS_UNKNOWN;
    int reason = OCSP_REVOKED_STATUS_NOSTATUS;
    OCSP_BASICRESP *bs = NULL;
    ASN1_GENERALIZEDTIME *rev, *thisupd, *nextupd;
    int response_status = OCSP_response_status(rsp);
    int rv = SSL_TLSEXT_ERR_OK;

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
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01934)
                     "stapling_check_response: Error Parsing Response!");
        return SSL_TLSEXT_ERR_OK;
    }

    if (!OCSP_resp_find_status(bs, cinf->cid, &status, &reason, &rev,
                               &thisupd, &nextupd)) {
        /* If ID not present pass back to client (if configured so) */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01935)
                     "stapling_check_response: certificate ID not present in response!");
        if (mctx->stapling_return_errors == FALSE)
            rv = SSL_TLSEXT_ERR_NOACK;
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
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01936)
                             "stapling_check_response: response times invalid");
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01937)
                             "stapling_check_response: cached response expired");
            }

            rv = SSL_TLSEXT_ERR_NOACK;
        }

        if (status != V_OCSP_CERTSTATUS_GOOD) {
            char snum[MAX_STRING_LEN] = { '\0' };
            BIO *bio = BIO_new(BIO_s_mem());

            if (bio) {
                int n;
                if ((i2a_ASN1_INTEGER(bio, cinf->cid->serialNumber) != -1) &&
                    ((n = BIO_read(bio, snum, sizeof snum - 1)) > 0))
                    snum[n] = '\0';
                BIO_free(bio);
            }

            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02969)
                         "stapling_check_response: response has certificate "
                         "status %s (reason: %s) for serial number %s",
                         OCSP_cert_status_str(status),
                         (reason != OCSP_REVOKED_STATUS_NOSTATUS) ?
                         OCSP_crl_reason_str(reason) : "n/a",
                         snum[0] ? snum : "[n/a]");

            if (mctx->stapling_return_errors == FALSE) {
                if (pok)
                    *pok = FALSE;
                rv = SSL_TLSEXT_ERR_NOACK;
            }
        }
    }

    OCSP_BASICRESP_free(bs);

    return rv;
}