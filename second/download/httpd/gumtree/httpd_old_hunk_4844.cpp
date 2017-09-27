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
