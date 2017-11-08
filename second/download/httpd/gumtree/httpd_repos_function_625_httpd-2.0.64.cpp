static table_entry_t *next_entry(table_t * table_p, table_linear_t * linear_p,
                                 int *error_p)
{
    table_entry_t *entry_p;
    int entry_c;

    /* can't next if we haven't first-ed */
    if (linear_p == NULL) {
        if (error_p != NULL)
            *error_p = TABLE_ERROR_LINEAR;
        return NULL;
    }

    if (linear_p->tl_bucket_c >= table_p->ta_bucket_n) {
        /*
         * NOTE: this might happen if we delete an item which shortens the
         * table bucket numbers.
         */
        if (error_p != NULL)
            *error_p = TABLE_ERROR_NOT_FOUND;
        return NULL;
    }

    linear_p->tl_entry_c++;

    /* find the entry which is the nth in the list */
    entry_p = table_p->ta_buckets[linear_p->tl_bucket_c];
    /* NOTE: we swap the order here to be more efficient */
    for (entry_c = linear_p->tl_entry_c; entry_c > 0; entry_c--) {
        /* did we reach the end of the list? */
        if (entry_p == NULL)
            break;
        entry_p = TABLE_POINTER(table_p, table_entry_t *, entry_p)->te_next_p;
    }

    /* did we find an entry in the current bucket? */
    if (entry_p != NULL) {
        if (error_p != NULL)
            *error_p = TABLE_ERROR_NONE;
        return TABLE_POINTER(table_p, table_entry_t *, entry_p);
    }

    /* find the first entry in the next non-empty bucket */

    linear_p->tl_entry_c = 0;
    for (linear_p->tl_bucket_c++; linear_p->tl_bucket_c < table_p->ta_bucket_n;
         linear_p->tl_bucket_c++) {
        entry_p = table_p->ta_buckets[linear_p->tl_bucket_c];
        if (entry_p != NULL) {
            if (error_p != NULL)
                *error_p = TABLE_ERROR_NONE;
            return TABLE_POINTER(table_p, table_entry_t *, entry_p);
        }
    }

    if (error_p != NULL)
        *error_p = TABLE_ERROR_NOT_FOUND;
    return NULL;
}