#if APR_HAS_THREADS
        apr_thread_mutex_lock(sec->lock);
#endif
        grp = apr_array_push(sec->groupattr);
        grp->name = "member";
        grp = apr_array_push(sec->groupattr);
        grp->name = "uniquemember";
#if APR_HAS_THREADS
        apr_thread_mutex_unlock(sec->lock);
#endif
    }

    /*
     * If we have been authenticated by some other module than mod_auth_ldap,
     * the req structure needed for authorization needs to be created
     * and populated with the userid and DN of the account in LDAP
     */

    /* Check that we have a userid to start with */
    if ((!r->user) || (strlen(r->user) == 0)) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
            "ldap authorize: Userid is blank, AuthType=%s",
            r->ap_auth_type);
    }

    if(!req) {
