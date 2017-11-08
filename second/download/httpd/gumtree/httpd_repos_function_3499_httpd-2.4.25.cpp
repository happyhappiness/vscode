static const char *util_ldap_set_retries(cmd_parms *cmd,
                                         void *dummy,
                                         const char *val)
{
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                                  &ldap_module);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    st->retries = atoi(val);
    if (st->retries < 0) {
        return  "LDAPRetries must be >= 0";
    }

    return NULL;
}