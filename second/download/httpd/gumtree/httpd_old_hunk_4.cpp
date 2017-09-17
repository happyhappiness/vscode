    {
	if (!ap_pool_is_ancestor(ap_find_pool(key), t->a.pool)) {
	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
	    abort();
	}
	if (!ap_pool_is_ancestor(ap_find_pool(val), t->a.pool)) {
	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
	    abort();
	}
    }
#endif

    for (i = 0; i < t->a.nelts; ) {
