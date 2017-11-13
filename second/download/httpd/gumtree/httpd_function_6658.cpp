static apr_status_t input_read(h2_task *task, ap_filter_t* f,
                               apr_bucket_brigade* bb, ap_input_mode_t mode,
                               apr_read_type_e block, apr_off_t readbytes)
{
    apr_status_t status = APR_SUCCESS;
    apr_bucket *b, *next, *first_data;
    apr_off_t bblen = 0;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                  "h2_task(%s): read, mode=%d, block=%d, readbytes=%ld", 
                  task->id, mode, block, (long)readbytes);
    
    if (mode == AP_MODE_INIT) {
        return ap_get_brigade(f->c->input_filters, bb, mode, block, readbytes);
    }
    
    if (f->c->aborted || !task->request) {
        return APR_ECONNABORTED;
    }
    
    if (!task->input.bb) {
        if (!task->input.eos_written) {
            input_append_eos(task, f->r);
            return APR_SUCCESS;
        }
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
    
    while (APR_BRIGADE_EMPTY(task->input.bb) && !task->input.eos) {
        /* Get more input data for our request. */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                      "h2_task(%s): get more data from mplx, block=%d, "
                      "readbytes=%ld, queued=%ld",
                      task->id, block, (long)readbytes, (long)bblen);
        
        /* Override the block mode we get called with depending on the input's
         * setting. */
        if (task->input.beam) {
            status = h2_beam_receive(task->input.beam, task->input.bb, block, 
                                     H2MIN(readbytes, 32*1024));
        }
        else {
            status = APR_EOF;
        }
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, f->c,
                      "h2_task(%s): read returned", task->id);
        if (APR_STATUS_IS_EAGAIN(status) 
            && (mode == AP_MODE_GETLINE || block == APR_BLOCK_READ)) {
            /* chunked input handling does not seem to like it if we
             * return with APR_EAGAIN from a GETLINE read... 
             * upload 100k test on test-ser.example.org hangs */
            status = APR_SUCCESS;
        }
        else if (APR_STATUS_IS_EOF(status)) {
            task->input.eos = 1;
        }
        else if (status != APR_SUCCESS) {
            return status;
        }
        
        /* Inspect the buckets received, detect EOS and apply
         * chunked encoding if necessary */
        h2_util_bb_log(f->c, task->stream_id, APLOG_TRACE2, 
                       "input.beam recv raw", task->input.bb);
        first_data = NULL;
        bblen = 0;
        for (b = APR_BRIGADE_FIRST(task->input.bb); 
             b != APR_BRIGADE_SENTINEL(task->input.bb); b = next) {
            next = APR_BUCKET_NEXT(b);
            if (APR_BUCKET_IS_METADATA(b)) {
                if (first_data && task->input.chunked) {
                    make_chunk(task, task->input.bb, first_data, bblen, b);
                    first_data = NULL;
                    bblen = 0;
                }
                if (APR_BUCKET_IS_EOS(b)) {
                    task->input.eos = 1;
                    input_handle_eos(task, f->r, b);
                    h2_util_bb_log(f->c, task->stream_id, APLOG_TRACE2, 
                                   "input.bb after handle eos", 
                                   task->input.bb);
                }
            }
            else if (b->length == 0) {
                apr_bucket_delete(b);
            } 
            else {
                if (!first_data) {
                    first_data = b;
                }
                bblen += b->length;
            }    
        }
        if (first_data && task->input.chunked) {
            make_chunk(task, task->input.bb, first_data, bblen, NULL);
        }            
        
        if (h2_task_logio_add_bytes_in) {
            h2_task_logio_add_bytes_in(f->c, bblen);
        }
    }
    
    if (task->input.eos) {
        if (!task->input.eos_written) {
            input_append_eos(task, f->r);
        }
        if (APR_BRIGADE_EMPTY(task->input.bb)) {
            return APR_EOF;
        }
    }

    h2_util_bb_log(f->c, task->stream_id, APLOG_TRACE2, 
                   "task_input.bb", task->input.bb);
           
    if (APR_BRIGADE_EMPTY(task->input.bb)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                      "h2_task(%s): no data", task->id);
        return (block == APR_NONBLOCK_READ)? APR_EAGAIN : APR_EOF;
    }
    
    if (mode == AP_MODE_EXHAUSTIVE) {
        /* return all we have */
        APR_BRIGADE_CONCAT(bb, task->input.bb);
    }
    else if (mode == AP_MODE_READBYTES) {
        status = h2_brigade_concat_length(bb, task->input.bb, readbytes);
    }
    else if (mode == AP_MODE_SPECULATIVE) {
        status = h2_brigade_copy_length(bb, task->input.bb, readbytes);
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
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                          "h2_task(%s): getline: %s",
                          task->id, buffer);
        }
    }
    else {
        /* Hmm, well. There is mode AP_MODE_EATCRLF, but we chose not
         * to support it. Seems to work. */
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOTIMPL, f->c,
                      APLOGNO(02942) 
                      "h2_task, unsupported READ mode %d", mode);
        status = APR_ENOTIMPL;
    }
    
    if (APLOGctrace1(f->c)) {
        apr_brigade_length(bb, 0, &bblen);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                      "h2_task(%s): return %ld data bytes",
                      task->id, (long)bblen);
    }
    return status;
}