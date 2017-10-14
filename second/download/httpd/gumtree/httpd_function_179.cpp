const char *util_ldap_set_cert_type(cmd_parms *cmd, void *dummy, const char *Type)
{
    util_ldap_state_t *st = 
    (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config, 
                                              &ldap_module);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                      "LDAP: SSL trusted certificate authority file type - %s", 
                       Type);

    if (0 == strcmp("DER_FILE", Type))
        st->cert_file_type = LDAP_CA_TYPE_DER;

    else if (0 == strcmp("BASE64_FILE", Type))
        st->cert_file_type = LDAP_CA_TYPE_BASE64;

    else if (0 == strcmp("CERT7_DB_PATH", Type))
        st->cert_file_type = LDAP_CA_TYPE_CERT7_DB;

    else
        st->cert_file_type = LDAP_CA_TYPE_UNKNOWN;

    return(NULL);
}