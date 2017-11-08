static const char *ldap_determine_binddn(request_rec *r, const char *user) {
    authn_ldap_config_t *sec =
        (authn_ldap_config_t *)ap_get_module_config(r->per_dir_config, &authnz_ldap_module);
    const char *result = user;
    ap_regmatch_t regm[AP_MAX_REG_MATCH];

    if (NULL == user || NULL == sec || !sec->bind_regex || !sec->bind_subst) {
        return result;
    }

    if (!ap_regexec(sec->bind_regex, user, AP_MAX_REG_MATCH, regm, 0)) {
        char *substituted = ap_pregsub(r->pool, sec->bind_subst, user, AP_MAX_REG_MATCH, regm);
        if (NULL != substituted) {
            result = substituted;
        }
    }

    apr_table_set(r->subprocess_env, "LDAP_BINDASUSER", result);

    return result;
}