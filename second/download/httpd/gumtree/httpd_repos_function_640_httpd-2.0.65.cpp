int table_retrieve(table_t * table_p,
                   const void *key_buf, const int key_size,
                   void **data_buf_p, int *data_size_p)
{
    int bucket;
    unsigned int ksize;
    table_entry_t *entry_p, **buckets;

    if (table_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (table_p->ta_magic != TABLE_MAGIC)
        return TABLE_ERROR_PNT;
    if (key_buf == NULL)
        return TABLE_ERROR_ARG_NULL;
    /* find key size */
    if (key_size < 0)
        ksize = strlen((char *) key_buf) + sizeof(char);
    else
        ksize = key_size;
    /* get the bucket number via a has function */
    bucket = hash(key_buf, ksize, 0) % table_p->ta_bucket_n;

    /* look for the entry in this bucket, only check keys of the same size */
    buckets = table_p->ta_buckets;
    for (entry_p = buckets[bucket];
         entry_p != NULL;
         entry_p = entry_p->te_next_p) {
        entry_p = TABLE_POINTER(table_p, table_entry_t *, entry_p);
        if (entry_p->te_key_size == ksize
            && memcmp(ENTRY_KEY_BUF(entry_p), key_buf, ksize) == 0)
            break;
    }

    /* not found? */
    if (entry_p == NULL)
        return TABLE_ERROR_NOT_FOUND;
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