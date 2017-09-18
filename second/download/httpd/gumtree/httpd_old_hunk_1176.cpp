 * Can we deliver this request from the cache?
 * If yes:
 *   deliver the content by installing the CACHE_OUT filter.
 * If no:
 *   check whether we're allowed to try cache it
 *   If yes:
 *     add CACHE_IN filter
 *   If No:
 *     oh well.
 */

static int cache_url_handler(request_rec *r, int lookup)
{
    apr_status_t rv;
    const char *cc_in, *pragma, *auth;
    apr_uri_t uri = r->parsed_uri;
    char *url = r->unparsed_uri;
    apr_size_t urllen;
    char *path = uri.path;
    const char *types;
    cache_info *info = NULL;
    cache_request_rec *cache;
    cache_server_conf *conf;

    conf = (cache_server_conf *) ap_get_module_config(r->server->module_config,
                                                      &cache_module);

    /* we don't handle anything but GET */
    if (r->method_number != M_GET) {
        return DECLINED;
    }

    /*
     * Which cache module (if any) should handle this request?
     */
    if (!(types = ap_cache_get_cachetype(r, conf, path))) {
        return DECLINED;
    }

    urllen = strlen(url);
    if (urllen > MAX_URL_LENGTH) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache: URL exceeds length threshold: %s", url);
        return DECLINED;
    }
    /* DECLINE urls ending in / ??? EGP: why? */
    if (url[urllen-1] == '/') {
        return DECLINED;
    }

    /* make space for the per request config */
    cache = (cache_request_rec *) ap_get_module_config(r->request_config, 
                                                       &cache_module);
    if (!cache) {
        cache = apr_pcalloc(r->pool, sizeof(cache_request_rec));
        ap_set_module_config(r->request_config, &cache_module, cache);
    }

    /* save away the type */
    cache->types = types;

    /*
     * Are we allowed to serve cached info at all?
     */

    /* find certain cache controlling headers */
    cc_in = apr_table_get(r->headers_in, "Cache-Control");
    pragma = apr_table_get(r->headers_in, "Pragma");
    auth = apr_table_get(r->headers_in, "Authorization");

    /* first things first - does the request allow us to return
     * cached information at all? If not, just decline the request.
     *
