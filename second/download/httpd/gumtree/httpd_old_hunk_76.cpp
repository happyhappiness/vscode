 * Otherwise
 *   replace ourselves with cache_in filter
 */

static int cache_conditional_filter(ap_filter_t *f, apr_bucket_brigade *in)
{
    ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, f->r->server,
                 "cache: running CACHE_CONDITIONAL filter");

    if (f->r->status == HTTP_NOT_MODIFIED) {
        /* replace ourselves with CACHE_OUT filter */
        ap_add_output_filter("CACHE_OUT", NULL, f->r, f->r->connection);
    }
