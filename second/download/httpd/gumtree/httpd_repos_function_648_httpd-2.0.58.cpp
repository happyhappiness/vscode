int table_next_r(table_t * table_p, table_linear_t * linear_p,
                 void **key_buf_p, int *key_size_p,
                 void **data_buf_p, int *data_size_p)
{
    table_entry_t *entry_p;
    int error;

    if (table_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (table_p->ta_magic != TABLE_MAGIC)
        return TABLE_ERROR_PNT;
    if (linear_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (linear_p->tl_magic != LINEAR_MAGIC)
        return TABLE_ERROR_LINEAR;
    /* move to the next entry */
    entry_p = next_entry(table_p, linear_p, &error);
    if (entry_p == NULL)
        return error;
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