static const char *util_ldap_set_retry_delay(cmd_parms *cmd,
                                            void *dummy,
                                            const char *val)
{
    apr_interval_time_t timeout;
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                                  &ldap_module);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    if (ap_timeout_parameter_parse(val, &timeout, "s") != APR_SUCCESS) {
        return "LDAPRetryDelay has wrong format";
    }

    if (timeout < 0) {
        return "LDAPRetryDelay must be >= 0";
    }

    st->retry_delay = timeout;
    return NULL;
}