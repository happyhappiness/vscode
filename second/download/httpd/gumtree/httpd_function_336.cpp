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
     * Note that there is a big difference between not being allowed
     * to cache a request (no-store) and not being allowed to return
     * a cached request without revalidation (max-age=0).
     *
     * Caching is forbidden under the following circumstances:
     *
     * - RFC2616 14.9.2 Cache-Control: no-store
     * - Pragma: no-cache
     * - Any requests requiring authorization.
     */
    if (conf->ignorecachecontrol == 1 && auth == NULL) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "incoming request is asking for a uncached version of "
                     "%s, but we know better and are ignoring it", url);
    }
    else {
        if (ap_cache_liststr(NULL, cc_in, "no-store", NULL) ||
            ap_cache_liststr(NULL, pragma, "no-cache", NULL) || (auth != NULL)) {
            /* delete the previously cached file */
            cache_remove_url(r, cache->types, url);

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache: no-store forbids caching of %s", url);
            return DECLINED;
        }
    }

    /*
     * Try to serve this request from the cache.
     *
     * If no existing cache file
     *   add cache_in filter
     * If stale cache file
     *   If conditional request
     *     add cache_in filter
     *   If non-conditional request
     *     fudge response into a conditional
     *     add cache_conditional filter
     * If fresh cache file
     *   clear filter stack
     *   add cache_out filter
     */

    rv = cache_select_url(r, cache->types, url);
    if (DECLINED == rv) {
        if (!lookup) {
            /* no existing cache file */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache: no cache - add cache_in filter and DECLINE");
            /* add cache_in filter to cache this request */
            ap_add_output_filter_handle(cache_in_filter_handle, NULL, r,
                                        r->connection);
        }
        return DECLINED;
    }
    else if (OK == rv) {
        /* RFC2616 13.2 - Check cache object expiration */
        cache->fresh = ap_cache_check_freshness(cache, r);
        if (cache->fresh) {
            /* fresh data available */
            apr_bucket_brigade *out;
            conn_rec *c = r->connection;

            if (lookup) {
                return OK;
            }
            rv = ap_meets_conditions(r);
            if (rv != OK) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "cache: fresh cache - returning status %d", rv);
                return rv;
            }

            /*
             * Not a conditionl request. Serve up the content 
             */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache: fresh cache - add cache_out filter and "
                         "handle request");

            /* We are in the quick handler hook, which means that no output
             * filters have been set. So lets run the insert_filter hook.
             */
            ap_run_insert_filter(r);
            ap_add_output_filter_handle(cache_out_filter_handle, NULL,
                                        r, r->connection);

            /* kick off the filter stack */
            out = apr_brigade_create(r->pool, c->bucket_alloc);
            if (APR_SUCCESS
                != (rv = ap_pass_brigade(r->output_filters, out))) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                             "cache: error returned while trying to return %s "
                             "cached data", 
                             cache->type);
                return rv;
            }
            return OK;
        }
        else {
            if (!r->err_headers_out) {
                r->err_headers_out = apr_table_make(r->pool, 3);
            }
            /* stale data available */
            if (lookup) {
                return DECLINED;
            }

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache: stale cache - test conditional");
            /* if conditional request */
            if (ap_cache_request_is_conditional(r)) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                             r->server,
                             "cache: conditional - add cache_in filter and "
                             "DECLINE");
                /* Why not add CACHE_CONDITIONAL? */
                ap_add_output_filter_handle(cache_in_filter_handle, NULL,
                                            r, r->connection);

                return DECLINED;
            }
            /* else if non-conditional request */
            else {
                /* Temporarily hack this to work the way it had been. Its broken,
                 * but its broken the way it was before. I'm working on figuring
                 * out why the filter add in the conditional filter doesn't work. pjr
                 *
                 * info = &(cache->handle->cache_obj->info);
                 *
                 * Uncomment the above when the code in cache_conditional_filter_handle
                 * is properly fixed...  pjr
                 */
                
                /* fudge response into a conditional */
                if (info && info->etag) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                                 r->server,
                                 "cache: nonconditional - fudge conditional "
                                 "by etag");
                    /* if we have a cached etag */
                    apr_table_set(r->headers_in, "If-None-Match", info->etag);
                }
                else if (info && info->lastmods) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                                 r->server,
                                 "cache: nonconditional - fudge conditional "
                                 "by lastmod");
                    /* if we have a cached IMS */
                    apr_table_set(r->headers_in, 
                                  "If-Modified-Since", 
                                  info->lastmods);
                }
                else {
                    /* something else - pretend there was no cache */
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                                 r->server,
                                 "cache: nonconditional - no cached "
                                 "etag/lastmods - add cache_in and DECLINE");

                    ap_add_output_filter_handle(cache_in_filter_handle, NULL,
                                                r, r->connection);

                    return DECLINED;
                }
                /* add cache_conditional filter */
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                             r->server,
                             "cache: nonconditional - add cache_conditional "
                             "and DECLINE");
                ap_add_output_filter_handle(cache_conditional_filter_handle,
                                            NULL, 
                                            r, 
                                            r->connection);

                return DECLINED;
            }
        }
    }
    else {
        /* error */
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, 
                     r->server,
                     "cache: error returned while checking for cached file by "
                     "%s cache", 
                     cache->type);
        return DECLINED;
    }
}