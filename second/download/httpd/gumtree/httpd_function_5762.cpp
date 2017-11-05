static authz_status
forward_dns_check_authorization(request_rec *r,
                                const char *require_line,
                                const void *parsed_require_line)
{
    const char *err = NULL;
    const ap_expr_info_t *expr = parsed_require_line;
    const char *require, *t;
    char *w;

    /* the require line is an expression, which is evaluated now. */
    require = ap_expr_str_exec(r, expr, &err);
    if (err) {
      ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(03354)
                    "Can't evaluate require expression: %s", err);
      return AUTHZ_DENIED;
    }

    /* tokenize expected list of names */
    t = require;
    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {

        apr_sockaddr_t *sa;
        apr_status_t rv;
        char *hash_ptr;

        /* stop on apache configuration file comments */
        if ((hash_ptr = ap_strchr(w, '#'))) {
            if (hash_ptr == w) {
                break;
            }
            *hash_ptr = '\0';
        }

        /* does the client ip match one of the names? */
        rv = apr_sockaddr_info_get(&sa, w, APR_UNSPEC, 0, 0, r->pool);
        if (rv == APR_SUCCESS) {

            while (sa) {
                int match = apr_sockaddr_equal(sa, r->useragent_addr);

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03355)
                              "access check for %s as '%s': %s",
                              r->useragent_ip, w, match? "yes": "no");
                if (match) {
                    return AUTHZ_GRANTED;
                }

                sa = sa->next;
            }
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(03356)
                          "No sockaddr info for \"%s\"", w);
        }

        /* stop processing, we are in a comment */
        if (hash_ptr) {
            break;
        }
    }

    return AUTHZ_DENIED;
}