    {
	if (!apr_pool_is_ancestor(apr_pool_find(key), t->a.pool)) {
	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
	    abort();
	}
	if (!apr_pool_is_ancestor(apr_pool_find(val), t->a.pool)) {
	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
	    abort();
	}
    }
#endif

    hash = TABLE_HASH(key);
