
    if (!user) {
        return AUTHZ_DENIED_NO_USER;
    }

    if (!conf->grpfile) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "No group file was specified in the configuration");
        return AUTHZ_DENIED;
    }

    /* fetch group data from dbm file only once. */
    if (!orig_groups) {
        apr_status_t status;

        status = get_dbm_grp(r, apr_pstrcat(r->pool, user, ":", realm, NULL),
                             user, conf->grpfile, conf->dbmtype, &groups);

        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                          "could not open dbm (type %s) group access "
                          "file: %s", conf->dbmtype, conf->grpfile);
            return AUTHZ_GENERAL_ERROR;
        }

        if (groups == NULL) {
            /* no groups available, so exit immediately */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Authorization of user %s to access %s failed, reason: "
                          "user doesn't appear in DBM group file (%s).", 
                          r->user, r->uri, conf->grpfile);
            return AUTHZ_DENIED;
        }

        orig_groups = groups;
    }
