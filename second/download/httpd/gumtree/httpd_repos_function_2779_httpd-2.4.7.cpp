static const char *mod_auth_ldap_set_deref(cmd_parms *cmd, void *config, const char *arg)
{
    authn_ldap_config_t *sec = config;

    if (strcmp(arg, "never") == 0 || strcasecmp(arg, "off") == 0) {
        sec->deref = never;
    }
    else if (strcmp(arg, "searching") == 0) {
        sec->deref = searching;
    }
    else if (strcmp(arg, "finding") == 0) {
        sec->deref = finding;
    }
    else if (strcmp(arg, "always") == 0 || strcasecmp(arg, "on") == 0) {
        sec->deref = always;
    }
    else {
        return "Unrecognized value for AuthLDAPDereferenceAliases directive";
    }
    return NULL;
}