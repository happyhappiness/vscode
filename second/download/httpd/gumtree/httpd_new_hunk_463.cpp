                }
                else if (h1 && h2 && !strcmp(h1, h2)) {
                    /* both headers exist and are equal - do nothing */
                }
                else {
                    /* headers do not match, so Vary failed */
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                                r->server,
                                "cache_select_url(): Vary header mismatch.");
                    return DECLINED;
                }
            }

            cache->provider = list->provider;
            cache->provider_name = list->provider_name;

            /* Is our cached response fresh enough? */
            fresh = ap_cache_check_freshness(h, r);
            if (!fresh) {
                cache_info *info = &(h->cache_obj->info);

                /* Make response into a conditional */
                /* FIXME: What if the request is already conditional? */
                if (info && info->etag) {
                    /* if we have a cached etag */
                    cache->stale_headers = apr_table_copy(r->pool,
                                                          r->headers_in);
                    apr_table_set(r->headers_in, "If-None-Match", info->etag);
                    cache->stale_handle = h;
                }
                else if (info && info->lastmods) {
                    /* if we have a cached Last-Modified header */
                    cache->stale_headers = apr_table_copy(r->pool,
                                                          r->headers_in);
                    apr_table_set(r->headers_in, "If-Modified-Since",
                                  info->lastmods);
                    cache->stale_handle = h;
                }

                return DECLINED;
            }

            /* Okay, this response looks okay.  Merge in our stuff and go. */
            apr_table_setn(r->headers_out, "Content-Type",
                           ap_make_content_type(r, h->content_type));
            r->filename = apr_pstrdup(r->pool, h->cache_obj->info.filename);
            accept_headers(h, r);

            cache->handle = h;
            return OK;
        }
        case DECLINED: {
            /* try again with next cache type */
            list = list->next;
            continue;
        }
        default: {
            /* oo-er! an error */
            return rv;
        }
        }
    }
    return DECLINED;
}

apr_status_t cache_generate_key_default( request_rec *r, apr_pool_t*p, char**key ) 
{
    if (r->hostname) {
