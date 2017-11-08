static apr_status_t odbc_lob_bucket_setaside(apr_bucket *e, apr_pool_t *pool)
{
    odbc_bucket *bd = (odbc_bucket *)e->data;

    /* Unlikely - but if the row pool is ancestor of this pool then it is OK */
    if (apr_pool_is_ancestor(bd->row->pool, pool))
        return APR_SUCCESS;
    
    return apr_bucket_setaside_notimpl(e, pool);
}