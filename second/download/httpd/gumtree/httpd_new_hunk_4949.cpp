            }
        }
    }

    /* Key format is a URI, optionally without the query-string */
    if (conf->ignorequerystring) {
        *key = apr_pstrcat(p, scheme, "://", hostname, port_str, path, "?",
                NULL);
    }
    else {
        *key = apr_pstrcat(p, scheme, "://", hostname, port_str, path, "?",
                querystring, NULL);
    }

    /*
     * Store the key in the request_config for the cache as r->parsed_uri
     * might have changed in the time from our first visit here triggered by the
     * quick handler and our possible second visit triggered by the CACHE_SAVE
     * filter (e.g. r->parsed_uri got unescaped). In this case we would save the
     * resource in the cache under a key where it is never found by the quick
     * handler during following requests.
     */
    ap_log_rerror(
            APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00698) "cache: Key for entity %s?%s is %s", uri, parsed_uri->query, *key);

    return APR_SUCCESS;
}

apr_status_t cache_generate_key_default(request_rec *r, apr_pool_t* p,
        const char **key)
{
    return cache_canonicalise_key(r, p, r->uri, &r->parsed_uri, key);
}

/*
 * Invalidate a specific URL entity in all caches
 *
 * All cached entities for this URL are removed, usually in
 * response to a POST/PUT or DELETE.
 *
 * This function returns OK if at least one entity was found and
 * removed, and DECLINED if no cached entities were removed.
 */
int cache_invalidate(cache_request_rec *cache, request_rec *r)
{
    cache_provider_list *list;
    apr_status_t rv, status = DECLINED;
    cache_handle_t *h;
    apr_uri_t location_uri;
    apr_uri_t content_location_uri;

    const char *location, *location_key = NULL;
    const char *content_location, *content_location_key = NULL;

    if (!cache) {
        /* This should never happen */
        ap_log_rerror(
                APLOG_MARK, APLOG_ERR, APR_EGENERAL, r, APLOGNO(00697) "cache: No cache request information available for key"
                " generation");
        return DECLINED;
    }

    if (!cache->key) {
        rv = cache_generate_key(r, r->pool, &cache->key);
        if (rv != APR_SUCCESS) {
            return DECLINED;
        }
    }

    location = apr_table_get(r->headers_out, "Location");
    if (location) {
        if (APR_SUCCESS != apr_uri_parse(r->pool, location, &location_uri)
                || APR_SUCCESS
                        != cache_canonicalise_key(r, r->pool, location,
                                &location_uri, &location_key)
                || strcmp(r->parsed_uri.hostname, location_uri.hostname)) {
            location_key = NULL;
        }
    }

    content_location = apr_table_get(r->headers_out, "Content-Location");
    if (content_location) {
        if (APR_SUCCESS
                != apr_uri_parse(r->pool, content_location,
                        &content_location_uri)
                || APR_SUCCESS
                        != cache_canonicalise_key(r, r->pool, content_location,
                                &content_location_uri, &content_location_key)
                || strcmp(r->parsed_uri.hostname,
                        content_location_uri.hostname)) {
            content_location_key = NULL;
        }
    }

    /* go through the cache types */
    h = apr_palloc(r->pool, sizeof(cache_handle_t));

    list = cache->providers;

    while (list) {

        /* invalidate the request uri */
        rv = list->provider->open_entity(h, r, cache->key);
        if (OK == rv) {
            rv = list->provider->invalidate_entity(h, r);
            status = OK;
        }
        ap_log_rerror(
                APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(02468) "cache: Attempted to invalidate cached entity with key: %s", cache->key);

        /* invalidate the Location */
        if (location_key) {
            rv = list->provider->open_entity(h, r, location_key);
            if (OK == rv) {
                rv = list->provider->invalidate_entity(h, r);
                status = OK;
            }
            ap_log_rerror(
                    APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(02469) "cache: Attempted to invalidate cached entity with key: %s", location_key);
        }

        /* invalidate the Content-Location */
        if (content_location_key) {
            rv = list->provider->open_entity(h, r, content_location_key);
            if (OK == rv) {
                rv = list->provider->invalidate_entity(h, r);
                status = OK;
            }
            ap_log_rerror(
                    APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(02470) "cache: Attempted to invalidate cached entity with key: %s", content_location_key);
        }

        list = list->next;
    }

    return status;
}
