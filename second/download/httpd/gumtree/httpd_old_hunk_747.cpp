	abort();
    }
#endif
    make_array_core(&new->a, p, t->a.nalloc, sizeof(apr_table_entry_t), 0);
    memcpy(new->a.elts, t->a.elts, t->a.nelts * sizeof(apr_table_entry_t));
    new->a.nelts = t->a.nelts;
    return new;
}

APR_DECLARE(void) apr_table_clear(apr_table_t *t)
{
    t->a.nelts = 0;
}

APR_DECLARE(const char *) apr_table_get(const apr_table_t *t, const char *key)
{
    apr_table_entry_t *elts = (apr_table_entry_t *) t->a.elts;
    int i;
    apr_uint32_t checksum;

    if (key == NULL) {
	return NULL;
    }

    COMPUTE_KEY_CHECKSUM(key, checksum);
    for (i = 0; i < t->a.nelts; ++i) {
	if ((checksum == elts[i].key_checksum) && !strcasecmp(elts[i].key, key)) {
	    return elts[i].val;
	}
    }

    return NULL;
}

APR_DECLARE(void) apr_table_set(apr_table_t *t, const char *key,
			       const char *val)
{
    register int i, j, k;
    apr_table_entry_t *elts = (apr_table_entry_t *) t->a.elts;
    int done = 0;
    apr_uint32_t checksum;

    COMPUTE_KEY_CHECKSUM(key, checksum);
    for (i = 0; i < t->a.nelts; ) {
	if ((checksum == elts[i].key_checksum) && !strcasecmp(elts[i].key, key)) {
	    if (!done) {
		elts[i].val = apr_pstrdup(t->a.pool, val);
		done = 1;
		++i;
	    }
	    else {		/* delete an extraneous element */
		for (j = i, k = i + 1; k < t->a.nelts; ++j, ++k) {
		    elts[j].key = elts[k].key;
		    elts[j].val = elts[k].val;
                    elts[j].key_checksum = elts[k].key_checksum;
		}
		--t->a.nelts;
	    }
	}
	else {
	    ++i;
	}
    }

    if (!done) {
	elts = (apr_table_entry_t *) table_push(t);
	elts->key = apr_pstrdup(t->a.pool, key);
	elts->val = apr_pstrdup(t->a.pool, val);
        elts->key_checksum = checksum;
    }
}

APR_DECLARE(void) apr_table_setn(apr_table_t *t, const char *key,
				const char *val)
{
    register int i, j, k;
    apr_table_entry_t *elts = (apr_table_entry_t *) t->a.elts;
    int done = 0;
    apr_uint32_t checksum;

#ifdef POOL_DEBUG
    {
	if (!apr_pool_is_ancestor(apr_pool_find(key), t->a.pool)) {
	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
	    abort();
	}
	if (!apr_pool_is_ancestor(apr_pool_find(val), t->a.pool)) {
	    fprintf(stderr, "table_set: val not in ancestor pool of t\n");
	    abort();
	}
    }
#endif

    COMPUTE_KEY_CHECKSUM(key, checksum);
    for (i = 0; i < t->a.nelts; ) {
	if ((checksum == elts[i].key_checksum) && !strcasecmp(elts[i].key, key)) {
	    if (!done) {
		elts[i].val = (char *)val;
		done = 1;
		++i;
	    }
	    else {		/* delete an extraneous element */
		for (j = i, k = i + 1; k < t->a.nelts; ++j, ++k) {
		    elts[j].key = elts[k].key;
		    elts[j].val = elts[k].val;
		    elts[j].key_checksum = elts[k].key_checksum;
		}
		--t->a.nelts;
	    }
	}
	else {
	    ++i;
	}
    }

    if (!done) {
	elts = (apr_table_entry_t *) table_push(t);
	elts->key = (char *)key;
	elts->val = (char *)val;
	elts->key_checksum = checksum;
    }
}

APR_DECLARE(void) apr_table_unset(apr_table_t *t, const char *key)
{
    register int i, j, k;
    apr_table_entry_t *elts = (apr_table_entry_t *) t->a.elts;
    apr_uint32_t checksum;

    COMPUTE_KEY_CHECKSUM(key, checksum);
    for (i = 0; i < t->a.nelts; ) {
	if ((checksum == elts[i].key_checksum) && !strcasecmp(elts[i].key, key)) {

	    /* found an element to skip over
	     * there are any number of ways to remove an element from
	     * a contiguous block of memory.  I've chosen one that
	     * doesn't do a memcpy/bcopy/array_delete, *shrug*...
	     */
	    for (j = i, k = i + 1; k < t->a.nelts; ++j, ++k) {
		elts[j].key = elts[k].key;
		elts[j].val = elts[k].val;
		elts[j].key_checksum = elts[k].key_checksum;
	    }
	    --t->a.nelts;
	}
	else {
	    ++i;
	}
    }
}

APR_DECLARE(void) apr_table_merge(apr_table_t *t, const char *key,
				 const char *val)
{
    apr_table_entry_t *elts = (apr_table_entry_t *) t->a.elts;
    int i;
    apr_uint32_t checksum;

    COMPUTE_KEY_CHECKSUM(key, checksum);
    for (i = 0; i < t->a.nelts; ++i) {
	if ((checksum == elts[i].key_checksum) && !strcasecmp(elts[i].key, key)) {
	    elts[i].val = apr_pstrcat(t->a.pool, elts[i].val, ", ", val, NULL);
	    return;
	}
    }

    elts = (apr_table_entry_t *) table_push(t);
    elts->key = apr_pstrdup(t->a.pool, key);
    elts->val = apr_pstrdup(t->a.pool, val);
    elts->key_checksum = checksum;
}

APR_DECLARE(void) apr_table_mergen(apr_table_t *t, const char *key,
				  const char *val)
{
    apr_table_entry_t *elts = (apr_table_entry_t *) t->a.elts;
    int i;
    apr_uint32_t checksum;

#ifdef POOL_DEBUG
    {
	if (!apr_pool_is_ancestor(apr_pool_find(key), t->a.pool)) {
	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
	    abort();
