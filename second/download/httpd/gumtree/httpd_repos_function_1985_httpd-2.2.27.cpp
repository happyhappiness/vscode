static int get_basic_auth(request_rec *r, const char **user,
                          const char **pw)
{
    const char *auth_line;
    char *decoded_line;
    int length;

    /* Get the appropriate header */
    auth_line = apr_table_get(r->headers_in, (PROXYREQ_PROXY == r->proxyreq)
                                              ? "Proxy-Authorization"
                                              : "Authorization");

    if (!auth_line) {
        note_basic_auth_failure(r);
        return HTTP_UNAUTHORIZED;
    }

    if (strcasecmp(ap_getword(r->pool, &auth_line, ' '), "Basic")) {
        /* Client tried to authenticate using wrong auth scheme */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "client used wrong authentication scheme: %s", r->uri);
        note_basic_auth_failure(r);
        return HTTP_UNAUTHORIZED;
    }

    /* Skip leading spaces. */
    while (apr_isspace(*auth_line)) {
        auth_line++;
    }

    decoded_line = apr_palloc(r->pool, apr_base64_decode_len(auth_line) + 1);
    length = apr_base64_decode(decoded_line, auth_line);
    /* Null-terminate the string. */
    decoded_line[length] = '\0';

    *user = ap_getword_nulls(r->pool, (const char**)&decoded_line, ':');
    *pw = decoded_line;

    /* set the user, even though the user is unauthenticated at this point */
    r->user = (char *) *user;

    return OK;
}