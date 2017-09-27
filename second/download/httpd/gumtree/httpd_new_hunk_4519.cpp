    if (io->write_size > WRITE_SIZE_INITIAL 
        && (io->cooldown_usecs > 0)
        && (apr_time_now() - io->last_write) >= io->cooldown_usecs) {
        /* long time not written, reset write size */
        io->write_size = WRITE_SIZE_INITIAL;
        io->bytes_written = 0;
    }
    else if (io->write_size < WRITE_SIZE_MAX 
             && io->bytes_written >= io->warmup_size) {
        /* connection is hot, use max size */
        io->write_size = WRITE_SIZE_MAX;
    }
}

static apr_status_t pass_output(h2_conn_io *io, int flush)
{
    conn_rec *c = io->c;
    apr_bucket_brigade *bb = io->output;
    apr_bucket *b;
    apr_off_t bblen;
    apr_status_t status;
    
    append_scratch(io);
    if (flush && !io->is_flushed) {
        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
    }
    
    if (APR_BRIGADE_EMPTY(bb)) {
        return APR_SUCCESS;
    }
    
    ap_update_child_status(c->sbh, SERVER_BUSY_WRITE, NULL);
    apr_brigade_length(bb, 0, &bblen);
    h2_conn_io_bb_log(c, 0, APLOG_TRACE2, "out", bb);
    
    status = ap_pass_brigade(c->output_filters, bb);
    if (status == APR_SUCCESS) {
        io->bytes_written += (apr_size_t)bblen;
        io->last_write = apr_time_now();
        if (flush) {
            io->is_flushed = 1;
        }
    }
    apr_brigade_cleanup(bb);

    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, APLOGNO(03044)
                      "h2_conn_io(%ld): pass_out brigade %ld bytes",
                      c->id, (long)bblen);
    }
    return status;
}

int h2_conn_io_needs_flush(h2_conn_io *io)
{
    if (!io->is_flushed) {
        apr_off_t len = h2_brigade_mem_size(io->output);
        if (len > io->flush_threshold) {
            return 1;
        }
        /* if we do not exceed flush length due to memory limits,
         * we want at least flush when we have that amount of data. */
        apr_brigade_length(io->output, 0, &len);
        return len > (4 * io->flush_threshold);
    }
    return 0;
}

apr_status_t h2_conn_io_flush(h2_conn_io *io)
{
    apr_status_t status;
    status = pass_output(io, 1);
    check_write_size(io);
    return status;
}

apr_status_t h2_conn_io_write(h2_conn_io *io, const char *data, size_t length)
{
    apr_status_t status = APR_SUCCESS;
    apr_size_t remain;
    
    if (length > 0) {
        io->is_flushed = 0;
    }
    
    if (io->buffer_output) {
        while (length > 0) {
            remain = assure_scratch_space(io);
            if (remain >= length) {
                memcpy(io->scratch + io->slen, data, length);
                io->slen += length;
                length = 0;
            }
            else {
                memcpy(io->scratch + io->slen, data, remain);
                io->slen += remain;
                data += remain;
                length -= remain;
            }
        }
