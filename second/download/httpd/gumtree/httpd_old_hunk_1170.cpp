        grp->name = "uniquemember";
#if APR_HAS_THREADS
        apr_thread_mutex_unlock(sec->lock);
#endif
    }

    if (!reqs_arr) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authorise: no requirements array", getpid());
        return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
    }

    /*
     * If we have been authenticated by some other module than mod_auth_ldap,
     * the req structure needed for authorization needs to be created
     * and populated with the userid and DN of the account in LDAP
     */

