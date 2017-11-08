static void *create_dir_config(apr_pool_t *p, char *dummy)
{
    cache_dir_conf *dconf = apr_pcalloc(p, sizeof(cache_dir_conf));

    dconf->no_last_mod_ignore = 0;
    dconf->store_expired = 0;
    dconf->store_private = 0;
    dconf->store_nostore = 0;

    /* maximum time to cache a document */
    dconf->maxex = DEFAULT_CACHE_MAXEXPIRE;
    dconf->minex = DEFAULT_CACHE_MINEXPIRE;
    /* default time to cache a document */
    dconf->defex = DEFAULT_CACHE_EXPIRE;

    /* factor used to estimate Expires date from LastModified date */
    dconf->factor = DEFAULT_CACHE_LMFACTOR;

    dconf->x_cache = DEFAULT_X_CACHE;
    dconf->x_cache_detail = DEFAULT_X_CACHE_DETAIL;

    dconf->stale_on_error = DEFAULT_CACHE_STALE_ON_ERROR;

    /* array of providers for this URL space */
    dconf->cacheenable = apr_array_make(p, 10, sizeof(struct cache_enable));

    return dconf;
}