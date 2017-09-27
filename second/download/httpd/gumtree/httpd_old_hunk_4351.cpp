        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, io->c,
                      "h2_conn_io(%ld): threshold reached, write size now %ld", 
                      (long)io->c->id, (long)io->write_size);
    }
}

static apr_status_t pass_output(h2_conn_io *io, int flush, int eoc)
{
    conn_rec *c = io->c;
    apr_bucket *b;
    apr_off_t bblen;
    apr_status_t status;
    
    append_scratch(io);
    if (flush) {
        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(io->output, b);
    }
    
    if (APR_BRIGADE_EMPTY(io->output)) {
        return APR_SUCCESS;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, c, "h2_conn_io: pass_output");
    ap_update_child_status(c->sbh, SERVER_BUSY_WRITE, NULL);
    apr_brigade_length(io->output, 0, &bblen);
    
    h2_conn_io_bb_log(c, 0, APLOG_TRACE2, "master conn pass", io->output);
    status = ap_pass_brigade(c->output_filters, io->output);

    /* careful with access after this, as we might have flushed an EOC bucket
     * that de-allocated us all. */
    if (!eoc) {
        apr_brigade_cleanup(io->output);
        if (status == APR_SUCCESS) {
            io->bytes_written += (apr_size_t)bblen;
            io->last_write = apr_time_now();
        }
    }
    
    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, APLOGNO(03044)
                      "h2_conn_io(%ld): pass_out brigade %ld bytes",
                      c->id, (long)bblen);
    }
    return status;
}

apr_status_t h2_conn_io_flush(h2_conn_io *io)
{
    return pass_output(io, 1, 0);
}

apr_status_t h2_conn_io_write_eoc(h2_conn_io *io, h2_session *session)
{
    apr_bucket *b = h2_bucket_eoc_create(io->c->bucket_alloc, session);
    APR_BRIGADE_INSERT_TAIL(io->output, b);
    return pass_output(io, 1, 1);
}

apr_status_t h2_conn_io_write(h2_conn_io *io, const char *data, size_t length)
{
    apr_status_t status = APR_SUCCESS;
    apr_size_t remain;
