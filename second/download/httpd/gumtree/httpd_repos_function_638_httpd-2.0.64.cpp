int table_insert_kd(table_t * table_p,
                    const void *key_buf, const int key_size,
                    const void *data_buf, const int data_size,
                    void **key_buf_p, void **data_buf_p,
                    const char overwrite_b)
{
    int bucket;
    unsigned int ksize, dsize;
    table_entry_t *entry_p, *last_p;
    void *key_copy_p, *data_copy_p;

    /* check the arguments */
    if (table_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (table_p->ta_magic != TABLE_MAGIC)
        return TABLE_ERROR_PNT;
    if (key_buf == NULL)
        return TABLE_ERROR_ARG_NULL;
    /* data_buf can be null but size must be >= 0, if it isn't null size != 0 */
    if ((data_buf == NULL && data_size < 0)
        || (data_buf != NULL && data_size == 0))
        return TABLE_ERROR_SIZE;
    /* determine sizes of key and data */
    if (key_size < 0)
        ksize = strlen((char *) key_buf) + sizeof(char);
    else
        ksize = key_size;
    if (data_size < 0)
        dsize = strlen((char *) data_buf) + sizeof(char);
    else
        dsize = data_size;
    /* get the bucket number via a hash function */
    bucket = hash(key_buf, ksize, 0) % table_p->ta_bucket_n;

    /* look for the entry in this bucket, only check keys of the same size */
    last_p = NULL;
    for (entry_p = table_p->ta_buckets[bucket];
         (entry_p != NULL) && (entry_p->te_next_p != last_p);
         last_p = entry_p, entry_p = entry_p->te_next_p) {
        if (entry_p->te_key_size == ksize
            && memcmp(ENTRY_KEY_BUF(entry_p), key_buf, ksize) == 0)
            break;
    }

    /* did we find it?  then we are in replace mode. */
    if (entry_p != NULL) {

        /* can we not overwrite existing data? */
        if (!overwrite_b) {
            if (key_buf_p != NULL)
                *key_buf_p = ENTRY_KEY_BUF(entry_p);
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
            return TABLE_ERROR_OVERWRITE;
        }

        /* re-alloc entry's data if the new size != the old */
        if (dsize != entry_p->te_data_size) {

            /*
             * First we delete it from the list to keep the list whole.
             * This properly preserves the linked list in case we have a
             * thread marching through the linked list while we are
             * inserting.  Maybe this is an unnecessary protection but it
             * should not harm that much.
             */
            if (last_p == NULL)
                table_p->ta_buckets[bucket] = entry_p->te_next_p;
            else
                last_p->te_next_p = entry_p->te_next_p;
            /*
             * Realloc the structure which may change its pointer. NOTE:
             * this may change any previous data_key_p and data_copy_p
             * pointers.
             */
            entry_p = (table_entry_t *)
                       table_p->ta_realloc(table_p->opt_param, entry_p,
			     entry_size(table_p, entry_p->te_key_size, dsize));
            if (entry_p == NULL)
                return TABLE_ERROR_ALLOC;
            /* add it back to the front of the list */
            entry_p->te_data_size = dsize;
            entry_p->te_next_p = table_p->ta_buckets[bucket];
            table_p->ta_buckets[bucket] = entry_p;
        }

        /* copy or replace data in storage */
        if (dsize > 0) {
            if (table_p->ta_data_align == 0)
                data_copy_p = ENTRY_DATA_BUF(table_p, entry_p);
            else
                data_copy_p = entry_data_buf(table_p, entry_p);
            if (data_buf != NULL)
                memcpy(data_copy_p, data_buf, dsize);
        }
        else
            data_copy_p = NULL;
        if (key_buf_p != NULL)
            *key_buf_p = ENTRY_KEY_BUF(entry_p);
        if (data_buf_p != NULL)
            *data_buf_p = data_copy_p;
        /* returning from the section where we were overwriting table data */
        return TABLE_ERROR_NONE;
    }

    /*
     * It is a new entry.
     */

    /* allocate a new entry */
    entry_p = (table_entry_t *)
               table_p->ta_malloc(table_p->opt_param,
                                  entry_size(table_p, ksize, dsize));
    if (entry_p == NULL)
        return TABLE_ERROR_ALLOC;
    /* copy key into storage */
    entry_p->te_key_size = ksize;
    key_copy_p = ENTRY_KEY_BUF(entry_p);
    memcpy(key_copy_p, key_buf, ksize);

    /* copy data in */
    entry_p->te_data_size = dsize;
    if (dsize > 0) {
        if (table_p->ta_data_align == 0)
            data_copy_p = ENTRY_DATA_BUF(table_p, entry_p);
        else
            data_copy_p = entry_data_buf(table_p, entry_p);
        if (data_buf != NULL)
            memcpy(data_copy_p, data_buf, dsize);
    }
    else
        data_copy_p = NULL;
    if (key_buf_p != NULL)
        *key_buf_p = key_copy_p;
    if (data_buf_p != NULL)
        *data_buf_p = data_copy_p;
    /* insert into list, no need to append */
    entry_p->te_next_p = table_p->ta_buckets[bucket];
    table_p->ta_buckets[bucket] = entry_p;

    table_p->ta_entry_n++;

    /* do we need auto-adjust? */
    if (table_p->ta_flags & TABLE_FLAG_AUTO_ADJUST
        && SHOULD_TABLE_GROW(table_p))
        return table_adjust(table_p, table_p->ta_entry_n);
    return TABLE_ERROR_NONE;
}