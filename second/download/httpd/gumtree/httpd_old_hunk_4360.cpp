            }
            h2_ihash_add(m->shold, stream);
            return;
        }
        else {
            /* already finished */
            task_destroy(m, task, 0);
        }
    }
    h2_stream_destroy(stream);
}

static int stream_done_iter(void *ctx, void *val)
{
    stream_done((h2_mplx*)ctx, val, 0);
    return 0;
}

static int task_print(void *ctx, void *val)
{
    h2_mplx *m = ctx;
    h2_task *task = val;

    if (task && task->request) {
        h2_stream *stream = h2_ihash_get(m->streams, task->stream_id);

        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%s): %s %s %s -> %s %d"
                      "[orph=%d/started=%d/done=%d]", 
                      task->id, task->request->method, 
                      task->request->authority, task->request->path,
                      task->response? "http" : (task->rst_error? "reset" : "?"),
                      task->response? task->response->http_status : task->rst_error,
                      (stream? 0 : 1), task->worker_started, 
                      task->worker_done);
    }
    else if (task) {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%ld-%d): NULL", m->id, task->stream_id);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%ld-NULL): NULL", m->id);
    }
    return 1;
}

static int task_abort_connection(void *ctx, void *val)
{
    h2_task *task = val;
    if (task->c) {
        task->c->aborted = 1;
    }
    if (task->input.beam) {
        h2_beam_abort(task->input.beam);
    }
    if (task->output.beam) {
        h2_beam_abort(task->output.beam);
    }
    return 1;
}

static int report_stream_iter(void *ctx, void *val) {
    h2_mplx *m = ctx;
    h2_stream *stream = val;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  "h2_mplx(%ld-%d): exists, started=%d, scheduled=%d, "
                  "submitted=%d, suspended=%d", 
                  m->id, stream->id, stream->started, stream->scheduled,
                  stream->submitted, stream->suspended);
    return 1;
}

apr_status_t h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
{
    apr_status_t status;
    int acquired;

    h2_workers_unregister(m->workers, m);
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        int i, wait_secs = 5;

        if (!h2_ihash_empty(m->streams) && APLOGctrace1(m->c)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          "h2_mplx(%ld): release_join with %d streams open, "
                          "%d streams resume, %d streams ready, %d tasks", 
                          m->id, (int)h2_ihash_count(m->streams),
                          (int)h2_ihash_count(m->sresume), 
                          (int)h2_ihash_count(m->sready), 
                          (int)h2_ihash_count(m->tasks));
            h2_ihash_iter(m->streams, report_stream_iter, m);
        }
        
        /* disable WINDOW_UPDATE callbacks */
        h2_mplx_set_consumed_cb(m, NULL, NULL);
        
        if (!h2_ihash_empty(m->shold)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): start release_join with %d streams in hold", 
                          m->id, (int)h2_ihash_count(m->shold));
        }
        if (!h2_ihash_empty(m->spurge)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): start release_join with %d streams to purge", 
                          m->id, (int)h2_ihash_count(m->spurge));
        }
        
        h2_iq_clear(m->q);
        apr_thread_cond_broadcast(m->task_thawed);
        while (!h2_ihash_iter(m->streams, stream_done_iter, m)) {
            /* iterate until all streams have been removed */
        }
        AP_DEBUG_ASSERT(h2_ihash_empty(m->streams));
    
        if (!h2_ihash_empty(m->shold)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): 2. release_join with %d streams in hold", 
                          m->id, (int)h2_ihash_count(m->shold));
        }
        if (!h2_ihash_empty(m->spurge)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): 2. release_join with %d streams to purge", 
                          m->id, (int)h2_ihash_count(m->spurge));
        }
        
        /* If we still have busy workers, we cannot release our memory
         * pool yet, as tasks have references to us.
         * Any operation on the task slave connection will from now on
         * be errored ECONNRESET/ABORTED, so processing them should fail 
         * and workers *should* return in a timely fashion.
         */
        for (i = 0; m->workers_busy > 0; ++i) {
            h2_ihash_iter(m->tasks, task_abort_connection, m);
            
            m->join_wait = wait;
            status = apr_thread_cond_timedwait(wait, m->lock, apr_time_from_sec(wait_secs));
            
            if (APR_STATUS_IS_TIMEUP(status)) {
                if (i > 0) {
                    /* Oh, oh. Still we wait for assigned  workers to report that 
                     * they are done. Unless we have a bug, a worker seems to be hanging. 
                     * If we exit now, all will be deallocated and the worker, once 
                     * it does return, will walk all over freed memory...
                     */
                    ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, APLOGNO(03198)
                                  "h2_mplx(%ld): release, waiting for %d seconds now for "
                                  "%d h2_workers to return, have still %d tasks outstanding", 
                                  m->id, i*wait_secs, m->workers_busy,
                                  (int)h2_ihash_count(m->tasks));
                    if (i == 1) {
                        h2_ihash_iter(m->tasks, task_print, m);
                    }
                }
                h2_mplx_abort(m);
                apr_thread_cond_broadcast(m->task_thawed);
            }
        }
        
        AP_DEBUG_ASSERT(h2_ihash_empty(m->shold));
        if (!h2_ihash_empty(m->spurge)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): 3. release_join %d streams to purge", 
                          m->id, (int)h2_ihash_count(m->spurge));
            purge_streams(m);
        }
        AP_DEBUG_ASSERT(h2_ihash_empty(m->spurge));
        
        if (!h2_ihash_empty(m->tasks)) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, APLOGNO(03056)
                          "h2_mplx(%ld): release_join -> destroy, "
                          "%d tasks still present", 
                          m->id, (int)h2_ihash_count(m->tasks));
        }
        leave_mutex(m, acquired);
        h2_mplx_destroy(m);
        /* all gone */
    }
    return status;
}

void h2_mplx_abort(h2_mplx *m)
{
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if (!m->aborted && enter_mutex(m, &acquired) == APR_SUCCESS) {
        m->aborted = 1;
        h2_ngn_shed_abort(m->ngn_shed);
        leave_mutex(m, acquired);
    }
}

apr_status_t h2_mplx_stream_done(h2_mplx *m, h2_stream *stream)
{
    apr_status_t status = APR_SUCCESS;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c, 
                      "h2_mplx(%ld-%d): marking stream as done.", 
                      m->id, stream->id);
        stream_done(m, stream, stream->rst_error);
        purge_streams(m);
        leave_mutex(m, acquired);
    }
    return status;
}

void h2_mplx_set_consumed_cb(h2_mplx *m, h2_mplx_consumed_cb *cb, void *ctx)
{
    m->input_consumed = cb;
    m->input_consumed_ctx = ctx;
}

static apr_status_t out_open(h2_mplx *m, int stream_id, h2_response *response)
{
    apr_status_t status = APR_SUCCESS;
    h2_task *task = h2_ihash_get(m->tasks, stream_id);
    h2_stream *stream = h2_ihash_get(m->streams, stream_id);
    
    if (!task || !stream) {
        return APR_ECONNABORTED;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  "h2_mplx(%s): open response: %d, rst=%d",
                  task->id, response->http_status, response->rst_error);
    
    h2_task_set_response(task, response);
    
    if (task->output.beam) {
        h2_beam_buffer_size_set(task->output.beam, m->stream_max_mem);
        h2_beam_timeout_set(task->output.beam, m->stream_timeout);
        h2_beam_on_consumed(task->output.beam, stream_output_consumed, task);
        m->tx_handles_reserved -= h2_beam_get_files_beamed(task->output.beam);
        h2_beam_on_file_beam(task->output.beam, can_beam_file, m);
        h2_beam_mutex_set(task->output.beam, beam_enter, task->cond, m);
    }
    
    h2_ihash_add(m->sready, stream);
    if (response && response->http_status < 300) {
        /* we might see some file buckets in the output, see
         * if we have enough handles reserved. */
        check_tx_reservation(m);
    }
    have_out_data_for(m, stream_id);
    return status;
}

apr_status_t h2_mplx_out_open(h2_mplx *m, int stream_id, h2_response *response)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            status = out_open(m, stream_id, response);
        }
        leave_mutex(m, acquired);
    }
    return status;
}

