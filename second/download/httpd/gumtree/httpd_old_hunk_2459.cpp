    {NULL}
};

module AP_MODULE_DECLARE_DATA authz_owner_module;

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
