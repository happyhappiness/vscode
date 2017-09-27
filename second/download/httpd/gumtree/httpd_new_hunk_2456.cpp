    }

    /* If there is no group file - then we are not
     * configured. So decline.
     */
    if (!(conf->groupfile)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01668)
                        "No group file was specified in the configuration");
        return AUTHZ_DENIED;
    }

    status = groups_for_user(r->pool, user, conf->groupfile,
                             &grpstatus);
    if (status != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01669)
                      "Could not open group file: %s",
                      conf->groupfile);
        return AUTHZ_DENIED;
    }

    if (apr_table_elts(grpstatus)->nelts == 0) {
        /* no groups available, so exit immediately */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01670)
                        "Authorization of user %s to access %s failed, reason: "
                        "user doesn't appear in group file (%s).",
                        r->user, r->uri, conf->groupfile);
        return AUTHZ_DENIED;
    }

