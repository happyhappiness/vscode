    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return NULL;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_io *io = h2_io_set_pop_highest_prio(m->ready_ios);
        if (io) {
            stream = h2_stream_set_get(streams, io->id);
            if (stream) {
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
                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, m->c, APLOGNO(02953) 
                              "h2_mplx(%ld): stream for response %d closed, "
                              "resetting io to close request processing",
                              m->id, io->id);
                io->orphaned = 1;
                if (io->task_done) {
                    io_destroy(m, io, 1);
                }
                else {
                    /* hang around until the h2_task is done, but
                     * shutdown input and send out any events (e.g. window
                     * updates) asap. */
                    h2_io_in_shutdown(io);
                    h2_io_rst(io, H2_ERR_STREAM_CLOSED);
                    io_process_events(m, io);
                }
            }
            
            if (io->output_drained) {
                apr_thread_cond_signal(io->output_drained);
            }
        }
        apr_thread_mutex_unlock(m->lock);
    }
    return stream;
}

static apr_status_t out_write(h2_mplx *m, h2_io *io, 
                              ap_filter_t* f, apr_bucket_brigade *bb,
                              apr_table_t *trailers,
                              struct apr_thread_cond_t *iowait)
{
    apr_status_t status = APR_SUCCESS;
    /* We check the memory footprint queued for this stream_id
     * and block if it exceeds our configured limit.
     * We will not split buckets to enforce the limit to the last
     * byte. After all, the bucket is already in memory.
     */
    while (!APR_BRIGADE_EMPTY(bb) 
           && (status == APR_SUCCESS)
           && !is_aborted(m, &status)) {
        
        status = h2_io_out_write(io, bb, m->stream_max_mem, trailers,
                                 &m->file_handles_allowed);
        /* Wait for data to drain until there is room again */
        while (!APR_BRIGADE_EMPTY(bb) 
               && iowait
               && status == APR_SUCCESS
               && (m->stream_max_mem <= h2_io_out_length(io))
               && !is_aborted(m, &status)) {
            trailers = NULL;
            io->output_drained = iowait;
            if (f) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                              "h2_mplx(%ld-%d): waiting for out drain", 
                              m->id, io->id);
            }
            apr_thread_cond_wait(io->output_drained, m->lock);
            io->output_drained = NULL;
        }
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
        if (bb) {
            status = out_write(m, io, f, bb, response->trailers, iowait);
        }
        have_out_data_for(m, stream_id);
    }
    else {
        status = APR_ECONNABORTED;
    }
