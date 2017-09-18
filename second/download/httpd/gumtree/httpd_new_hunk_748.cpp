	    abort();
	}
    }
#endif

    COMPUTE_KEY_CHECKSUM(key, checksum);
    hash = TABLE_HASH(key);
    if (!TABLE_INDEX_IS_INITIALIZED(t, hash)) {
        t->index_first[hash] = t->a.nelts;
        TABLE_SET_INDEX_INITIALIZED(t, hash);
        goto add_new_elt;
    }
    next_elt = ((apr_table_entry_t *) t->a.elts) + t->index_first[hash];;
    end_elt = ((apr_table_entry_t *) t->a.elts) + t->index_last[hash];

    for (; next_elt <= end_elt; next_elt++) {
	if ((checksum == next_elt->key_checksum) &&
            !strcasecmp(next_elt->key, key)) {

            /* Found an existing entry with the same key, so merge with it */
	    next_elt->val = apr_pstrcat(t->a.pool, next_elt->val, ", ",
                                        val, NULL);
	    return;
	}
    }

add_new_elt:
    t->index_last[hash] = t->a.nelts;
    next_elt = (apr_table_entry_t *) table_push(t);
    next_elt->key = (char *)key;
    next_elt->val = (char *)val;
    next_elt->key_checksum = checksum;
}

APR_DECLARE(void) apr_table_add(apr_table_t *t, const char *key,
			       const char *val)
{
    apr_table_entry_t *elts;
    apr_uint32_t checksum;
    int hash;

    hash = TABLE_HASH(key);
    t->index_last[hash] = t->a.nelts;
    if (!TABLE_INDEX_IS_INITIALIZED(t, hash)) {
        t->index_first[hash] = t->a.nelts;
        TABLE_SET_INDEX_INITIALIZED(t, hash);
    }
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
    int hash;

#ifdef POOL_DEBUG
    {
	if (!apr_pool_is_ancestor(apr_pool_find(key), t->a.pool)) {
	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
	    abort();
