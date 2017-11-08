static const char *set_bind_pattern(cmd_parms *cmd, void *_cfg, const char *exp, const char *subst)
{
    authn_ldap_config_t *sec = _cfg;
    ap_regex_t *regexp;

    regexp = ap_pregcomp(cmd->pool, exp, AP_REG_EXTENDED);

    if (!regexp) {
        return apr_pstrcat(cmd->pool, "AuthLDAPInitialBindPattern: cannot compile regular "
                                      "expression '", exp, "'", NULL);
    }

    sec->bind_regex = regexp;
    sec->bind_subst = apr_pstrdup(cmd->pool, subst);

    return NULL;
}