static apr_status_t h2_filter_slave_in(ap_filter_t* f,
                                       apr_bucket_brigade* bb,
                                       ap_input_mode_t mode,
                                       apr_read_type_e block,
                                       apr_off_t readbytes)
{
    h2_task *task;
    apr_status_t status = APR_SUCCESS;
    apr_bucket *b, *next;
    apr_off_t bblen;
    const int trace1 = APLOGctrace1(f->c);
    apr_size_t rmax = ((readbytes <= APR_SIZE_MAX)? 
                       (apr_size_t)readbytes : APR_SIZE_MAX);
    
    task = h2_ctx_cget_task(f->c);
    ap_assert(task);

    if (trace1) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                      "h2_slave_in(%s): read, mode=%d, block=%d, readbytes=%ld", 
                      task->id, mode, block, (long)readbytes);
    }
    
    if (mode == AP_MODE_INIT) {
        return ap_get_brigade(f->c->input_filters, bb, mode, block, readbytes);
    }
    
    if (f->c->aborted) {
        return APR_ECONNABORTED;
    }
    
    if (!task->input.bb) {
        return APR_EOF;
    }
    
    /* Cleanup brigades from those nasty 0 length non-meta buckets
     * that apr_brigade_split_line() sometimes produces. */
    for (b = APR_BRIGADE_FIRST(task->input.bb);
         b != APR_BRIGADE_SENTINEL(task->input.bb); b = next) {
        next = APR_BUCKET_NEXT(b);
        if (b->length == 0 && !APR_BUCKET_IS_METADATA(b)) {
            apr_bucket_delete(b);
        } 
    }
    
    while (APR_BRIGADE_EMPTY(task->input.bb)) {
        /* Get more input data for our request. */
        if (trace1) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                          "h2_slave_in(%s): get more data from mplx, block=%d, "
                          "readbytes=%ld", task->id, block, (long)readbytes);
        }
        if (task->input.beam) {
            status = h2_beam_receive(task->input.beam, task->input.bb, block, 
                                     128*1024);
        }
        else {
            status = APR_EOF;
        }
        
        if (trace1) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, f->c,
                          "h2_slave_in(%s): read returned", task->id);
        }
        if (APR_STATUS_IS_EAGAIN(status) 
            && (mode == AP_MODE_GETLINE || block == APR_BLOCK_READ)) {
            /* chunked input handling does not seem to like it if we
             * return with APR_EAGAIN from a GETLINE read... 
             * upload 100k test on test-ser.example.org hangs */
            status = APR_SUCCESS;
        }
        else if (APR_STATUS_IS_EOF(status)) {
            break;
        }
        else if (status != APR_SUCCESS) {
            return status;
        }

        if (trace1) {
            h2_util_bb_log(f->c, task->stream_id, APLOG_TRACE2, 
                        "input.beam recv raw", task->input.bb);
        }
        if (h2_task_logio_add_bytes_in) {
            apr_brigade_length(bb, 0, &bblen);
            h2_task_logio_add_bytes_in(f->c, bblen);
        }
    }
    
    /* Nothing there, no more data to get. Return APR_EAGAIN on
     * speculative reads, this is ap_check_pipeline()'s trick to
     * see if the connection needs closing. */
    if (status == APR_EOF && APR_BRIGADE_EMPTY(task->input.bb)) {
        return (mode == AP_MODE_SPECULATIVE)? APR_EAGAIN : APR_EOF;
    }

    if (trace1) {
        h2_util_bb_log(f->c, task->stream_id, APLOG_TRACE2, 
                    "task_input.bb", task->input.bb);
    }
           
    if (APR_BRIGADE_EMPTY(task->input.bb)) {
        if (trace1) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                          "h2_slave_in(%s): no data", task->id);
        }
        return (block == APR_NONBLOCK_READ)? APR_EAGAIN : APR_EOF;
    }
    
    if (mode == AP_MODE_EXHAUSTIVE) {
        /* return all we have */
        APR_BRIGADE_CONCAT(bb, task->input.bb);
    }
    else if (mode == AP_MODE_READBYTES) {
        status = h2_brigade_concat_length(bb, task->input.bb, rmax);
    }
    else if (mode == AP_MODE_SPECULATIVE) {
        status = h2_brigade_copy_length(bb, task->input.bb, rmax);
    }
    else if (mode == AP_MODE_GETLINE) {
        /* we are reading a single LF line, e.g. the HTTP headers. 
         * this has the nasty side effect to split the bucket, even
         * though it ends with CRLF and creates a 0 length bucket */
        status = apr_brigade_split_line(bb, task->input.bb, block, 
                                        HUGE_STRING_LEN);
        if (APLOGctrace1(f->c)) {
            char buffer[1024];
            apr_size_t len = sizeof(buffer)-1;
            apr_brigade_flatten(bb, buffer, &len);
            buffer[len] = 0;
            if (trace1) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                              "h2_slave_in(%s): getline: %s",
                              task->id, buffer);
            }
        }
    }
    else {
        /* Hmm, well. There is mode AP_MODE_EATCRLF, but we chose not
         * to support it. Seems to work. */
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOTIMPL, f->c,
                      APLOGNO(03472) 
                      "h2_slave_in(%s), unsupported READ mode %d", 
                      task->id, mode);
        status = APR_ENOTIMPL;
    }
    
    if (trace1) {
        apr_brigade_length(bb, 0, &bblen);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                      "h2_slave_in(%s): %ld data bytes", task->id, (long)bblen);
    }
    return status;
}