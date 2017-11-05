static const char *util_ldap_set_trusted_global_cert(cmd_parms *cmd,
                                                     void *dummy,
                                                     const char *type,
                                                     const char *file,
                                                     const char *password)
{
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                                  &ldap_module);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    apr_finfo_t finfo;
    apr_status_t rv;
    int cert_type = 0;
    apr_ldap_opt_tls_cert_t *cert;

    if (err != NULL) {
        return err;
    }

    /* handle the certificate type */
    if (type) {
        cert_type = util_ldap_parse_cert_type(type);
        if (APR_LDAP_CA_TYPE_UNKNOWN == cert_type) {
           return apr_psprintf(cmd->pool, "The certificate type %s is "
                                          "not recognised. It should be one "
                                          "of CA_DER, CA_BASE64, CA_CERT7_DB, "
                                          "CA_SECMOD, CERT_DER, CERT_BASE64, "
                                          "CERT_KEY3_DB, CERT_NICKNAME, "
                                          "KEY_DER, KEY_BASE64", type);
        }
    }
    else {
        return "Certificate type was not specified.";
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                      "LDAP: SSL trusted global cert - %s (type %s)",
                       file, type);

    /* add the certificate to the global array */
    cert = (apr_ldap_opt_tls_cert_t *)apr_array_push(st->global_certs);
    cert->type = cert_type;
    cert->path = file;
    cert->password = password;

    /* if file is a file or path, fix the path */
    if (cert_type != APR_LDAP_CA_TYPE_UNKNOWN &&
        cert_type != APR_LDAP_CERT_TYPE_NICKNAME) {

        cert->path = ap_server_root_relative(cmd->pool, file);
        if (cert->path &&
            ((rv = apr_stat (&finfo, cert->path, APR_FINFO_MIN, cmd->pool))
                != APR_SUCCESS))
        {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cmd->server,
                         "LDAP: Could not open SSL trusted certificate "
                         "authority file - %s",
                         cert->path == NULL ? file : cert->path);
            return "Invalid global certificate file path";
        }
    }

    return(NULL);
}