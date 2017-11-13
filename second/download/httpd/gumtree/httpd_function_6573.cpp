apr_status_t h2_filter_request_in(ap_filter_t* f,
                                  apr_bucket_brigade* bb,
                                  ap_input_mode_t mode,
                                  apr_read_type_e block,
                                  apr_off_t readbytes)
{
    h2_task *task = f->ctx;
    request_rec *r = f->r;
    apr_status_t status = APR_SUCCESS;
    apr_bucket *b, *next;

    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, f->r,
                  "h2_task(%s): request filter, exp=%d", task->id, r->expecting_100);
    if (!task->request->chunked) {
        status = ap_get_brigade(f->next, bb, mode, block, readbytes);
        /* pipe data through, just take care of trailers */
        for (b = APR_BRIGADE_FIRST(bb); 
             b != APR_BRIGADE_SENTINEL(bb); b = next) {
            next = APR_BUCKET_NEXT(b);
            if (H2_BUCKET_IS_HEADERS(b)) {
                h2_headers *headers = h2_bucket_headers_get(b);
                ap_assert(headers);
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "h2_task(%s): receiving trailers", task->id);
                r->trailers_in = apr_table_clone(r->pool, headers->headers);
                APR_BUCKET_REMOVE(b);
                apr_bucket_destroy(b);
                ap_remove_input_filter(f);
                break;
            }
        }
        return status;
    }

    /* Things are more complicated. The standard HTTP input filter, which
     * does a lot what we do not want to duplicate, also cares about chunked
     * transfer encoding and trailers.
     * We need to simulate chunked encoding for it to be happy.
     */
    if ((status = read_and_chunk(f, task, block)) != APR_SUCCESS) {
        return status;
    }
    
    if (mode == AP_MODE_EXHAUSTIVE) {
        /* return all we have */
        APR_BRIGADE_CONCAT(bb, task->input.bbchunk);
    }
    else if (mode == AP_MODE_READBYTES) {
        status = h2_brigade_concat_length(bb, task->input.bbchunk, readbytes);
    }
    else if (mode == AP_MODE_SPECULATIVE) {
        status = h2_brigade_copy_length(bb, task->input.bbchunk, readbytes);
    }
    else if (mode == AP_MODE_GETLINE) {
        /* we are reading a single LF line, e.g. the HTTP headers. 
         * this has the nasty side effect to split the bucket, even
         * though it ends with CRLF and creates a 0 length bucket */
        status = apr_brigade_split_line(bb, task->input.bbchunk, block, 
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
    
    h2_util_bb_log(f->c, task->stream_id, APLOG_TRACE2, "forwarding input", bb);
    return status;
}