
        ap_set_module_config(r->request_config, &authnz_ldap_module, req);
        req->dn = apr_pstrdup(r->pool, dn);
        req->user = r->user;
    }

    t = require_args;

    if (req->dn == NULL || strlen(req->dn) == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01725)
                      "auth_ldap authorize: require dn: user's DN has not "
                      "been defined; failing authorization");
        return AUTHZ_DENIED;
