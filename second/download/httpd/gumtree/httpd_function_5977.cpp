static apr_status_t h2_conn_io_bucket_read(h2_conn_io *io,
                                           apr_read_type_e block,
                                           h2_conn_io_on_read_cb on_read_cb,
                                           void *puser, int *pdone)
{
    apr_status_t status = APR_SUCCESS;
    apr_size_t readlen = 0;
    *pdone = 0;
    
    while (status == APR_SUCCESS && !*pdone
           && !APR_BRIGADE_EMPTY(io->input)) {
        
        apr_bucket* bucket = APR_BRIGADE_FIRST(io->input);
        if (APR_BUCKET_IS_METADATA(bucket)) {
            /* we do nothing regarding any meta here */
        }
        else {
            const char *bucket_data = NULL;
            apr_size_t bucket_length = 0;
            status = apr_bucket_read(bucket, &bucket_data,
                                     &bucket_length, block);
            
            if (status == APR_SUCCESS && bucket_length > 0) {
                apr_size_t consumed = 0;

                if (APLOGctrace2(io->connection)) {
                    char buffer[32];
                    h2_util_hex_dump(buffer, sizeof(buffer)/sizeof(buffer[0]),
                                     bucket_data, bucket_length);
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, io->connection,
                                  "h2_conn_io(%ld): read %d bytes: %s",
                                  io->connection->id, (int)bucket_length, buffer);
                }
                
                status = on_read_cb(bucket_data, bucket_length, &consumed, 
                                    pdone, puser);
                if (status == APR_SUCCESS && bucket_length > consumed) {
                    /* We have data left in the bucket. Split it. */
                    status = apr_bucket_split(bucket, consumed);
                }
                readlen += consumed;
            }
        }
        apr_bucket_delete(bucket);
    }
    
    if (readlen == 0 && status == APR_SUCCESS && block == APR_NONBLOCK_READ) {
        return APR_EAGAIN;
    }
    return status;
}