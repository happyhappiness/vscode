 */
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
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01927)
                     "OCSP stapling response encode error??");
        return FALSE;
    }

    if (resp_derlen > sizeof resp_der) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01928)
                     "OCSP stapling response too big (%u bytes)", resp_derlen);
        return FALSE;
    }

    p = resp_der;
