	    abort();
	}
    }
#endif

    COMPUTE_KEY_CHECKSUM(key, checksum);
    for (i = 0; i < t->a.nelts; ++i) {
	if ((checksum == elts[i].key_checksum) && !strcasecmp(elts[i].key, key)) {
	    elts[i].val = apr_pstrcat(t->a.pool, elts[i].val, ", ", val, NULL);
	    return;
	}
    }

    elts = (apr_table_entry_t *) table_push(t);
    elts->key = (char *)key;
    elts->val = (char *)val;
    elts->key_checksum = checksum;
}

APR_DECLARE(void) apr_table_add(apr_table_t *t, const char *key,
			       const char *val)
{
    apr_table_entry_t *elts;
    apr_uint32_t checksum;

    COMPUTE_KEY_CHECKSUM(key, checksum);
    elts = (apr_table_entry_t *) table_push(t);
    elts->key = apr_pstrdup(t->a.pool, key);
    elts->val = apr_pstrdup(t->a.pool, val);
    elts->key_checksum = checksum;
}

APR_DECLARE(void) apr_table_addn(apr_table_t *t, const char *key,
				const char *val)
{
    apr_table_entry_t *elts;
    apr_uint32_t checksum;

#ifdef POOL_DEBUG
    {
	if (!apr_pool_is_ancestor(apr_pool_find(key), t->a.pool)) {
	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
	    abort();
