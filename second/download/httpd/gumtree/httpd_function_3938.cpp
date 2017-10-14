static const char *util_ldap_set_verify_srv_cert(cmd_parms *cmd,
                                                 void *dummy,
                                                 int mode)
{
    util_ldap_state_t *st =
    (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                              &ldap_module);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                      "LDAP: SSL verify server certificate - %s",
                      mode?"TRUE":"FALSE");

    st->verify_svr_cert = mode;

    return(NULL);
}