static apr_status_t mplx_transfer(h2_sos_mplx *msos, int stream_id, 
                                  apr_pool_t *pool)
{
    apr_status_t status;
    apr_table_t *trailers = NULL;
    
    if (!msos->tmp) {
        msos->tmp = apr_brigade_create(msos->bb->p, msos->bb->bucket_alloc);
    }
    status = h2_mplx_out_get_brigade(msos->m, stream_id, msos->tmp, 
                                     msos->buffer_size-1, &trailers);
    if (!APR_BRIGADE_EMPTY(msos->tmp)) {
        h2_transfer_brigade(msos->bb, msos->tmp, pool);
    }
    if (trailers) {
        msos->trailers = trailers;
    }
    return status;
}