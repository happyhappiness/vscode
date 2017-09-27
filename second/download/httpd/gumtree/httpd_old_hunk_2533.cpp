 * admin. The CACHE filter is then removed.
 *
 * This allows caching to be performed before the content is passed to the
 * INCLUDES filter, or to a filter that might perform transformations unique
 * to the specific request and that would otherwise be non-cacheable.
 */
static int cache_filter(ap_filter_t *f, apr_bucket_brigade *in)
{
    /* we are just a marker, so let's just remove ourselves */
    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, f->r->server,
                 "cache: CACHE filter was added twice, or was added in quick "
    		     "handler mode and will be ignored.");
    ap_remove_output_filter(f);
    return ap_pass_brigade(f->next, in);
}

/* -------------------------------------------------------------- */
/* Setup configurable data */

static void * create_cache_config(apr_pool_t *p, server_rec *s)
{
    const char *tmppath;
    cache_server_conf *ps = apr_pcalloc(p, sizeof(cache_server_conf));

    /* array of URL prefixes for which caching is enabled */
    ps->cacheenable = apr_array_make(p, 10, sizeof(struct cache_enable));
    /* array of URL prefixes for which caching is disabled */
    ps->cachedisable = apr_array_make(p, 10, sizeof(struct cache_disable));
    /* maximum time to cache a document */
    ps->maxex = DEFAULT_CACHE_MAXEXPIRE;
    ps->maxex_set = 0;
    ps->minex = DEFAULT_CACHE_MINEXPIRE;
    ps->minex_set = 0;
    /* default time to cache a document */
    ps->defex = DEFAULT_CACHE_EXPIRE;
    ps->defex_set = 0;
    /* factor used to estimate Expires date from LastModified date */
    ps->factor = DEFAULT_CACHE_LMFACTOR;
    ps->factor_set = 0;
    ps->no_last_mod_ignore_set = 0;
    ps->no_last_mod_ignore = 0;
    ps->ignorecachecontrol = 0;
    ps->ignorecachecontrol_set = 0;
    ps->store_private = 0;
    ps->store_private_set = 0;
    ps->store_nostore = 0;
    ps->store_nostore_set = 0;
    /* array of headers that should not be stored in cache */
    ps->ignore_headers = apr_array_make(p, 10, sizeof(char *));
    ps->ignore_headers_set = CACHE_IGNORE_HEADERS_UNSET;
    /* flag indicating that query-string should be ignored when caching */
    ps->ignorequerystring = 0;
    ps->ignorequerystring_set = 0;
