static const char *set_authtype(cmd_parms *cmd, void *mconfig,
                                const char *word1)
{
    authn_core_dir_conf *aconfig = (authn_core_dir_conf *)mconfig;

    aconfig->auth_type_set = 1;
    aconfig->ap_auth_type = strcasecmp(word1, "None") ? word1 : NULL;

    return NULL;
}