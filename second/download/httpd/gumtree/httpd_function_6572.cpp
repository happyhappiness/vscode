static apr_status_t read_and_chunk(ap_filter_t *f, h2_task *task,
                                   apr_read_type_e block) {
    request_rec *r = f->r;
    apr_status_t status = APR_SUCCESS;
    apr_bucket_brigade *bb = task->input.bbchunk;
    
    if (!bb) {
        bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
        task->input.bbchunk = bb;
    }
    
    if (APR_BRIGADE_EMPTY(bb)) {
        apr_bucket *b, *next, *first_data = NULL;
        apr_bucket_brigade *tmp;
        apr_off_t bblen = 0;

        /* get more data from the lower layer filters. Always do this
         * in larger pieces, since we handle the read modes ourself. */
        status = ap_get_brigade(f->next, bb, 
                                AP_MODE_READBYTES, block, 32*1024);
        if (status == APR_EOF) {
            if (!task->input.eos) {
                status = apr_brigade_puts(bb, NULL, NULL, "0\r\n\r\n");
                task->input.eos = 1;
                return APR_SUCCESS;
            }
            ap_remove_input_filter(f);
            return status;
            
        }
        else if (status != APR_SUCCESS) {
            return status;
        }

        for (b = APR_BRIGADE_FIRST(bb); 
             b != APR_BRIGADE_SENTINEL(bb) && !task->input.eos; 
             b = next) {
            next = APR_BUCKET_NEXT(b);
            if (APR_BUCKET_IS_METADATA(b)) {
                if (first_data) {
                    make_chunk(task, bb, first_data, bblen, b);
                    first_data = NULL;
                }
                
                if (H2_BUCKET_IS_HEADERS(b)) {
                    h2_headers *headers = h2_bucket_headers_get(b);
                    
                    ap_assert(headers);
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                                  "h2_task(%s): receiving trailers", task->id);
                    tmp = apr_brigade_split_ex(bb, b, NULL);
                    if (!apr_is_empty_table(headers->headers)) {
                        status = apr_brigade_puts(bb, NULL, NULL, "0\r\n");
                        apr_table_do(ser_header, bb, headers->headers, NULL);
                        status = apr_brigade_puts(bb, NULL, NULL, "\r\n");
                    }
                    else {
                        status = apr_brigade_puts(bb, NULL, NULL, "0\r\n\r\n");
                    }
                    r->trailers_in = apr_table_clone(r->pool, headers->headers);
                    APR_BUCKET_REMOVE(b);
                    apr_bucket_destroy(b);
                    APR_BRIGADE_CONCAT(bb, tmp);
                    apr_brigade_destroy(tmp);
                    task->input.eos = 1;
                }
                else if (APR_BUCKET_IS_EOS(b)) {
                    tmp = apr_brigade_split_ex(bb, b, NULL);
                    status = apr_brigade_puts(bb, NULL, NULL, "0\r\n\r\n");
                    APR_BRIGADE_CONCAT(bb, tmp);
                    apr_brigade_destroy(tmp);
                    task->input.eos = 1;
                }
            }
            else if (b->length == 0) {
                APR_BUCKET_REMOVE(b);
                apr_bucket_destroy(b);
            } 
            else {
                if (!first_data) {
                    first_data = b;
                    bblen = 0;
                }
                bblen += b->length;
            }    
        }
        
        if (first_data) {
            make_chunk(task, bb, first_data, bblen, NULL);
        }            
    }
    return status;
}