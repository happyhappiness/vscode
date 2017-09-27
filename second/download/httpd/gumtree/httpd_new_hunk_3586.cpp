 *
 * Deliver cached content (headers and body) up the stack.
 */
static apr_status_t cache_out_filter(ap_filter_t *f, apr_bucket_brigade *in)
{
    request_rec *r = f->r;
    cache_request_rec *cache = (cache_request_rec *)f->ctx;

    if (!cache) {
        /* user likely configured CACHE_OUT manually; they should use mod_cache
         * configuration to do that */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00762)
