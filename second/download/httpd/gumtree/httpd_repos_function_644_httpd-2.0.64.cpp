int table_adjust(table_t * table_p, const int bucket_n)
{
    table_entry_t *entry_p, *next_p;
    table_entry_t **buckets, **bucket_p, **bounds_p;
    int bucket;
    unsigned int buck_n;

    if (table_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (table_p->ta_magic != TABLE_MAGIC)
        return TABLE_ERROR_PNT;
    /*
     * NOTE: we walk through the entries and rehash them.  If we stored
     * the hash value as a full int in the table-entry, all we would
     * have to do is remod it.
     */

    /* normalize to the number of entries */
    if (bucket_n == 0)
        buck_n = table_p->ta_entry_n;
    else
        buck_n = bucket_n;
    /* we must have at least 1 bucket */
    if (buck_n == 0)
        buck_n = 1;
    /* make sure we have somethign to do */
    if (buck_n <= table_p->ta_bucket_n)
        return TABLE_ERROR_NONE;
    /* allocate a new bucket list */
    buckets = (table_entry_t **)
               table_p->ta_calloc(table_p->opt_param,
                                  buck_n, sizeof(table_entry_t *));
    if (table_p->ta_buckets == NULL)
        return TABLE_ERROR_ALLOC;
    /*
     * run through each of the items in the current table and rehash
     * them into the newest bucket sizes
     */
    bounds_p = table_p->ta_buckets + table_p->ta_bucket_n;
    for (bucket_p = table_p->ta_buckets; bucket_p < bounds_p; bucket_p++) {
        for (entry_p = *bucket_p; entry_p != NULL; entry_p = next_p) {

            /* hash the old data into the new table size */
            bucket = hash(ENTRY_KEY_BUF(entry_p), entry_p->te_key_size, 0) % buck_n;

            /* record the next one now since we overwrite next below */
            next_p = entry_p->te_next_p;

            /* insert into new list, no need to append */
            entry_p->te_next_p = buckets[bucket];
            buckets[bucket] = entry_p;

            /*
             * NOTE: we may want to adjust the bucket_c linear entry here to
             * keep it current
             */
        }
        /* remove the old table pointers as we go by */
        *bucket_p = NULL;
    }

    /* replace the table buckets with the new ones */
    table_p->ta_free(table_p->opt_param, table_p->ta_buckets);
    table_p->ta_buckets = buckets;
    table_p->ta_bucket_n = buck_n;

    return TABLE_ERROR_NONE;
}