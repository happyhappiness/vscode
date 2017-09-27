        m->aborted = 1;
        h2_ngn_shed_abort(m->ngn_shed);
        leave_mutex(m, acquired);
    }
}

apr_status_t h2_mplx_stream_done(h2_mplx *m, int stream_id, int rst_error)
{
    apr_status_t status = APR_SUCCESS;
    int acquired;
    
    /* This maybe called from inside callbacks that already hold the lock.
     * E.g. when we are streaming out DATA and the EOF triggers the stream
     * release.
     */
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);

        /* there should be an h2_io, once the stream has been scheduled
         * for processing, e.g. when we received all HEADERs. But when
         * a stream is cancelled very early, it will not exist. */
        if (io) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c, 
                          "h2_mplx(%ld-%d): marking stream as done.", 
                          m->id, stream_id);
            io_stream_done(m, io, rst_error);
        }
        leave_mutex(m, acquired);
    }
    return status;
}

apr_status_t h2_mplx_in_read(h2_mplx *m, apr_read_type_e block,
                             int stream_id, apr_bucket_brigade *bb, 
                             apr_table_t *trailers,
                             struct apr_thread_cond_t *iowait)
{
    apr_status_t status; 
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_read_pre");
            
            h2_io_signal_init(io, H2_IO_READ, m->stream_timeout, iowait);
            status = h2_io_in_read(io, bb, -1, trailers);
            while (APR_STATUS_IS_EAGAIN(status) 
                   && !is_aborted(m, &status)
                   && block == APR_BLOCK_READ) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
                              "h2_mplx(%ld-%d): wait on in data (BLOCK_READ)", 
                              m->id, stream_id);
                status = h2_io_signal_wait(m, io);
                if (status == APR_SUCCESS) {
                    status = h2_io_in_read(io, bb, -1, trailers);
                }
            }
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_read_post");
            h2_io_signal_exit(io);
        }
        else {
            status = APR_EOF;
        }
        leave_mutex(m, acquired);
    }
    return status;
}

apr_status_t h2_mplx_in_write(h2_mplx *m, int stream_id, 
                              const char *data, apr_size_t len, int eos)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_write_pre");
            status = h2_io_in_write(io, data, len, eos);
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_write_post");
            h2_io_signal(io, H2_IO_READ);
            io_in_consumed_signal(m, io);
        }
        else {
            status = APR_ECONNABORTED;
        }
        leave_mutex(m, acquired);
    }
    return status;
}

apr_status_t h2_mplx_in_close(h2_mplx *m, int stream_id)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            status = h2_io_in_close(io);
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_close");
            h2_io_signal(io, H2_IO_READ);
            io_in_consumed_signal(m, io);
        }
        else {
            status = APR_ECONNABORTED;
        }
        leave_mutex(m, acquired);
    }
    return status;
}

void h2_mplx_set_consumed_cb(h2_mplx *m, h2_mplx_consumed_cb *cb, void *ctx)
{
    m->input_consumed = cb;
    m->input_consumed_ctx = ctx;
}

typedef struct {
    h2_mplx * m;
    int streams_updated;
} update_ctx;

static int update_window(void *ctx, h2_io *io)
{
    update_ctx *uctx = (update_ctx*)ctx;
    if (io_in_consumed_signal(uctx->m, io)) {
        ++uctx->streams_updated;
    }
    return 1;
}

apr_status_t h2_mplx_in_update_windows(h2_mplx *m)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        update_ctx ctx;
        
        ctx.m               = m;
        ctx.streams_updated = 0;

        status = APR_EAGAIN;
        h2_io_set_iter(m->stream_ios, update_window, &ctx);
        
        if (ctx.streams_updated) {
            status = APR_SUCCESS;
        }
        leave_mutex(m, acquired);
    }
    return status;
}

apr_status_t h2_mplx_out_get_brigade(h2_mplx *m, int stream_id, 
                                     apr_bucket_brigade *bb, 
                                     apr_off_t len, apr_table_t **ptrailers)
{
    apr_status_t status;
    int acquired;

    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_get_brigade_pre");
            
            status = h2_io_out_get_brigade(io, bb, len);
            
            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_get_brigade_post");
            if (status == APR_SUCCESS) {
                h2_io_signal(io, H2_IO_WRITE);
            }
        }
        else {
            status = APR_ECONNABORTED;
        }
        *ptrailers = io->response? io->response->trailers : NULL;
        leave_mutex(m, acquired);
    }
    return status;
}

h2_stream *h2_mplx_next_submit(h2_mplx *m, h2_ihash_t *streams)
{
    apr_status_t status;
    h2_stream *stream = NULL;
    int acquired;

    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_shift(m->ready_ios);
        if (io && !m->aborted) {
            stream = h2_ihash_get(streams, io->id);
            if (stream) {
                io->submitted = 1;
                if (io->rst_error) {
                    h2_stream_rst(stream, io->rst_error);
                }
                else {
                    AP_DEBUG_ASSERT(io->response);
                    H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_next_submit_pre");
                    h2_stream_set_response(stream, io->response, io->bbout);
                    H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_next_submit_post");
                }
            }
            else {
                /* We have the io ready, but the stream has gone away, maybe
                 * reset by the client. Should no longer happen since such
                 * streams should clear io's from the ready queue.
                 */
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, APLOGNO(03347)
                              "h2_mplx(%ld): stream for response %d closed, "
                              "resetting io to close request processing",
                              m->id, io->id);
                h2_io_make_orphaned(io, H2_ERR_STREAM_CLOSED);
                if (!io->worker_started || io->worker_done) {
                    io_destroy(m, io, 1);
                }
                else {
                    /* hang around until the h2_task is done, but
                     * shutdown input and send out any events (e.g. window
                     * updates) asap. */
                    h2_io_in_shutdown(io);
                    io_in_consumed_signal(m, io);
                }
            }
            
            h2_io_signal(io, H2_IO_WRITE);
        }
        leave_mutex(m, acquired);
    }
    return stream;
}

static apr_status_t out_write(h2_mplx *m, h2_io *io, 
                              ap_filter_t* f, int blocking,
                              apr_bucket_brigade *bb,
                              struct apr_thread_cond_t *iowait)
{
    apr_status_t status = APR_SUCCESS;
    /* We check the memory footprint queued for this stream_id
     * and block if it exceeds our configured limit.
     * We will not split buckets to enforce the limit to the last
     * byte. After all, the bucket is already in memory.
     */
    while (status == APR_SUCCESS 
           && !APR_BRIGADE_EMPTY(bb) 
           && !is_aborted(m, &status)) {
        
        status = h2_io_out_write(io, bb, blocking? m->stream_max_mem : INT_MAX, 
                                 &m->tx_handles_reserved);
        io_out_consumed_signal(m, io);
        
        /* Wait for data to drain until there is room again or
         * stream timeout expires */
        h2_io_signal_init(io, H2_IO_WRITE, m->stream_timeout, iowait);
        while (status == APR_SUCCESS
               && !APR_BRIGADE_EMPTY(bb) 
               && iowait
               && (m->stream_max_mem <= h2_io_out_length(io))
               && !is_aborted(m, &status)) {
            if (!blocking) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                              "h2_mplx(%ld-%d): incomplete write", 
                              m->id, io->id);
                return APR_INCOMPLETE;
            }
            if (f) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                              "h2_mplx(%ld-%d): waiting for out drain", 
                              m->id, io->id);
            }
            status = h2_io_signal_wait(m, io);
        }
        h2_io_signal_exit(io);
    }
    apr_brigade_cleanup(bb);
    
    return status;
}

static apr_status_t out_open(h2_mplx *m, int stream_id, h2_response *response,
                             ap_filter_t* f, apr_bucket_brigade *bb,
                             struct apr_thread_cond_t *iowait)
{
    apr_status_t status = APR_SUCCESS;
    
    h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
    if (io && !io->orphaned) {
        if (f) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                          "h2_mplx(%ld-%d): open response: %d, rst=%d",
                          m->id, stream_id, response->http_status, 
                          response->rst_error);
        }
        
        h2_io_set_response(io, response);
        h2_io_set_add(m->ready_ios, io);
        if (response && response->http_status < 300) {
            /* we might see some file buckets in the output, see
             * if we have enough handles reserved. */
            check_tx_reservation(m);
        }
        if (bb) {
            status = out_write(m, io, f, 0, bb, iowait);
            if (status == APR_INCOMPLETE) {
                /* write will have transferred as much data as possible.
                   caller has to deal with non-empty brigade */
                status = APR_SUCCESS;
            }
        }
        have_out_data_for(m, stream_id);
    }
    else {
        status = APR_ECONNABORTED;
    }
    return status;
}

apr_status_t h2_mplx_out_open(h2_mplx *m, int stream_id, h2_response *response,
                              ap_filter_t* f, apr_bucket_brigade *bb,
                              struct apr_thread_cond_t *iowait)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            status = out_open(m, stream_id, response, f, bb, iowait);
            if (APLOGctrace1(m->c)) {
                h2_util_bb_log(m->c, stream_id, APLOG_TRACE1, "h2_mplx_out_open", bb);
            }
        }
        leave_mutex(m, acquired);
    }
    return status;
}

apr_status_t h2_mplx_out_write(h2_mplx *m, int stream_id, 
                               ap_filter_t* f, int blocking,
                               apr_bucket_brigade *bb,
                               struct apr_thread_cond_t *iowait)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            status = out_write(m, io, f, blocking, bb, iowait);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
                          "h2_mplx(%ld-%d): write", m->id, io->id);
            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_write");
            
            have_out_data_for(m, stream_id);
        }
        else {
            status = APR_ECONNABORTED;
        }
        leave_mutex(m, acquired);
    }
    return status;
}

apr_status_t h2_mplx_out_close(h2_mplx *m, int stream_id)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            if (!io->response && !io->rst_error) {
                /* In case a close comes before a response was created,
                 * insert an error one so that our streams can properly
                 * reset.
                 */
                h2_response *r = h2_response_die(stream_id, APR_EGENERAL, 
                                                 io->request, m->pool);
                status = out_open(m, stream_id, r, NULL, NULL, NULL);
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, m->c,
                              "h2_mplx(%ld-%d): close, no response, no rst", 
                              m->id, io->id);
            }
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
                          "h2_mplx(%ld-%d): close with eor=%s", 
                          m->id, io->id, io->eor? "yes" : "no");
            status = h2_io_out_close(io);
            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_close");
            io_out_consumed_signal(m, io);
            
            have_out_data_for(m, stream_id);
        }
        else {
            status = APR_ECONNABORTED;
        }
        leave_mutex(m, acquired);
    }
    return status;
}

apr_status_t h2_mplx_out_rst(h2_mplx *m, int stream_id, int error)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->rst_error && !io->orphaned) {
            h2_io_rst(io, error);
            if (!io->response) {
                h2_io_set_add(m->ready_ios, io);
            }
            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_rst");
            
            have_out_data_for(m, stream_id);
            h2_io_signal(io, H2_IO_WRITE);
        }
        else {
            status = APR_ECONNABORTED;
        }
        leave_mutex(m, acquired);
    }
    return status;
}

int h2_mplx_out_has_data_for(h2_mplx *m, int stream_id)
{
    apr_status_t status;
    int has_data = 0;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io && !io->orphaned) {
            has_data = h2_io_out_has_data(io);
        }
        else {
            has_data = 0;
        }
        leave_mutex(m, acquired);
    }
    return has_data;
}

apr_status_t h2_mplx_out_trywait(h2_mplx *m, apr_interval_time_t timeout,
                                 apr_thread_cond_t *iowait)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            m->added_output = iowait;
            status = apr_thread_cond_timedwait(m->added_output, m->lock, timeout);
            if (APLOGctrace2(m->c)) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                              "h2_mplx(%ld): trywait on data for %f ms)",
                              m->id, timeout/1000.0);
