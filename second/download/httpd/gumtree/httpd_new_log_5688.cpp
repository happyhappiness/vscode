ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, 
                              "ldap_compare_s(%pp, %s, %s, %s) = %s (cached)", 
                              ldc->ldap, dn, attrib, value, ldap_err2string(result));