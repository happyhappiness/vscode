static int cache_save_store(ap_filter_t *f, apr_bucket_brigade *in,
        cache_server_conf *conf, cache_request_rec *cache)
{
    int rv = APR_SUCCESS;
    apr_bucket *e;

    /* pass the brigade in into the cache provider, which is then
     * expected to move cached buckets to the out brigade, for us
     * to pass up the filter stack. repeat until in is empty, or
     * we fail.
     */
    while (APR_SUCCESS == rv && !APR_BRIGADE_EMPTY(in)) {

        rv = cache->provider->store_body(cache->handle, f->r, in, cache->out);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, f->r, APLOGNO(00765)
                    "cache: Cache provider's store_body failed!");
            ap_remove_output_filter(f);

            /* give someone else the chance to cache the file */
            cache_remove_lock(conf, cache, f->r, NULL);

            /* give up trying to cache, just step out the way */
            APR_BRIGADE_PREPEND(in, cache->out);
            return ap_pass_brigade(f->next, in);

        }

        /* does the out brigade contain eos? if so, we're done, commit! */
        for (e = APR_BRIGADE_FIRST(cache->out);
             e != APR_BRIGADE_SENTINEL(cache->out);
             e = APR_BUCKET_NEXT(e))
        {
            if (APR_BUCKET_IS_EOS(e)) {
                rv = cache->provider->commit_entity(cache->handle, f->r);
                break;
            }
        }

        /* conditionally remove the lock as soon as we see the eos bucket */
        cache_remove_lock(conf, cache, f->r, cache->out);

        if (APR_BRIGADE_EMPTY(cache->out)) {
            if (APR_BRIGADE_EMPTY(in)) {
                /* cache provider wants more data before passing the brigade
                 * upstream, oblige the provider by leaving to fetch more.
                 */
                break;
            }
            else {
                /* oops, no data out, but not all data read in either, be
                 * safe and stand down to prevent a spin.
                 */
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, f->r, APLOGNO(00766)
                        "cache: Cache provider's store_body returned an "
                        "empty brigade, but didn't consume all of the "
                        "input brigade, standing down to prevent a spin");
                ap_remove_output_filter(f);

                /* give someone else the chance to cache the file */
                cache_remove_lock(conf, cache, f->r, NULL);

                return ap_pass_brigade(f->next, in);
            }
        }

        rv = ap_pass_brigade(f->next, cache->out);
    }

    return rv;
}