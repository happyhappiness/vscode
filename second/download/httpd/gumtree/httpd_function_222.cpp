static void cgid_child_errfn(apr_pool_t *pool, apr_status_t err,
                             const char *description)
{
    request_rec *r;
    void *vr;

    apr_pool_userdata_get(&vr, ERRFN_USERDATA_KEY, pool);
    r = vr;

    /* sure we got r, but don't call ap_log_rerror() because we don't
     * have r->headers_in and possibly other storage referenced by
     * ap_log_rerror()
     */
    ap_log_error(APLOG_MARK, APLOG_ERR, err, r->server, "%s", description);
}