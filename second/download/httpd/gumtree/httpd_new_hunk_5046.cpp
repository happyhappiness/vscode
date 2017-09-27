            return AUTHZ_GRANTED;
        }
        else { 
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01719)
                              "auth_ldap authorize: require group \"%s\": "
                              "didn't match with attr %s [%s][%d - %s]",
                              t, ent[i].name, ldc->reason, result, 
                              ldap_err2string(result));
        }
    }
    
    for (i = 0; i < sec->groupattr->nelts; i++) {
        /* nested groups need searches and compares, so grab a new handle */
