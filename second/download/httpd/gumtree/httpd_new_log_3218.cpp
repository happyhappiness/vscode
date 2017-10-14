ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01717)
                                  "auth_ldap authorise: require group "
                                  "(sub-group): authorisation successful "
                                  "(attribute %s) [%s][%d - %s]",
                                  ent[i].name, ldc->reason, result,
                                  ldap_err2string(result));