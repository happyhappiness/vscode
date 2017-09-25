
static apr_status_t ef_close_file(void *vfile)
{
    return apr_file_close(vfile);
}

/* init_ext_filter_process: get the external filter process going
 * This is per-filter-instance (i.e., per-request) initialization.
 */
static apr_status_t init_ext_filter_process(ap_filter_t *f)
{
    ef_ctx_t *ctx = f->ctx;
