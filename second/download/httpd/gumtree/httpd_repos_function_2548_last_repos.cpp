static apr_status_t recv_RAW_brigade(conn_rec *c, h2_filter_cin *cin, 
                                     apr_bucket_brigade *bb, 
                                     apr_read_type_e block)
{
    apr_status_t status = APR_SUCCESS;
    apr_bucket* b;
    int consumed = 0;
    
    h2_util_bb_log(c, c->id, APLOG_TRACE2, "RAW_in", bb);
    while (status == APR_SUCCESS && !APR_BRIGADE_EMPTY(bb)) {
        b = APR_BRIGADE_FIRST(bb);

        if (APR_BUCKET_IS_METADATA(b)) {
            /* nop */
        }
        else {
            status = recv_RAW_DATA(c, cin, b, block);
        }
        consumed = 1;
        apr_bucket_delete(b);
    }
    
    if (!consumed && status == APR_SUCCESS && block == APR_NONBLOCK_READ) {
        return APR_EAGAIN;
    }
    return status;
}