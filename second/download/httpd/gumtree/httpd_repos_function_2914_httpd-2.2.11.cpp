static apr_bucket *apr_bucket_lob_make(apr_bucket *b,
                                       const apr_dbd_row_t *row, int col,
                                       apr_off_t offset, apr_size_t len,
                                       apr_pool_t *p)
{
    apr_bucket_lob *f;

    f = apr_bucket_alloc(sizeof(*f), b->list);
    f->row = row;
    f->col = col;
    f->readpool = p;

    b = apr_bucket_shared_make(b, f, offset, len);
    b->type = &apr_bucket_type_lob;

    return b;
}