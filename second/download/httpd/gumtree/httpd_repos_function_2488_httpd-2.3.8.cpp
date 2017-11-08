static const char *mod_auth_ldap_add_subgroup_attribute(cmd_parms *cmd, void *config, const char *arg)
{
    int i = 0;

    authn_ldap_config_t *sec = config;

    for (i = 0; sec->sgAttributes[i]; i++) {
        ;
    }
    if (i == GROUPATTR_MAX_ELTS)
        return "Too many AuthLDAPSubGroupAttribute values";

    sec->sgAttributes[i] = apr_pstrdup(cmd->pool, arg);

    return NULL;
}