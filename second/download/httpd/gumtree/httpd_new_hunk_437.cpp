    ap_table_setn(r->err_headers_out,

	    r->proxyreq ? "Proxy-Authenticate" : "WWW-Authenticate",

	    ap_psprintf(r->pool, "Digest realm=\"%s\", nonce=\"%lu\"",

		ap_auth_name(r), r->request_time));

}



API_EXPORT(int) ap_get_basic_auth_pw(request_rec *r, const char **pw)

{

    const char *auth_line = ap_table_get(r->headers_in,

                                      r->proxyreq ? "Proxy-Authorization"

                                                  : "Authorization");

    const char *t;



    if (!(t = ap_auth_type(r)) || strcasecmp(t, "Basic"))

        return DECLINED;



    if (!ap_auth_name(r)) {

        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR,

