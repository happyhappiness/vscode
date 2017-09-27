 *
 * After the various failure cases, the cache lock is proactively removed, so
 * that another request is given the opportunity to attempt to cache without
 * waiting for a potentially slow client to acknowledge the failure.
 */

static int cache_save_filter(ap_filter_t *f, apr_bucket_brigade *in)
{
    int rv = !OK;
    request_rec *r = f->r;
    cache_request_rec *cache;
    cache_server_conf *conf;
    const char *cc_out, *cl;
    const char *exps, *lastmods, *dates, *etag;
    apr_time_t exp, date, lastmod, now;
    apr_off_t size = -1;
    cache_info *info = NULL;
    char *reason;
    apr_pool_t *p;
    apr_bucket *e;

    conf = (cache_server_conf *) ap_get_module_config(r->server->module_config,
                                                      &cache_module);

    /* Setup cache_request_rec */
    cache = (cache_request_rec *) ap_get_module_config(r->request_config,
                                                       &cache_module);
    if (!cache) {
        /* user likely configured CACHE_SAVE manually; they should really use
         * mod_cache configuration to do that
         */
        cache = apr_pcalloc(r->pool, sizeof(cache_request_rec));
        ap_set_module_config(r->request_config, &cache_module, cache);
        cache->size = -1;
    }

    reason = NULL;
    p = r->pool;
    /*
     * Pass Data to Cache
