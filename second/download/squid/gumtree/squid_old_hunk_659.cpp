            if (sslpath && ((rc == LDAP_SERVER_DOWN) || (rc == LDAP_CONNECT_ERROR))) {
                int sslerr = PORT_GetError();
                fprintf(stderr, PROGRAM_NAME ": WARNING: SSL error %d (%s)\n", sslerr, ldapssl_err2string(sslerr));
            }
#endif
            ldap_msgfree(res);
            return 1;
        }
    }
    entry = ldap_first_entry(ld, res);
    if (!entry) {
        ldap_msgfree(res);
        return 1;
