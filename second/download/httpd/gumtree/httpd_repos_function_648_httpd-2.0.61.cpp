int table_this_r(table_t * table_p, table_linear_t * linear_p,
                 void **key_buf_p, int *key_size_p,
                 void **data_buf_p, int *data_size_p)
{
    table_entry_t *entry_p;
    int entry_c;

    if (table_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (table_p->ta_magic != TABLE_MAGIC)
        return TABLE_ERROR_PNT;
    if (linear_p->tl_magic != LINEAR_MAGIC)
        return TABLE_ERROR_LINEAR;
    /* if we removed an item that shorted the bucket list, we may get this */
    if (linear_p->tl_bucket_c >= table_p->ta_bucket_n) {
        /*
         * NOTE: this might happen if we delete an item which shortens the
         * table bucket numbers.
         */
        return TABLE_ERROR_NOT_FOUND;
    }

    /* find the entry which is the nth in the list */
    for (entry_c = linear_p->tl_entry_c,
         entry_p = table_p->ta_buckets[linear_p->tl_bucket_c];
         entry_p != NULL && entry_c > 0;
         entry_c--, entry_p = TABLE_POINTER(table_p, table_entry_t *,
                                            entry_p)->te_next_p) {
    }

    if (entry_p == NULL)
        return TABLE_ERROR_NOT_FOUND;
    if (key_buf_p != NULL)
        *key_buf_p = ENTRY_KEY_BUF(entry_p);
    if (key_size_p != NULL)
        *key_size_p = entry_p->te_key_size;
    if (data_buf_p != NULL) {
        if (entry_p->te_data_size == 0)
            *data_buf_p = NULL;
        else {
            if (table_p->ta_data_align == 0)
                *data_buf_p = ENTRY_DATA_BUF(table_p, entry_p);
            else
                *data_buf_p = entry_data_buf(table_p, entry_p);
        }
    }
    if (data_size_p != NULL)
        *data_size_p = entry_p->te_data_size;
    return TABLE_ERROR_NONE;
}