apr_status_t h2_io_out_write(h2_io *io, apr_bucket_brigade *bb, 
                             apr_size_t maxlen, 
                             apr_size_t *pfile_buckets_allowed)
{
    apr_status_t status;
    apr_bucket *b;
    int start_allowed;
    
    if (io->rst_error) {
        return APR_ECONNABORTED;
    }

    /* Filter the EOR bucket and set it aside. We prefer to tear down
     * the request when the whole h2 stream is done */
    for (b = APR_BRIGADE_FIRST(bb);
         b != APR_BRIGADE_SENTINEL(bb);
         b = APR_BUCKET_NEXT(b))
    {
        if (AP_BUCKET_IS_EOR(b)) {
            APR_BUCKET_REMOVE(b);
            io->eor = b;
            break;
        }
        else if (APR_BUCKET_IS_EOS(b)) {
            io->eos_out = 1;
            break;
        }
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
    check_bbout(io);
    start_allowed = *pfile_buckets_allowed;
    status = h2_util_move(io->bbout, bb, maxlen, pfile_buckets_allowed, 
                          "h2_io_out_write");
    /* track # file buckets moved into our pool */
    if (start_allowed != *pfile_buckets_allowed) {
        io->files_handles_owned += (start_allowed - *pfile_buckets_allowed);
    }
    return status;
}