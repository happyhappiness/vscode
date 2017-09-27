        }
    }
    else {
        return "Certificate type was not specified.";
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01303)
                      "LDAP: SSL trusted global cert - %s (type %s)",
                       file, type);

    /* add the certificate to the global array */
    cert = (apr_ldap_opt_tls_cert_t *)apr_array_push(st->global_certs);
    cert->type = cert_type;
