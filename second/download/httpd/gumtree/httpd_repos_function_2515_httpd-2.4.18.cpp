apr_status_t h2_io_out_write(h2_io *io, apr_bucket_brigade *bb, 
                             apr_size_t maxlen, apr_table_t *trailers,
                             int *pfile_handles_allowed)
{
    apr_status_t status;
    int start_allowed;
    
    if (io->rst_error) {
        return APR_ECONNABORTED;
    }

    if (io->eos_out) {
        apr_off_t len;
        /* We have already delivered an EOS bucket to a reader, no
         * sense in storing anything more here.
         */
        status = apr_brigade_length(bb, 1, &len);
        if (status == APR_SUCCESS) {
            if (len > 0) {
                /* someone tries to write real data after EOS, that
                 * does not look right. */
                status = APR_EOF;
            }
            /* cleanup, as if we had moved the data */
            apr_brigade_cleanup(bb);
        }
        return status;
    }

    process_trailers(io, trailers);
    if (!io->bbout) {
        io->bbout = apr_brigade_create(io->pool, io->bucket_alloc);
    }
    
    /* Let's move the buckets from the request processing in here, so
     * that the main thread can read them when it has time/capacity.
     *
     * Move at most "maxlen" memory bytes. If buckets remain, it is
     * the caller's responsibility to take care of this.
     *
     * We allow passing of file buckets as long as we do not have too
     * many open files already buffered. Otherwise we will run out of
     * file handles.
     */
    start_allowed = *pfile_handles_allowed;
    status = h2_util_move(io->bbout, bb, maxlen, pfile_handles_allowed, 
                          "h2_io_out_write");
    /* track # file buckets moved into our pool */
    if (start_allowed != *pfile_handles_allowed) {
        io->files_handles_owned += (start_allowed - *pfile_handles_allowed);
    }
    return status;
}