
static apr_status_t ef_close_file(void *vfile)
{
    return apr_file_close(vfile);
}

static void child_errfn(apr_pool_t *p, apr_status_t err, const char *desc)
{
    request_rec *r;
    void *vr;

    apr_pool_userdata_get(&vr, ERRFN_USERDATA_KEY, p);
    r = vr;
    
    ap_log_rerror(APLOG_MARK, APLOG_ERR, err, r, "%s", desc);
}

/* init_ext_filter_process: get the external filter process going
 * This is per-filter-instance (i.e., per-request) initialization.
 */
static apr_status_t init_ext_filter_process(ap_filter_t *f)
{
    ef_ctx_t *ctx = f->ctx;
