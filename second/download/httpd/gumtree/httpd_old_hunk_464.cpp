                                      "authorisation failed [%s][%s]",
                                      getpid(), t, ldc->reason, ldap_err2string(result));
                    }
                }
            }
        }
    }

    if (!method_restricted) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r, 
                      "[%d] auth_ldap authorise: agreeing because non-restricted", 
                      getpid());
