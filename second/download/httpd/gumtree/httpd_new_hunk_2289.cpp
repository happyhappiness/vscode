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
