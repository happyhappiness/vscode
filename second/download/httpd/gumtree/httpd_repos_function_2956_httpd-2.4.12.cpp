static const char *fcgi_define_provider(cmd_parms *cmd,
                                        void *d,
                                        int argc,
                                        char *const argv[])
{
    const char *dname = "AuthnzFcgiDefineProvider";
    ap_rxplus_t *fcgi_backend_regex;
    apr_status_t rv;
    char *host;
    const char *err, *stype;
    fcgi_provider_conf *conf = apr_pcalloc(cmd->pool, sizeof(*conf));
    int ca = 0, rc;

    fcgi_backend_regex = ap_rxplus_compile(cmd->pool, FCGI_BACKEND_REGEX_STR);
    if (!fcgi_backend_regex) {
        return apr_psprintf(cmd->pool,
                            "%s: failed to compile regexec '%s'",
                            dname, FCGI_BACKEND_REGEX_STR);
    }

    err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err)
        return err;

    if (ca >= argc) {
        return apr_pstrcat(cmd->pool, dname, ": No type given", NULL);
    }

    stype = argv[ca];
    ca++;

    if (!strcasecmp(stype, "authn")) {
        conf->is_authn = 1;
    }
    else if (!strcasecmp(stype, "authz")) {
        conf->is_authz = 1;
    }
    else if (!strcasecmp(stype, "authnz")) {
        conf->is_authn = conf->is_authz = 1;
    }
    else {
        return apr_pstrcat(cmd->pool,
                           dname,
                           ": Invalid provider type ",
                           stype,
                           NULL);
    }

    if (ca >= argc) {
        return apr_pstrcat(cmd->pool, dname, ": No provider name given", NULL);
    }
    conf->name = argv[ca];
    ca++;

    if (ca >= argc) {
        return apr_pstrcat(cmd->pool, dname, ": No backend-address given",
                           NULL);
    }

    rc = ap_rxplus_exec(cmd->pool, fcgi_backend_regex, argv[ca], NULL);
    if (!rc || ap_rxplus_nmatch(fcgi_backend_regex) != 3) {
        return apr_pstrcat(cmd->pool,
                           dname, ": backend-address '",
                           argv[ca],
                           "' has invalid form",
                           NULL);
    }

    host = ap_rxplus_pmatch(cmd->pool, fcgi_backend_regex, 1);
    if (host[0] == '[' && host[strlen(host) - 1] == ']') {
        host += 1;
        host[strlen(host) - 1] = '\0';
    }

    conf->port = atoi(ap_rxplus_pmatch(cmd->pool, fcgi_backend_regex, 2));
    if (conf->port > 65535) {
        return apr_pstrcat(cmd->pool,
                           dname, ": backend-address '",
                           argv[ca],
                           "' has invalid port",
                           NULL);
    }

    conf->backend = argv[ca];
    conf->host = host;
    ca++;

    rv = apr_sockaddr_info_get(&conf->backend_addrs, conf->host,
                               APR_UNSPEC, conf->port, 0, cmd->pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, rv, NULL,
                     APLOGNO(02530) "Address %s could not be resolved",
                     conf->backend);
        return apr_pstrcat(cmd->pool,
                           dname,
                           ": Error resolving backend address",
                           NULL);
    }

    if (ca != argc) {
        return apr_pstrcat(cmd->pool,
                           dname,
                           ": Unexpected parameter ",
                           argv[ca],
                           NULL);
    }

    if (conf->is_authn) {
        apr_hash_set(fcgi_authn_providers, conf->name, APR_HASH_KEY_STRING,
                     conf);
        ap_register_auth_provider(cmd->pool, AUTHN_PROVIDER_GROUP,
                                  conf->name,
                                  AUTHN_PROVIDER_VERSION,
                                  &fcgi_authn_provider,
                                  AP_AUTH_INTERNAL_PER_CONF);
    }

    if (conf->is_authz) {
        apr_hash_set(fcgi_authz_providers, conf->name, APR_HASH_KEY_STRING,
                     conf);
        ap_register_auth_provider(cmd->pool, AUTHZ_PROVIDER_GROUP,
                                  conf->name,
                                  AUTHZ_PROV