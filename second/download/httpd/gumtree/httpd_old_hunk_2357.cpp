 * Support for the Basic authentication protocol, and a bit for Digest.
 */
AP_DECLARE(void) ap_note_auth_failure(request_rec *r)
{
    const char *type = ap_auth_type(r);
    if (type) {
        if (!strcasecmp(type, "Basic"))
            ap_note_basic_auth_failure(r);
        else if (!strcasecmp(type, "Digest"))
            ap_note_digest_auth_failure(r);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR,
                      0, r, "need AuthType to note auth failure: %s", r->uri);
    }
}

AP_DECLARE(void) ap_note_basic_auth_failure(request_rec *r)
{
    const char *type = ap_auth_type(r);

    /* if there is no AuthType configure or it is something other than
     * Basic, let ap_note_auth_failure() deal with it
     */
    if (!type || strcasecmp(type, "Basic"))
        ap_note_auth_failure(r);
    else
        apr_table_setn(r->err_headers_out,
                       (PROXYREQ_PROXY == r->proxyreq) ? "Proxy-Authenticate"
                                                       : "WWW-Authenticate",
                       apr_pstrcat(r->pool, "Basic realm=\"", ap_auth_name(r),
                                   "\"", NULL));
}

AP_DECLARE(void) ap_note_digest_auth_failure(request_rec *r)
{
    apr_table_setn(r->err_headers_out,
                   (PROXYREQ_PROXY == r->proxyreq) ? "Proxy-Authenticate"
                                                   : "WWW-Authenticate",
                   apr_psprintf(r->pool, "Digest realm=\"%s\", nonce=\""
                                "%" APR_UINT64_T_HEX_FMT "\"",
                                ap_auth_name(r), (apr_uint64_t)r->request_time));
}

AP_DECLARE(int) ap_get_basic_auth_pw(request_rec *r, const char **pw)
{
    const char *auth_line = apr_table_get(r->headers_in,
                                          (PROXYREQ_PROXY == r->proxyreq)
