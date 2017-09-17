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
-- apache_1.3.0/src/main/buff.c	1998-05-17 00:34:48.000000000 +0800
