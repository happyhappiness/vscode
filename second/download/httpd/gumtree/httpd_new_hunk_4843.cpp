        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01665)
                        "Could not open group file: %s",
                        conf->groupfile);
        return AUTHZ_DENIED;
    }

    if (apr_is_empty_table(grpstatus)) {
        /* no groups available, so exit immediately */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01666)
                      "Authorization of user %s to access %s failed, reason: "
                      "user doesn't appear in group file (%s).",
                      r->user, r->uri, conf->groupfile);
        return AUTHZ_DENIED;
