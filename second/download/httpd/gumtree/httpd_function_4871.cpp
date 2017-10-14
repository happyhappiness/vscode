static BOOL stapling_cache_response(server_rec *s, modssl_ctx_t *mctx,
                                    OCSP_RESPONSE *rsp, certinfo *cinf,
                                    BOOL ok, apr_pool_t *pool)
{
    SSLModConfigRec *mc = myModConfig(s);
    unsigned char resp_der[MAX_STAPLING_DER];
    unsigned char *p;
    int resp_derlen;
    BOOL rv;
    apr_time_t expiry;

    resp_derlen = i2d_OCSP_RESPONSE(rsp, NULL) + 1;

    if (resp_derlen <= 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "OCSP stapling response encode error??");
        return FALSE;
    }

    if (resp_derlen > sizeof resp_der) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "OCSP stapling response too big (%u bytes)", resp_derlen);
        return FALSE;
    }

    p = resp_der;

    /* TODO: potential optimization; _timeout members as apr_interval_time_t */
    if (ok == TRUE) {
        *p++ = 1;
        expiry = apr_time_from_sec(mctx->stapling_cache_timeout);
    } 
    else {
        *p++ = 0;
        expiry = apr_time_from_sec(mctx->stapling_errcache_timeout);
    }

    expiry += apr_time_now();

    i2d_OCSP_RESPONSE(rsp, &p);

    rv = mc->stapling_cache->store(mc->stapling_cache_context, s,
                                   cinf->idx, sizeof(cinf->idx),
                                   expiry, resp_der, resp_derlen, pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "stapling_cache_response: OCSP response session store error!");
        return FALSE;
    }

    return TRUE;
}