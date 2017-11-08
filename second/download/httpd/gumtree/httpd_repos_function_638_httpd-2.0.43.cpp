int table_info(table_t * table_p, int *num_buckets_p, int *num_entries_p)
{
    if (table_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (table_p->ta_magic != TABLE_MAGIC)
        return TABLE_ERROR_PNT;
    if (num_buckets_p != NULL)
        *num_buckets_p = table_p->ta_bucket_n;
    if (num_entries_p != NULL)
        *num_entries_p = table_p->ta_entry_n;
    return TABLE_ERROR_NONE;
}