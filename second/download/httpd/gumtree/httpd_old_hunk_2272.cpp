
    ent = (struct mod_auth_ldap_groupattr_entry_t *) sec->groupattr->elts;

    if (sec->group_attrib_is_dn) {
        if (req->dn == NULL || strlen(req->dn) == 0) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "[%" APR_PID_T_FMT "] auth_ldap authorize: require group: "
                          "user's DN has not been defined; failing authorization for user %s",
                          getpid(), r->user);
            return AUTHZ_DENIED;
        }
    }
    else {
        if (req->user == NULL || strlen(req->user) == 0) {
            /* We weren't called in the authentication phase, so we didn't have a
