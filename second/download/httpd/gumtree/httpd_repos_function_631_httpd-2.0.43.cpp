int table_clear(table_t * table_p)
{
#if 0
    table_entry_t *entry_p, *next_p;
#endif
    table_entry_t **bucket_p, **bounds_p;

    if (table_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (table_p->ta_magic != TABLE_MAGIC)
        return TABLE_ERROR_PNT;
    /* free the table allocation and table structure */
    bounds_p = table_p->ta_buckets + table_p->ta_bucket_n;
    for (bucket_p = table_p->ta_buckets; bucket_p <= bounds_p; bucket_p++) {
#if 0
        for (entry_p = *bucket_p; entry_p != NULL; entry_p = next_p) {
            /* record the next pointer before we free */
            next_p = entry_p->te_next_p;
            table_p->ta_free(table_p->opt_param, entry_p);
        }
#endif
        /* clear the bucket entry after we free its entries */
        *bucket_p = NULL;
    }

    /* reset table state info */
    table_p->ta_entry_n = 0;
    table_p->ta_linear.tl_magic = 0;
    table_p->ta_linear.tl_bucket_c = 0;
    table_p->ta_linear.tl_entry_c = 0;

    return TABLE_ERROR_NONE;
}