static void *merge_dir_config(apr_pool_t *p, void *basev, void *addv) {
    cache_dir_conf *new = (cache_dir_conf *) apr_pcalloc(p, sizeof(cache_dir_conf));
    cache_dir_conf *add = (cache_dir_conf *) addv;
    cache_dir_conf *base = (cache_dir_conf *) basev;

    new->no_last_mod_ignore = (add->no_last_mod_ignore_set == 0) ? base->no_last_mod_ignore : add->no_last_mod_ignore;
    new->no_last_mod_ignore_set = add->no_last_mod_ignore_set || base->no_last_mod_ignore_set;

    new->store_expired = (add->store_expired_set == 0) ? base->store_expired : add->store_expired;
    new->store_expired_set = add->store_expired_set || base->store_expired_set;
    new->store_private = (add->store_private_set == 0) ? base->store_private : add->store_private;
    new->store_private_set = add->store_private_set || base->store_private_set;
    new->store_nostore = (add->store_nostore_set == 0) ? base->store_nostore : add->store_nostore;
    new->store_nostore_set = add->store_nostore_set || base->store_nostore_set;

    /* maximum time to cache a document */
    new->maxex = (add->maxex_set == 0) ? base->maxex : add->maxex;
    new->maxex_set = add->maxex_set || base->maxex_set;
    new->minex = (add->minex_set == 0) ? base->minex : add->minex;
    new->minex_set = add->minex_set || base->minex_set;

    /* default time to cache a document */
    new->defex = (add->defex_set == 0) ? base->defex : add->defex;
    new->defex_set = add->defex_set || base->defex_set;

    /* factor used to estimate Expires date from LastModified date */
    new->factor = (add->factor_set == 0) ? base->factor : add->factor;
    new->factor_set = add->factor_set || base->factor_set;

    new->x_cache = (add->x_cache_set == 0) ? base->x_cache : add->x_cache;
    new->x_cache_set = add->x_cache_set || base->x_cache_set;
    new->x_cache_detail = (add->x_cache_detail_set == 0) ? base->x_cache_detail
            : add->x_cache_detail;
    new->x_cache_detail_set = add->x_cache_detail_set
            || base->x_cache_detail_set;

    new->stale_on_error = (add->stale_on_error_set == 0) ? base->stale_on_error
            : add->stale_on_error;
    new->stale_on_error_set = add->stale_on_error_set
            || base->stale_on_error_set;

    new->cacheenable = add->enable_set ? apr_array_append(p, base->cacheenable,
            add->cacheenable) : base->cacheenable;
    new->enable_set = add->enable_set || base->enable_set;
    new->disable = (add->disable_set == 0) ? base->disable : add->disable;
    new->disable_set = add->disable_set || base->disable_set;

    return new;
}