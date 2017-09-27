                }
                else if (h1 && h2 && !strcmp(h1, h2)) {
                    /* both headers exist and are equal - do nothing */
                }
                else {
                    /* headers do not match, so Vary failed */
                    ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS, r->server,
                                 "cache_select_url(): Vary header mismatch - Cached document cannot be used. \n");
                    apr_table_clear(r->headers_out);
                    r->status_line = NULL;
                    cache->handle = NULL;
                    return DECLINED;
                }
            }
            cache->provider = list->provider;
            cache->provider_name = list->provider_name;
            return OK;
        }
        case DECLINED: {
            /* try again with next cache type */
            list = list->next;
            continue;
        }
        default: {
            /* oo-er! an error */
            cache->handle = NULL;
            return rv;
        }
        }
    }
    cache->handle = NULL;
    return DECLINED;
}

apr_status_t cache_generate_key_default( request_rec *r, apr_pool_t*p, char**key ) 
{
    if (r->hostname) {
