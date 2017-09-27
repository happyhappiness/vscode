    }
    else {
        return 0;
    }
}

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

static authz_status ip_check_authorization(request_rec *r, const char *require_line)
{
    const char *t, *w;

    /* The 'ip' provider will allow the configuration to specify a list of
        ip addresses to check rather than a single address.  This is different
        from the previous host based syntax. */
    t = require_line;
    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
        char *where = apr_pstrdup(r->pool, w);
        char *s;
        char msgbuf[120];
        apr_ipsubnet_t *ip;
        apr_status_t rv;
        int got_ip = 0;

        if ((s = ap_strchr(where, '/'))) {
            *s++ = '\0';
            rv = apr_ipsubnet_create(&ip, where, s, r->pool);
            if(APR_STATUS_IS_EINVAL(rv)) {
                /* looked nothing like an IP address */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "an ip address 'require' list appears to be invalid ");
            }
            else if (rv != APR_SUCCESS) {
                apr_strerror(rv, msgbuf, sizeof msgbuf);
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "an ip address 'require' list appears to be invalid; %s ",
                              msgbuf);
            }
            else
                got_ip = 1;
        }
        else if (!APR_STATUS_IS_EINVAL(rv = apr_ipsubnet_create(&ip, where,
                                                                NULL, r->pool))) {
            if (rv != APR_SUCCESS) {
                apr_strerror(rv, msgbuf, sizeof msgbuf);
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "an ip address 'require' list appears to be invalid; %s ",
                              msgbuf);
            }
            else 
                got_ip = 1;
        }

        if (got_ip && apr_ipsubnet_test(ip, r->connection->remote_addr)) {
            return AUTHZ_GRANTED;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "access to %s failed, reason: ip address list does not meet "
                  "'require'ments for user '%s' to be allowed access",
                  r->uri, r->user);

    return AUTHZ_DENIED;
}

static authz_status host_check_authorization(request_rec *r, const char *require_line)
{
    const char *t, *w;
    const char *remotehost = NULL;
    int remotehost_is_ip;

    remotehost = ap_get_remote_host(r->connection,
                                    r->per_dir_config,
                                    REMOTE_DOUBLE_REV,
                                    &remotehost_is_ip);

    if ((remotehost == NULL) || remotehost_is_ip) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "access to %s failed, reason: unable to get the "
                      "remote host name", r->uri);
    }
    else {
        /* The 'host' provider will allow the configuration to specify a list of
            host names to check rather than a single name.  This is different
            from the previous host based syntax. */
        t = require_line;
        while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
            if (in_domain(w, remotehost)) {
                return AUTHZ_GRANTED;
            }
        }

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "access to %s failed, reason: host name list does not meet "
                      "'require'ments for user '%s' to be allowed access",
                      r->uri, r->user);
    }

    return AUTHZ_DENIED;
}

static authz_status all_check_authorization(request_rec *r, const char *require_line)
{
    /* If the argument to the 'all' provider is 'granted' then just let 
        everybody in. This would be equivalent to the previous syntax of
        'allow from all'. If the argument is anything else, this would
        be equivalent to 'deny from all' Of course the opposite would be 
        true if the 'all' provider is invoked by the 'reject' directive */
    if (strcasecmp(require_line, "granted") == 0) {
        return AUTHZ_GRANTED;
    }
    return AUTHZ_DENIED;
}

static const authz_provider authz_env_provider =
{
    &env_check_authorization,
};

static const authz_provider authz_ip_provider =
{
    &ip_check_authorization,
};

static const authz_provider authz_host_provider =
{
    &host_check_authorization,
};

static const authz_provider authz_all_provider =
{
    &all_check_authorization,
};

static void register_hooks(apr_pool_t *p)
{
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "env",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_env_provider, AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "ip",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_ip_provider, AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "host",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_host_provider, AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "all",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_all_provider, AP_AUTH_INTERNAL_PER_CONF);
}

AP_DECLARE_MODULE(authz_host) =
{
    STANDARD20_MODULE_STUFF,
    create_authz_host_dir_config,   /* dir config creater */
    NULL,                           /* dir merger --- default is to override */
    NULL,                           /* server config */
    NULL,                           /* merge server config */
    authz_host_cmds,
    register_hooks                  /* register hooks */
};
