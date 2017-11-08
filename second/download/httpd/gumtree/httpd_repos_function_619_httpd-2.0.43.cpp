static table_entry_t *first_entry(table_t * table_p,
                                  table_linear_t * linear_p)
{
    table_entry_t *entry_p;
    unsigned int bucket_c = 0;

    /* look for the first non-empty bucket */
    for (bucket_c = 0; bucket_c < table_p->ta_bucket_n; bucket_c++) {
        entry_p = table_p->ta_buckets[bucket_c];
        if (entry_p != NULL) {
            if (linear_p != NULL) {
                linear_p->tl_bucket_c = bucket_c;
                linear_p->tl_entry_c = 0;
            }
            return TABLE_POINTER(table_p, table_entry_t *, entry_p);
        }
    }

    return NULL;
}