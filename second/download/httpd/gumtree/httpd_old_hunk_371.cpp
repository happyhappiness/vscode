                     "LDAP: SSL connections (ldaps://) not supported by utilLDAP");
            return(!OK);
        }
    }
    */

    if (!charset_confname) {
        return OK;
    }

    charset_confname = ap_server_root_relative(p, charset_confname);
    if (!charset_confname) {
