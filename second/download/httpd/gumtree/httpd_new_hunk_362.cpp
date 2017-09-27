 * Can we deliver this request from the cache?
 * If yes:
 *   deliver the content by installing the CACHE_OUT filter.
 * If no:
 *   check whether we're allowed to try cache it
 *   If yes:
 *     add CACHE_SAVE filter
 *   If No:
 *     oh well.
 */

static int cache_url_handler(request_rec *r, int lookup)
{
    apr_status_t rv;
    const char *pragma, *auth;
    apr_uri_t uri;
    char *url;
    char *path;
    cache_provider_list *providers;
    cache_info *info;
    cache_request_rec *cache;
    cache_server_conf *conf;
    apr_bucket_brigade *out;

    /* Delay initialization until we know we are handling a GET */
    if (r->method_number != M_GET) {
        return DECLINED;
    }

    uri = r->parsed_uri;
    url = r->unparsed_uri;
    path = uri.path;
    info = NULL;

    conf = (cache_server_conf *) ap_get_module_config(r->server->module_config,
                                                      &cache_module);

    /*
     * Which cache module (if any) should handle this request?
     */
    if (!(providers = ap_cache_get_providers(r, conf, path))) {
        return DECLINED;
    }

    /* make space for the per request config */
    cache = (cache_request_rec *) ap_get_module_config(r->request_config,
                                                       &cache_module);
    if (!cache) {
        cache = apr_pcalloc(r->pool, sizeof(cache_request_rec));
        ap_set_module_config(r->request_config, &cache_module, cache);
    }

    /* save away the possible providers */
    cache->providers = providers;

    /*
     * Are we allowed to serve cached info at all?
     */

    /* find certain cache controlling headers */
    pragma = apr_table_get(r->headers_in, "Pragma");
    auth = apr_table_get(r->headers_in, "Authorization");

    /* first things first - does the request allow us to return
     * cached information at all? If not, just decline the request.
     *
