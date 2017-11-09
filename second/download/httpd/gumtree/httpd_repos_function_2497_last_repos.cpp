apr_status_t h2_conn_io_pass(h2_conn_io *io, apr_bucket_brigade *bb)
{
    apr_bucket *b;
    apr_status_t status = APR_SUCCESS;
    
    if (!APR_BRIGADE_EMPTY(bb)) {
        io->is_flushed = 0;
    }

    while (!APR_BRIGADE_EMPTY(bb) && status == APR_SUCCESS) {
        b = APR_BRIGADE_FIRST(bb);
        
        if (APR_BUCKET_IS_METADATA(b)) {
            /* need to finish any open scratch bucket, as meta data 
             * needs to be forward "in order". */
            append_scratch(io);
            APR_BUCKET_REMOVE(b);
            APR_BRIGADE_INSERT_TAIL(io->output, b);
        }
        else if (io->buffer_output) {
            apr_size_t remain = assure_scratch_space(io);
            if (b->length > remain) {
                apr_bucket_split(b, remain);
                if (io->slen == 0) {
                    /* complete write_size bucket, append unchanged */
                    APR_BUCKET_REMOVE(b);
                    APR_BRIGADE_INSERT_TAIL(io->output, b);
                    continue;
                }
            }
            else {
                /* bucket fits in remain, copy to scratch */
                status = read_to_scratch(io, b);
                apr_bucket_delete(b);
                continue;
            }
        }
        else {
            /* no buffering, forward buckets setaside on flush */
            if (APR_BUCKET_IS_TRANSIENT(b)) {
                apr_bucket_setaside(b, io->c->pool);
            }
            APR_BUCKET_REMOVE(b);
            APR_BRIGADE_INSERT_TAIL(io->output, b);
        }
    }
    return status;
}