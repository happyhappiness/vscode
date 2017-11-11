int table_delete_first(table_t * table_p,
                       void **key_buf_p, int *key_size_p,
                       void **data_buf_p, int *data_size_p)
{
    unsigned char *data_copy_p;
    table_entry_t *entry_p;
    table_linear_t linear;

    if (table_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (table_p->ta_magic != TABLE_MAGIC)
        return TABLE_ERROR_PNT;
    /* take the first entry */
    entry_p = first_entry(table_p, &linear);
    if (entry_p == NULL)
        return TABLE_ERROR_NOT_FOUND;
    /*
     * NOTE: we may want to adjust the linear counters here if the entry
     * we are deleting is the one we are pointing on or is ahead of the
     * one in the bucket list
     */

    /* remove entry from the linked list */
    table_p->ta_buckets[linear.tl_bucket_c] = entry_p->te_next_p;

    /* free entry */
    if (key_buf_p != NULL) {
        if (entry_p->te_key_size == 0)
            *key_buf_p = NULL;
        else {
            /*
             * if we were storing it compacted, we now need to malloc some
             * space if the user wants the value after the delete.
             */
            *key_buf_p = table_p->ta_malloc(table_p->opt_param,
                                            entry_p->te_key_size);
            if (*key_buf_p == NULL)
                return TABLE_ERROR_ALLOC;
            memcpy(*key_buf_p, ENTRY_KEY_BUF(entry_p), entry_p->te_key_size);
        }
    }
    if (key_size_p != NULL)
        *key_size_p = entry_p->te_key_size;
    if (data_buf_p != NULL) {
        if (entry_p->te_data_size == 0)
            *data_buf_p = NULL;
        else {
            /*
             * if we were storing it compacted, we now need to malloc some
             * space if the user wants the value after the delete.
             */
            *data_buf_p = table_p->ta_malloc(table_p->opt_param,
                                             entry_p->te_data_size);
            if (*data_buf_p == NULL)
                return TABLE_ERROR_ALLOC;
            if (table_p->ta_data_align == 0)
                data_copy_p = ENTRY_DATA_BUF(table_p, entry_p);
            else
                data_copy_p = entry_data_buf(table_p, entry_p);
            memcpy(*data_buf_p, data_copy_p, entry_p->te_data_size);
        }
    }
    if (data_size_p != NULL)
        *data_size_p = entry_p->te_data_size;
    table_p->ta_free(table_p->opt_param, entry_p);

    table_p->ta_entry_n--;

    /* do we need auto-adjust down? */
    if ((table_p->ta_flags & TABLE_FLAG_AUTO_ADJUST)
        && (table_p->ta_flags & TABLE_FLAG_ADJUST_DOWN)
        && SHOULD_TABLE_SHRINK(table_p))
        return table_adjust(table_p, table_p->ta_entry_n);
    return TABLE_ERROR_NONE;
}