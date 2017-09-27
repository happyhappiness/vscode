 */
static BOOL stapling_cache_response(server_rec *s, modssl_ctx_t *mctx,
                                    OCSP_RESPONSE *rsp, certinfo *cinf,
                                    BOOL ok, apr_pool_t *pool)
{
    SSLModConfigRec *mc = myModConfig(s);
    unsigned char resp_der[MAX_STAPLING_DER]; /* includes one-byte flag + response */
    unsigned char *p;
    int resp_derlen, stored_len;
    BOOL rv;
    apr_time_t expiry;

    resp_derlen = i2d_OCSP_RESPONSE(rsp, NULL);

    if (resp_derlen <= 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01927)
                     "OCSP stapling response encode error??");
        return FALSE;
    }

    stored_len = resp_derlen + 1; /* response + ok flag */
    if (stored_len > sizeof resp_der) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01928)
                     "OCSP stapling response too big (%u bytes)", resp_derlen);
        return FALSE;
    }

    p = resp_der;
