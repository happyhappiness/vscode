                                    ldapServer, port);
                            exit(1);
                        }
                    } else
#endif
                        if ((ld = ldap_init(ldapServer, port)) == NULL) {
                            broken = HLP_MSG("Unable to connect to LDAP server");
                            fprintf(stderr, "ERROR: %s:%s port:%d\n", broken, ldapServer, port);
                            break;
                        }
                if (connect_timeout)
                    squid_ldap_set_connect_timeout(ld, connect_timeout);

#ifdef LDAP_VERSION3
                if (version == -1) {
                    version = LDAP_VERSION3;
                }
                if (ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version) != LDAP_SUCCESS) {
                    broken = HLP_MSG("Could not set LDAP_OPT_PROTOCOL_VERSION");
                    fprintf(stderr, "ERROR: %s %d\n", broken, version);
                    ldap_unbind(ld);
                    ld = NULL;
                    break;
                }
                if (use_tls) {
#ifdef LDAP_OPT_X_TLS
                    if (version != LDAP_VERSION3) {
                        fprintf(stderr, "FATAL: TLS requires LDAP version 3\n");
                        exit(1);
                    } else if (ldap_start_tls_s(ld, NULL, NULL) != LDAP_SUCCESS) {
                        broken = HLP_MSG("Could not Activate TLS connection");
                        fprintf(stderr, "ERROR: %s\n", broken);
                        ldap_unbind(ld);
                        ld = NULL;
                        break;
                    }
#else
                    fprintf(stderr, "FATAL: TLS not supported with your LDAP library\n");
