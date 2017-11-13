ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                   "[%" APR_PID_T_FMT "] auth_ldap authorise: require group (sub-group): "
                                   "authorisation successful (attribute %s) [%s][%d - %s]",
                                   getpid(), ent[i].name, ldc->reason, result, ldap_err2string(result));