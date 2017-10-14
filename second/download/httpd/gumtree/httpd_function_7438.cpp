static authz_status user_check_authorization(request_rec *r,
                                             const char *require_args,
                                             const void *parsed_require_args)
{
    const char *err = NULL;
    const ap_expr_info_t *expr = parsed_require_args;
    const char *require;

    const char *t, *w;

    if (!r->user) {
        return AUTHZ_DENIED_NO_USER;
    }

    require = ap_expr_str_exec(r, expr, &err);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02594)
                      "authz_user authorize: require user: Can't "
                      "evaluate require expression: %s", err);
        return AUTHZ_DENIED;
    }

    t = require;
    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
        if (!strcmp(r->user, w)) {
            return AUTHZ_GRANTED;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01663)
                  "access to %s failed, reason: user '%s' does not meet "
                  "'require'ments for user to be allowed access",
                  r->uri, r->user);

    return AUTHZ_DENIED;
}