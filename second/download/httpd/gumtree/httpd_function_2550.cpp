static authz_status fileowner_check_authorization(request_rec *r,
                                             const char *require_args)
{
    char *reason = NULL;
    apr_status_t status = 0;

#if !APR_HAS_USER
    reason = "'Require file-owner' is not supported on this platform.";
    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                  "Authorization of user %s to access %s failed, reason: %s",
                  r->user, r->uri, reason ? reason : "unknown");
    return AUTHZ_DENIED;
#else  /* APR_HAS_USER */
    char *owner = NULL;
    apr_finfo_t finfo;

    if (!r->user) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "access to %s failed, reason: no authenticated user", r->uri);
        return AUTHZ_DENIED;
    }

    if (!r->filename) {
        reason = "no filename available";
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Authorization of user %s to access %s failed, reason: %s",
                      r->user, r->uri, reason ? reason : "unknown");
        return AUTHZ_DENIED;
    }

    status = apr_stat(&finfo, r->filename, APR_FINFO_USER, r->pool);
    if (status != APR_SUCCESS) {
        reason = apr_pstrcat(r->pool, "could not stat file ",
                                r->filename, NULL);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Authorization of user %s to access %s failed, reason: %s",
                      r->user, r->uri, reason ? reason : "unknown");
        return AUTHZ_DENIED;
    }

    if (!(finfo.valid & APR_FINFO_USER)) {
        reason = "no file owner information available";
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Authorization of user %s to access %s failed, reason: %s",
                      r->user, r->uri, reason ? reason : "unknown");
        return AUTHZ_DENIED;
    }

    status = apr_uid_name_get(&owner, finfo.user, r->pool);
    if (status != APR_SUCCESS || !owner) {
        reason = "could not get name of file owner";
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Authorization of user %s to access %s failed, reason: %s",
                      r->user, r->uri, reason ? reason : "unknown");
        return AUTHZ_DENIED;
    }

    if (strcmp(owner, r->user)) {
        reason = apr_psprintf(r->pool, "file owner %s does not match.",
                                owner);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Authorization of user %s to access %s failed, reason: %s",
                      r->user, r->uri, reason ? reason : "unknown");
        return AUTHZ_DENIED;
    }

    /* this user is authorized */
    return AUTHZ_GRANTED;
#endif /* APR_HAS_USER */
}