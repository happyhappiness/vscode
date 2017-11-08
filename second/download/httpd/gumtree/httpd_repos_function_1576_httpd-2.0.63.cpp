static const char *set_charset_config(cmd_parms *cmd, void *config, const char *arg)
{
    ap_set_module_config(cmd->server->module_config, &auth_ldap_module,
                         (void *)arg);
    return NULL;
}