	abort();
    }
#endif
    make_array_core(&new->a, p, t->a.nalloc, sizeof(apr_table_entry_t), 0);
    memcpy(new->a.elts, t->a.elts, t->a.nelts * sizeof(apr_table_entry_t));
    new->a.nelts = t->a.nelts;
    memcpy(new->index_first, t->index_first, sizeof(int) * TABLE_HASH_SIZE);
    memcpy(new->index_last, t->index_last, sizeof(int) * TABLE_HASH_SIZE);
    new->index_initialized = t->index_initialized;
    return new;
}

static void table_reindex(apr_table_t *t)
{
    int i;
    int hash;
    apr_table_entry_t *next_elt = (apr_table_entry_t *) t->a.elts;

    t->index_initialized = 0;
    for (i = 0; i < t->a.nelts; i++, next_elt++) {
        hash = TABLE_HASH(next_elt->key);
        t->index_last[hash] = i;
        if (!TABLE_INDEX_IS_INITIALIZED(t, hash)) {
            t->index_first[hash] = i;
            TABLE_SET_INDEX_INITIALIZED(t, hash);
        }
    }
}

APR_DECLARE(void) apr_table_clear(apr_table_t *t)
{
    t->a.nelts = 0;
    t->index_initialized = 0;
}

APR_DECLARE(const char *) apr_table_get(const apr_table_t *t, const char *key)
{
    apr_table_entry_t *next_elt;
    apr_table_entry_t *end_elt;
    apr_uint32_t checksum;
    int hash;

    if (key == NULL) {
	return NULL;
    }

    hash = TABLE_HASH(key);
    if (!TABLE_INDEX_IS_INITIALIZED(t, hash)) {
        return NULL;
    }
    COMPUTE_KEY_CHECKSUM(key, checksum);
    next_elt = ((apr_table_entry_t *) t->a.elts) + t->index_first[hash];;
    end_elt = ((apr_table_entry_t *) t->a.elts) + t->index_last[hash];

    for (; next_elt <= end_elt; next_elt++) {
	if ((checksum == next_elt->key_checksum) &&
            !strcasecmp(next_elt->key, key)) {
	    return next_elt->val;
	}
    }

    return NULL;
}

APR_DECLARE(void) apr_table_set(apr_table_t *t, const char *key,
                                const char *val)
{
    apr_table_entry_t *next_elt;
    apr_table_entry_t *end_elt;
    apr_table_entry_t *table_end;
    apr_uint32_t checksum;
    int hash;

    COMPUTE_KEY_CHECKSUM(key, checksum);
    hash = TABLE_HASH(key);
    if (!TABLE_INDEX_IS_INITIALIZED(t, hash)) {
        t->index_first[hash] = t->a.nelts;
        TABLE_SET_INDEX_INITIALIZED(t, hash);
        goto add_new_elt;
    }
    next_elt = ((apr_table_entry_t *) t->a.elts) + t->index_first[hash];;
    end_elt = ((apr_table_entry_t *) t->a.elts) + t->index_last[hash];
    table_end =((apr_table_entry_t *) t->a.elts) + t->a.nelts;

    for (; next_elt <= end_elt; next_elt++) {
	if ((checksum == next_elt->key_checksum) &&
            !strcasecmp(next_elt->key, key)) {

            /* Found an existing entry with the same key, so overwrite it */

            int must_reindex = 0;
            apr_table_entry_t *dst_elt = NULL;

            next_elt->val = apr_pstrdup(t->a.pool, val);

            /* Remove any other instances of this key */
            for (next_elt++; next_elt <= end_elt; next_elt++) {
                if ((checksum == next_elt->key_checksum) &&
                    !strcasecmp(next_elt->key, key)) {
                    t->a.nelts--;
                    if (!dst_elt) {
                        dst_elt = next_elt;
                    }
                }
                else if (dst_elt) {
                    *dst_elt++ = *next_elt;
                    must_reindex = 1;
		}
	    }

            /* If we've removed anything, shift over the remainder
             * of the table (note that the previous loop didn't
             * run to the end of the table, just to the last match
             * for the index)
             */
            if (dst_elt) {
                for (; next_elt < table_end; next_elt++) {
                    *dst_elt++ = *next_elt;
                }
                must_reindex = 1;
            }
            if (must_reindex) {
                table_reindex(t);
            }
            return;
	}
    }

add_new_elt:
    t->index_last[hash] = t->a.nelts;
    next_elt = (apr_table_entry_t *) table_push(t);
    next_elt->key = apr_pstrdup(t->a.pool, key);
    next_elt->val = apr_pstrdup(t->a.pool, val);
    next_elt->key_checksum = checksum;
}

APR_DECLARE(void) apr_table_setn(apr_table_t *t, const char *key,
                                 const char *val)
{
    apr_table_entry_t *next_elt;
    apr_table_entry_t *end_elt;
    apr_table_entry_t *table_end;
    apr_uint32_t checksum;
    int hash;

    COMPUTE_KEY_CHECKSUM(key, checksum);
    hash = TABLE_HASH(key);
    if (!TABLE_INDEX_IS_INITIALIZED(t, hash)) {
        t->index_first[hash] = t->a.nelts;
        TABLE_SET_INDEX_INITIALIZED(t, hash);
        goto add_new_elt;
    }
    next_elt = ((apr_table_entry_t *) t->a.elts) + t->index_first[hash];;
    end_elt = ((apr_table_entry_t *) t->a.elts) + t->index_last[hash];
    table_end =((apr_table_entry_t *) t->a.elts) + t->a.nelts;

    for (; next_elt <= end_elt; next_elt++) {
	if ((checksum == next_elt->key_checksum) &&
            !strcasecmp(next_elt->key, key)) {

            /* Found an existing entry with the same key, so overwrite it */

            int must_reindex = 0;
            apr_table_entry_t *dst_elt = NULL;

            next_elt->val = (char *)val;

            /* Remove any other instances of this key */
            for (next_elt++; next_elt <= end_elt; next_elt++) {
                if ((checksum == next_elt->key_checksum) &&
                    !strcasecmp(next_elt->key, key)) {
                    t->a.nelts--;
                    if (!dst_elt) {
                        dst_elt = next_elt;
                    }
                }
                else if (dst_elt) {
                    *dst_elt++ = *next_elt;
                    must_reindex = 1;
		}
	    }

            /* If we've removed anything, shift over the remainder
             * of the table (note that the previous loop didn't
             * run to the end of the table, just to the last match
             * for the index)
             */
            if (dst_elt) {
                for (; next_elt < table_end; next_elt++) {
                    *dst_elt++ = *next_elt;
                }
                must_reindex = 1;
            }
            if (must_reindex) {
                table_reindex(t);
            }
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

APR_DECLARE(void) apr_table_unset(apr_table_t *t, const char *key)
{
    apr_table_entry_t *next_elt;
    apr_table_entry_t *end_elt;
    apr_table_entry_t *dst_elt;
    apr_uint32_t checksum;
    int hash;
    int must_reindex;

    hash = TABLE_HASH(key);
    if (!TABLE_INDEX_IS_INITIALIZED(t, hash)) {
        return;
    }
    COMPUTE_KEY_CHECKSUM(key, checksum);
    next_elt = ((apr_table_entry_t *) t->a.elts) + t->index_first[hash];
    end_elt = ((apr_table_entry_t *) t->a.elts) + t->index_last[hash];
    must_reindex = 0;
    for (; next_elt <= end_elt; next_elt++) {
	if ((checksum == next_elt->key_checksum) &&
            !strcasecmp(next_elt->key, key)) {

            /* Found a match: remove this entry, plus any additional
             * matches for the same key that might follow
	     */
            apr_table_entry_t *table_end = ((apr_table_entry_t *) t->a.elts) +
                t->a.nelts;
            t->a.nelts--;
            dst_elt = next_elt;
            for (next_elt++; next_elt <= end_elt; next_elt++) {
                if ((checksum == next_elt->key_checksum) &&
                    !strcasecmp(next_elt->key, key)) {
                    t->a.nelts--;
                }
                else {
                    *dst_elt++ = *next_elt;
                }
	    }

            /* Shift over the remainder of the table (note that
             * the previous loop didn't run to the end of the table,
             * just to the last match for the index)
             */
            for (; next_elt < table_end; next_elt++) {
                *dst_elt++ = *next_elt;
            }
            must_reindex = 1;
            break;
	}
    }
    if (must_reindex) {
        table_reindex(t);
    }
}

APR_DECLARE(void) apr_table_merge(apr_table_t *t, const char *key,
				 const char *val)
{
    apr_table_entry_t *next_elt;
    apr_table_entry_t *end_elt;
    apr_uint32_t checksum;
    int hash;

    COMPUTE_KEY_CHECKSUM(key, checksum);
    hash = TABLE_HASH(key);
    if (!TABLE_INDEX_IS_INITIALIZED(t, hash)) {
        t->index_first[hash] = t->a.nelts;
        TABLE_SET_INDEX_INITIALIZED(t, hash);
        goto add_new_elt;
    }
    next_elt = ((apr_table_entry_t *) t->a.elts) + t->index_first[hash];
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
    next_elt->key = apr_pstrdup(t->a.pool, key);
    next_elt->val = apr_pstrdup(t->a.pool, val);
    next_elt->key_checksum = checksum;
}

APR_DECLARE(void) apr_table_mergen(apr_table_t *t, const char *key,
				  const char *val)
{
    apr_table_entry_t *next_elt;
    apr_table_entry_t *end_elt;
    apr_uint32_t checksum;
    int hash;

#ifdef POOL_DEBUG
    {
	if (!apr_pool_is_ancestor(apr_pool_find(key), t->a.pool)) {
	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
	    abort();
