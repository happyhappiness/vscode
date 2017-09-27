				const char *val)
{
    apr_table_entry_t *elts;
    apr_uint32_t checksum;
    int hash;

#if APR_POOL_DEBUG
    {
	if (!apr_pool_is_ancestor(apr_pool_find(key), t->a.pool)) {
	    fprintf(stderr, "apr_table_addn: key not in ancestor pool of t\n");
	    abort();
	}
	if (!apr_pool_is_ancestor(apr_pool_find(val), t->a.pool)) {
	    fprintf(stderr, "apr_table_addn: key not in ancestor pool of t\n");
	    abort();
	}
    }
#endif

    hash = TABLE_HASH(key);
