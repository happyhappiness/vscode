static const char *mod_auth_ldap_set_subgroup_maxdepth(cmd_parms *cmd,
                                                       void *config,
                                                       const char *max_depth)
{
    authn_ldap_config_t *sec = config;

    sec->maxNestingDepth = atol(max_depth);

    return NULL;
}