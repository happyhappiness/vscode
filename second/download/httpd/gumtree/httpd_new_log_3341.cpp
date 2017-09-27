ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01745)
                              "auth_ldap authorize: require ldap-filter: "
                              "authorization successful");
                set_request_vars(r, LDAP_AUTHZ);
                return AUTHZ_GRANTED;;