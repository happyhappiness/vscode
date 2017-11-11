static const char *util_ldap_set_debug_level(cmd_parms *cmd,
                                             void *config,
                                             const char *arg) { 
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                                  &ldap_module);

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

#ifndef AP_LDAP_OPT_DEBUG
    return "This directive is not supported with the currently linked LDAP library";
#endif

    st->debug_level = atoi(arg);
    return NULL;
}