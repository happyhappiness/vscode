static apr_status_t lob_bucket_read(apr_bucket *e, const char **str,
                                    apr_size_t *len, apr_read_type_e block)
{
    apr_bucket_lob *a = e->data;
    const apr_dbd_row_t *row = a->row;
    apr_dbd_results_t *res = row->res;
    int col = a->col;
    apr_bucket *b = NULL;
    int rv;
    apr_size_t blength = e->length;  /* bytes remaining in file past offset */
    apr_off_t boffset = e->start;
    MYSQL_BIND *bind = &res->bind[col];

    *str = NULL;  /* in case we die prematurely */

    /* fetch from offset if not at the beginning */
    if (boffset > 0) {
        rv = mysql_stmt_fetch_column(res->statement, bind, col,
                                     (unsigned long) boffset);
        if (rv != 0) {
            return APR_EGENERAL;
        }
    }
    blength -= blength > bind->buffer_length ? bind->buffer_length : blength;
    *len = e->length - blength;
    *str = bind->buffer;

    /* allocate new buffer, since we used this one for the bucket */
    bind->buffer = apr_palloc(res->pool, bind->buffer_length);

    /*
     * Change the current bucket to refer to what we read,
     * even if we read nothing because we hit EOF.
     */
    apr_bucket_pool_make(e, *str, *len, res->pool);

    /* If we have more to read from the field, then create another bucket */
    if (blength > 0) {
        /* for efficiency, we can just build a new apr_bucket struct
         * to wrap around the existing LOB bucket */
        b = apr_bucket_alloc(sizeof(*b), e->list);
        b->start  = boffset + *len;
        b->length = blength;
        b->data   = a;
        b->type   = &apr_bucket_type_lob;
        b->free   = apr_bucket_free;
        b->list   = e->list;
        APR_BUCKET_INSERT_AFTER(e, b);
    }
    else {
        lob_bucket_destroy(a);
    }

    return APR_SUCCESS;
}