static apr_status_t odbc_create_bucket(const apr_dbd_row_t *row, const int col, 
                                       SQLSMALLINT type, apr_bucket_brigade *bb)
{
    apr_bucket_alloc_t *list = bb->bucket_alloc;
    apr_bucket *b = apr_bucket_alloc(sizeof(*b), list);
    odbc_bucket *bd = apr_bucket_alloc(sizeof(odbc_bucket), list);
    apr_bucket *eos = apr_bucket_eos_create(list);
    
    bd->row = row;
    bd->col = col;
    bd->type = type;

    APR_BUCKET_INIT(b);
    b->type = &odbc_bucket_type;
    b->free = apr_bucket_free;
    b->list = list;
    /* LOB lengths are unknown in ODBC */
    b = apr_bucket_shared_make(b, bd, 0, -1);

    APR_BRIGADE_INSERT_TAIL(bb, b);
    APR_BRIGADE_INSERT_TAIL(bb, eos);

    return APR_SUCCESS;
}