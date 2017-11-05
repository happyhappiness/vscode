static const char *util_ldap_set_certdbpath(cmd_parms *cmd, void *dummy, const char *path)
{
    util_ldap_state_t *st = 
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config, 
						  &ldap_module);

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                      "[%d] ldap cache: Setting LDAP SSL client certificate dbpath to %s.", 
                      getpid(), path);

    st->have_certdb = 1;
    if (ldapssl_client_init(path, NULL) != 0) {
        return "Could not initialize SSL client";
    }
    else {
        return NULL;
    }
}