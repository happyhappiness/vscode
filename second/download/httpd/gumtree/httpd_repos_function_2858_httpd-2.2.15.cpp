static apr_status_t lob_bucket_read(apr_bucket *e, const char **str,
                                    apr_size_t *len, apr_read_type_e block)
{
    apr_bucket_lob *a = e->data;
    const apr_dbd_row_t *row = a->row;
    apr_dbd_results_t *res = row->res;
    int col = a->col;
    apr_bucket *b = NULL;
    apr_size_t blength = e->length;  /* bytes remaining in file past offset */
    apr_off_t boffset = e->start;
    define_arg *val = &res->statement->out[col];
    apr_dbd_t *sql = res->handle;
/* Only with 10g, unfortunately
    oraub8 length = APR_BUCKET_BUFF_SIZE;
*/
    ub4 length = APR_BUCKET_BUFF_SIZE;
    char *buf = NULL;

    *str = NULL;  /* in case we die prematurely */

    /* fetch from offset if not at the beginning */
    buf = apr_palloc(row->pool, APR_BUCKET_BUFF_SIZE);
    sql->status = OCILobRead(sql->svc, sql->err, val->buf.lobval,
                             &length, 1 + (size_t)boffset,
                             (dvoid*) buf, APR_BUCKET_BUFF_SIZE,
                             NULL, NULL, 0, SQLCS_IMPLICIT);
/* Only with 10g, unfortunately
    sql->status = OCILobRead2(sql->svc, sql->err, val->buf.lobval,
                              &length, NULL, 1 + boffset,
                              (dvoid*) buf, APR_BUCKET_BUFF_SIZE,
                              OCI_ONE_PIECE, NULL, NULL, 0, SQLCS_IMPLICIT);
*/
    if (sql->status != OCI_SUCCESS) {
        return APR_EGENERAL;
    }
    blength -= length;
    *len = length;
    *str = buf;

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