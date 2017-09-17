    {
	if (!ap_pool_is_ancestor(ap_find_pool(key), t->a.pool)) {
	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
	    abort();
	}
	if (!ap_pool_is_ancestor(ap_find_pool(val), t->a.pool)) {
	    fprintf(stderr, "table_set: val not in ancestor pool of t\n");
	    abort();
	}
    }
#endif

    for (i = 0; i < t->a.nelts; ) {
++ apache_1.3.1/src/main/buff.c	1998-07-05 02:22:11.000000000 +0800
