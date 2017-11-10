static apr_bucket *apr_bucket_lob_create(const apr_dbd_row_t *row, int col,
                                         apr_off_t offset,
                                         apr_size_t len, apr_pool_t *p,
                                         apr_bucket_alloc_t *list)
{
    apr_bucket *b = apr_bucket_alloc(sizeof(*b), list);

    APR_BUCKET_INIT(b);
    b->free = apr_bucket_free;
    b->list = list;
    return apr_bucket_lob_make(b, row, col, offset, len, p);
}