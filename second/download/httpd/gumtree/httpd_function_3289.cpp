static authz_status env_check_authorization(request_rec *r, const char *require_line)
{
    const char *t, *w;

    /* The 'env' provider will allow the configuration to specify a list of
        env variables to check rather than a single variable.  This is different
        from the previous host based syntax. */
    t = require_line;
    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
        if (apr_table_get(r->subprocess_env, w)) {
            return AUTHZ_GRANTED;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "access to %s failed, reason: env variable list does not meet "
                  "'require'ments for user '%s' to be allowed access",
                  r->uri, r->user);

    return AUTHZ_DENIED;
}