static apr_status_t pass_output(h2_conn_io *io, int flush,
                                h2_session *session_eoc)
{
    conn_rec *c = io->c;
    apr_bucket_brigade *bb = io->output;
    apr_bucket *b;
    apr_off_t bblen;
    apr_status_t status;
    
    append_scratch(io);
    if (flush) {
        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
    }
    
    if (APR_BRIGADE_EMPTY(bb)) {
        return APR_SUCCESS;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, c, "h2_conn_io: pass_output");
    ap_update_child_status(c->sbh, SERVER_BUSY_WRITE, NULL);
    apr_brigade_length(bb, 0, &bblen);
    
    h2_conn_io_bb_log(c, 0, APLOG_TRACE2, "master conn pass", bb);
    status = ap_pass_brigade(c->output_filters, bb);
    if (status == APR_SUCCESS) {
        io->bytes_written += (apr_size_t)bblen;
        io->last_write = apr_time_now();
    }
    apr_brigade_cleanup(bb);

    if (session_eoc) {
        apr_status_t tmp;
        b = h2_bucket_eoc_create(c->bucket_alloc, session_eoc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        h2_conn_io_bb_log(c, 0, APLOG_TRACE2, "master conn pass", bb);
        tmp = ap_pass_brigade(c->output_filters, bb);
        if (status == APR_SUCCESS) {
            status = tmp;
        }
        /* careful with access to io after this, we have flushed an EOC bucket
         * that de-allocated us all. */
        apr_brigade_cleanup(bb);
    }
    
    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, APLOGNO(03044)
                      "h2_conn_io(%ld): pass_out brigade %ld bytes",
                      c->id, (long)bblen);
    }
    return status;
}