int table_this(table_t * table_p,
               void **key_buf_p, int *key_size_p,
               void **data_buf_p, int *data_size_p)
{
    table_entry_t *entry_p = NULL;
    int entry_c;

    if (table_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (table_p->ta_magic != TABLE_MAGIC)
        return TABLE_ERROR_PNT;
    if (table_p->ta_linear.tl_magic != LINEAR_MAGIC)
        return TABLE_ERROR_LINEAR;
    /* if we removed an item that shorted the bucket list, we may get this */
    if (table_p->ta_linear.tl_bucket_c >= table_p->ta_bucket_n) {
        /*
         * NOTE: this might happen if we delete an item which shortens the
         * table bucket numbers.
         */
        return TABLE_ERROR_NOT_FOUND;
    }

    /* find the entry which is the nth in the list */
    entry_p = table_p->ta_buckets[table_p->ta_linear.tl_bucket_c];
    /* NOTE: we swap the order here to be more efficient */
    for (entry_c = table_p->ta_linear.tl_entry_c; entry_c > 0; entry_c--) {
        /* did we reach the end of the list? */
        if (entry_p == NULL)
            break;
        entry_p = TABLE_POINTER(table_p, table_entry_t *, entry_p)->te_next_p;
    }

    /* is this a NOT_FOUND or a LINEAR error */
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