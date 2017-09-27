    char *group = NULL;
    apr_finfo_t finfo;
    apr_status_t status = 0;

    if (!r->filename) {
        reason = "no filename available";
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01638)
                      "Authorization of user %s to access %s failed, reason: %s",
                      r->user, r->uri, reason ? reason : "unknown");
        return NULL;
    }

    status = apr_stat(&finfo, r->filename, APR_FINFO_GROUP, r->pool);
    if (status != APR_SUCCESS) {
        reason = apr_pstrcat(r->pool, "could not stat file ",
                                r->filename, NULL);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01639)
                      "Authorization of user %s to access %s failed, reason: %s",
                      r->user, r->uri, reason ? reason : "unknown");
        return NULL;
    }

    if (!(finfo.valid & APR_FINFO_GROUP)) {
        reason = "no file group information available";
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01640)
                      "Authorization of user %s to access %s failed, reason: %s",
                      r->user, r->uri, reason ? reason : "unknown");
        return NULL;
    }

    status = apr_gid_name_get(&group, finfo.group, r->pool);
    if (status != APR_SUCCESS || !group) {
        reason = "could not get name of file group";
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01641)
                      "Authorization of user %s to access %s failed, reason: %s",
                      r->user, r->uri, reason ? reason : "unknown");
        return NULL;
    }

    return group;
#endif /* APR_HAS_USER */
}

static const authz_provider authz_fileowner_provider =
{
    &fileowner_check_authorization,
    NULL,
};

static void register_hooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(authz_owner_get_file_group);

