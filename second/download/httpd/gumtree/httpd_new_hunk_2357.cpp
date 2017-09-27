 * Support for the Basic authentication protocol, and a bit for Digest.
 */
AP_DECLARE(void) ap_note_auth_failure(request_rec *r)
{
    const char *type = ap_auth_type(r);
    if (type) {
        ap_run_note_auth_failure(r, type);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR,
                      0, r, "need AuthType to note auth failure: %s", r->uri);
    }
}

AP_DECLARE(void) ap_note_basic_auth_failure(request_rec *r)
{
    ap_note_auth_failure(r);
}

AP_DECLARE(void) ap_note_digest_auth_failure(request_rec *r)
{
    ap_note_auth_failure(r);
}

AP_DECLARE(int) ap_get_basic_auth_pw(request_rec *r, const char **pw)
{
    const char *auth_line = apr_table_get(r->headers_in,
                                          (PROXYREQ_PROXY == r->proxyreq)
