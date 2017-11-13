apr_status_t h2_response_output_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    h2_task *task = f->ctx;
    h2_from_h1 *from_h1 = task->output? task->output->from_h1 : NULL;
    request_rec *r = f->r;
    apr_bucket *b;
    ap_bucket_error *eb = NULL;

    AP_DEBUG_ASSERT(from_h1 != NULL);
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                  "h2_from_h1(%d): output_filter called", from_h1->stream_id);
    
    if (r->header_only && task->output && from_h1->response) {
        /* throw away any data after we have compiled the response */
        apr_brigade_cleanup(bb);
        return OK;
    }
    
    for (b = APR_BRIGADE_FIRST(bb);
         b != APR_BRIGADE_SENTINEL(bb);
         b = APR_BUCKET_NEXT(b))
    {
        if (AP_BUCKET_IS_ERROR(b) && !eb) {
            eb = b->data;
            continue;
        }
        /*
         * If we see an EOC bucket it is a signal that we should get out
         * of the way doing nothing.
         */
        if (AP_BUCKET_IS_EOC(b)) {
            ap_remove_output_filter(f);
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
                          "h2_from_h1(%d): eoc bucket passed", 
                          from_h1->stream_id);
            return ap_pass_brigade(f->next, bb);
        }
    }
    
    if (eb) {
        int st = eb->status;
        apr_brigade_cleanup(bb);
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c,
                      "h2_from_h1(%d): err bucket status=%d", 
                      from_h1->stream_id, st);
        ap_die(st, r);
        return AP_FILTER_ERROR;
    }
    
    from_h1->response = create_response(from_h1, r);
    if (from_h1->response == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
                      "h2_from_h1(%d): unable to create response", 
                      from_h1->stream_id);
        return APR_ENOMEM;
    }
    
    if (r->header_only) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                      "h2_from_h1(%d): header_only, cleanup output brigade", 
                      from_h1->stream_id);
        apr_brigade_cleanup(bb);
        return OK;
    }
    
    r->sent_bodyct = 1;         /* Whatever follows is real body stuff... */
    
    ap_remove_output_filter(f);
    if (APLOGctrace1(f->c)) {
        apr_off_t len = 0;
        apr_brigade_length(bb, 0, &len);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                      "h2_from_h1(%d): removed header filter, passing brigade "
                      "len=%ld", from_h1->stream_id, (long)len);
    }
    return ap_pass_brigade(f->next, bb);
}