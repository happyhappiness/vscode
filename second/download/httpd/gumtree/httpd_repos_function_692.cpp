static BOOL stapling_get_cached_response(server_rec *s, OCSP_RESPONSE **prsp,
                                         BOOL *pok, certinfo *cinf,
                                         apr_pool_t *pool)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;
    OCSP_RESPONSE *rsp;
    unsigned char resp_der[MAX_STAPLING_DER];
    const unsigned char *p;
    unsigned int resp_derlen = MAX_STAPLING_DER;

    rv = mc->stapling_cache->retrieve(mc->stapling_cache_context, s,
                                      cinf->idx, sizeof(cinf->idx),
                                      resp_der, &resp_derlen, pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "stapling_get_cached_response: cache miss");
        return TRUE;
    }
    if (resp_derlen <= 1) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "stapling_get_cached_response: response length invalid??");
        return TRUE;
    }
    p = resp_der;
    if (pok) {
        if (*p)
            *pok = TRUE;
        else
            *pok = FALSE;
    }
    p++;
    resp_derlen--;
    rsp = d2i_OCSP_RESPONSE(NULL, &p, resp_derlen);
    if (!rsp) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "stapling_get_cached_response: response parse error??");
        return TRUE;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "stapling_get_cached_response: cache hit");

    *prsp = rsp;

    return TRUE;
}