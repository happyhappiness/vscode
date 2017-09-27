    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
        if (!strcmp(r->user, w)) {
            return AUTHZ_GRANTED;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01663)
                  "access to %s failed, reason: user '%s' does not meet "
                  "'require'ments for user to be allowed access",
                  r->uri, r->user);

    return AUTHZ_DENIED;
}

static authz_status validuser_check_authorization(request_rec *r,
                                                  const char *require_line,
                                                  const void *parsed_require_line)
{
    if (!r->user) {
        return AUTHZ_DENIED_NO_USER;
    }

    return AUTHZ_GRANTED;
}

static const authz_provider authz_user_provider =
{
    &user_check_authorization,
    NULL,
};
static const authz_provider authz_validuser_provider =
{
    &validuser_check_authorization,
    NULL,
};

static void register_hooks(apr_pool_t *p)
{
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "user",
                              AUTHZ_PROVIDER_VERSION,
