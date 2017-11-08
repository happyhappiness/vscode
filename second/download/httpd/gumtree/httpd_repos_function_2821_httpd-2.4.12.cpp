static const char *set_authname(cmd_parms *cmd, void *mconfig,
                                const char *word1)
{
    authn_core_dir_conf *aconfig = (authn_core_dir_conf *)mconfig;

    aconfig->ap_auth_name = ap_escape_quotes(cmd->pool, word1);
    return NULL;
}