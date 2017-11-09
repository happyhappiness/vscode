static apr_status_t append_bucket(h2_bucket_beam *beam, 
                                  apr_bucket *b,
                                  apr_read_type_e block,
                                  h2_beam_lock *pbl)
{
    const char *data;
    apr_size_t len;
    apr_size_t space_left = 0;
    apr_status_t status;
    
    if (APR_BUCKET_IS_METADATA(b)) {
        if (APR_BUCKET_IS_EOS(b)) {
            beam->closed = 1;
        }
        APR_BUCKET_REMOVE(b);
        H2_BLIST_INSERT_TAIL(&beam->send_list, b);
        return APR_SUCCESS;
    }
    else if (APR_BUCKET_IS_FILE(b)) {
        /* file bucket lengths do not really count */
    }
    else {
        space_left = calc_space_left(beam);
        if (space_left > 0 && b->length == ((apr_size_t)-1)) {
            const char *data;
            status = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
            if (status != APR_SUCCESS) {
                return status;
            }
        }
        
        if (space_left <= 0) {
            status = r_wait_space(beam, block, pbl, &space_left);
            if (status != APR_SUCCESS) {
                return status;
            }
            if (space_left <= 0) {
                return APR_EAGAIN;
            }
        }
        /* space available, maybe need bucket split */
    }
    

    /* The fundamental problem is that reading a sender bucket from
     * a receiver thread is a total NO GO, because the bucket might use
     * its pool/bucket_alloc from a foreign thread and that will
     * corrupt. */
    status = APR_ENOTIMPL;
    if (APR_BUCKET_IS_TRANSIENT(b)) {
        /* this takes care of transient buckets and converts them
         * into heap ones. Other bucket types might or might not be
         * affected by this. */
        status = apr_bucket_setaside(b, beam->send_pool);
    }
    else if (APR_BUCKET_IS_HEAP(b)) {
        /* For heap buckets read from a receiver thread is fine. The
         * data will be there and live until the bucket itself is
         * destroyed. */
        status = APR_SUCCESS;
    }
    else if (APR_BUCKET_IS_POOL(b)) {
        /* pool buckets are bastards that register at pool cleanup
         * to morph themselves into heap buckets. That may happen anytime,
         * even after the bucket data pointer has been read. So at
         * any time inside the receiver thread, the pool bucket memory
         * may disappear. yikes. */
        status = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
        if (status == APR_SUCCESS) {
            apr_bucket_heap_make(b, data, len, NULL);
        }
    }
    else if (APR_BUCKET_IS_FILE(b)) {
        /* For file buckets the problem is their internal readpool that
         * is used on the first read to allocate buffer/mmap.
         * Since setting aside a file bucket will de-register the
         * file cleanup function from the previous pool, we need to
         * call that only from the sender thread.
         *
         * Currently, we do not handle file bucket with refcount > 1 as
         * the beam is then not in complete control of the file's lifetime.
         * Which results in the bug that a file get closed by the receiver
         * while the sender or the beam still have buckets using it. 
         * 
         * Additionally, we allow callbacks to prevent beaming file
         * handles across. The use case for this is to limit the number 
         * of open file handles and rather use a less efficient beam
         * transport. */
        apr_bucket_file *bf = b->data;
        apr_file_t *fd = bf->fd;
        int can_beam = (bf->refcount.refcount == 1);
        if (can_beam && beam->can_beam_fn) {
            can_beam = beam->can_beam_fn(beam->can_beam_ctx, beam, fd);
        }
        if (can_beam) {
            status = apr_bucket_setaside(b, beam->send_pool);
        }
        /* else: enter ENOTIMPL case below */
    }
    
    if (status == APR_ENOTIMPL) {
        /* we have no knowledge about the internals of this bucket,
         * but hope that after read, its data stays immutable for the
         * lifetime of the bucket. (see pool bucket handling above for
         * a counter example).
         * We do the read while in the sender thread, so that the bucket may
         * use pools/allocators safely. */
        if (space_left < APR_BUCKET_BUFF_SIZE) {
            space_left = APR_BUCKET_BUFF_SIZE;
        }
        if (space_left < b->length) {
            apr_bucket_split(b, space_left);
        }
        status = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
        if (status == APR_SUCCESS) {
            status = apr_bucket_setaside(b, beam->send_pool);
        }
    }
    
    if (status != APR_SUCCESS && status != APR_ENOTIMPL) {
        return status;
    }
    
    APR_BUCKET_REMOVE(b);
    H2_BLIST_INSERT_TAIL(&beam->send_list, b);
    beam->sent_bytes += b->length;
    
    return APR_SUCCESS;
}