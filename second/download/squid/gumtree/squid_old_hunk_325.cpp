                    }
#endif
                    fprintf(stderr, PROGRAM_NAME " WARNING, LDAP search error, trying to recover'%s'\n", ldap_err2string(rc));
                    ldap_msgfree(res);
                    /* try to connect to the LDAP server agin, maybe my persisten conexion failed. */
                    if (!retry) {
                        retry++;
                        ldap_unbind(ld);
                        ld = NULL;
                        ldapconnect();
                        goto retrysrch;
                    }
                    return NULL;
