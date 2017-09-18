
static int cache_in_filter(ap_filter_t *f, apr_bucket_brigade *in)
{
    int rv;
    request_rec *r = f->r;
    char *url = r->unparsed_uri;
    const char *cc_out = apr_table_get(r->headers_out, "Cache-Control");
    const char *exps, *lastmods, *dates, *etag;
    apr_time_t exp, date, lastmod, now;
    apr_off_t size;
    cache_info *info;
    void *sconf = r->server->module_config;
    cache_server_conf *conf =
        (cache_server_conf *) ap_get_module_config(sconf, &cache_module);
    void *scache = r->request_config;
    cache_request_rec *cache =
        (cache_request_rec *) ap_get_module_config(scache, &cache_module);


    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server,
                 "cache: running CACHE_IN filter");

    /* check first whether running this filter has any point or not */
