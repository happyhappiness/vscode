static const char *mod_auth_ldap_add_subgroup_class(cmd_parms *cmd, void *config, const char *arg)
{
    struct mod_auth_ldap_groupattr_entry_t *new;

    authn_ldap_config_t *sec = config;

    if (sec->subgroupclasses->nelts > GROUPATTR_MAX_ELTS)
        return "Too many AuthLDAPSubGroupClass values";

    new = apr_array_push(sec->subgroupclasses);
    new->name = apr_pstrdup(cmd->pool, arg);

    return NULL;
}