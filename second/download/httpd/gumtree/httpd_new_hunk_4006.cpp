        /*
         * If we see an EOC bucket it is a signal that we should get out
         * of the way doing nothing.
         */
        if (AP_BUCKET_IS_EOC(b)) {
            ap_remove_output_filter(f);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, f->c,
                          "h2_from_h1(%d): eoc bucket passed", 
                          from_h1->stream_id);
            return ap_pass_brigade(f->next, bb);
        }
    }
    
    if (eb) {
        int st = eb->status;
        apr_brigade_cleanup(bb);
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c, APLOGNO(03047)
                      "h2_from_h1(%d): err bucket status=%d", 
                      from_h1->stream_id, st);
        ap_die(st, r);
        return AP_FILTER_ERROR;
    }
    
    from_h1->response = create_response(from_h1, r);
    if (from_h1->response == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_NOTICE, 0, f->c, APLOGNO(03048)
                      "h2_from_h1(%d): unable to create response", 
                      from_h1->stream_id);
        return APR_ENOMEM;
    }
    
    if (r->header_only) {
