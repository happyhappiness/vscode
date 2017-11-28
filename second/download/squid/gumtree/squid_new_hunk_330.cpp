                        break;
                    }
                } else {
                    password = *value;
                    break;
                }
                ++value;
            }
            debug("password: %s\n", password);
            if (password)
                password = xstrdup(password);
            ldap_value_free(values);
            ldap_msgfree(res);
            return password;
        } else {
            fprintf(stderr, PROGRAM_NAME " WARNING, LDAP error '%s'\n", ldap_err2string(rc));
            /* try to connect to the LDAP server agin, maybe my persisten conexion failed. */
            if (!retry) {
                ++retry;
                ldap_unbind(ld);
                ld = NULL;
                ldapconnect();
                goto retrydnattr;
            }
            return NULL;
