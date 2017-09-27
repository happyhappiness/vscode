APR_DECLARE(apr_table_t *) apr_table_overlay(apr_pool_t *p,
					     const apr_table_t *overlay,
					     const apr_table_t *base)
{
    apr_table_t *res;

#if APR_POOL_DEBUG
    /* we don't copy keys and values, so it's necessary that
     * overlay->a.pool and base->a.pool have a life span at least
     * as long as p
     */
    if (!apr_pool_is_ancestor(overlay->a.pool, p)) {
	fprintf(stderr,
		"apr_table_overlay: overlay's pool is not an ancestor of p\n");
	abort();
    }
    if (!apr_pool_is_ancestor(base->a.pool, p)) {
	fprintf(stderr,
		"apr_table_overlay: base's pool is not an ancestor of p\n");
	abort();
    }
#endif

    res = apr_palloc(p, sizeof(apr_table_t));
    /* behave like append_arrays */
