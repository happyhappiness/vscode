ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01718)
                          "auth_ldap authorise: require group "
                          "(sub-group) \"%s\": didn't match with attr %s "
                          "[%s][%d - %s]",
                          t, ldc->reason, ent[i].name, result, 
                          ldap_err2string(result));