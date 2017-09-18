 *
 * Deliver cached content (headers and body) up the stack.
 */
static int cache_out_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    request_rec *r = f->r;
    cache_request_rec *cache;

    cache = (cache_request_rec *) ap_get_module_config(r->request_config, 
                                                       &cache_module);

    if (!cache) {
        /* user likely configured CACHE_OUT manually; they should use mod_cache
         * configuration to do that */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "CACHE_OUT enabled unexpectedly");
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, bb);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
                 "cache: running CACHE_OUT filter");

    /* cache_read_entity_headers() was called in cache_select_url() */
    cache_read_entity_body(cache->handle, r->pool, bb);

    /* This filter is done once it has served up its content */
    ap_remove_output_filter(f);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
                 "cache: serving cached version of %s", r->uri);
    return ap_pass_brigade(f->next, bb);
}


/*
 * CACHE_CONDITIONAL filter
