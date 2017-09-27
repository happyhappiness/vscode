        h2_iq_clear(m->q);
        leave_mutex(m, acquired);
    }
    return max_stream_started;
}

static void input_consumed_signal(h2_mplx *m, h2_stream *stream)
{
    if (stream->input && stream->started) {
        h2_beam_send(stream->input, NULL, 0); /* trigger updates */
    }
}

static int output_consumed_signal(h2_mplx *m, h2_task *task)
{
    if (task->output.beam && task->worker_started && task->assigned) {
        /* trigger updates */
        h2_beam_send(task->output.beam, NULL, APR_NONBLOCK_READ);
    }
    return 0;
}


static void task_destroy(h2_mplx *m, h2_task *task, int called_from_master)
{
    conn_rec *slave = NULL;
    int reuse_slave = 0;
    apr_status_t status;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c, 
                  "h2_task(%s): destroy", task->id);
    if (called_from_master) {
        /* Process outstanding events before destruction */
        h2_stream *stream = h2_ihash_get(m->streams, task->stream_id);
        if (stream) {
            input_consumed_signal(m, stream);
        }
    }
    
    /* The pool is cleared/destroyed which also closes all
     * allocated file handles. Give this count back to our
     * file handle pool. */
    if (task->output.beam) {
        m->tx_handles_reserved += 
        h2_beam_get_files_beamed(task->output.beam);
        h2_beam_on_produced(task->output.beam, NULL, NULL);
        status = h2_beam_shutdown(task->output.beam, APR_NONBLOCK_READ, 1);
        if (status != APR_SUCCESS){
            ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, m->c, 
                          APLOGNO(03385) "h2_task(%s): output shutdown "
                          "incomplete", task->id);
        }
    }
    
    slave = task->c;
    reuse_slave = ((m->spare_slaves->nelts < m->spare_slaves->nalloc)
                   && !task->rst_error);
    
    h2_ihash_remove(m->tasks, task->stream_id);
    if (m->redo_tasks) {
        h2_ihash_remove(m->redo_tasks, task->stream_id);
    }
    h2_task_destroy(task);

    if (slave) {
        if (reuse_slave && slave->keepalive == AP_CONN_KEEPALIVE) {
            APR_ARRAY_PUSH(m->spare_slaves, conn_rec*) = slave;
        }
        else {
            slave->sbh = NULL;
            h2_slave_destroy(slave, NULL);
        }
    }
    
    check_tx_free(m);
}

static void stream_done(h2_mplx *m, h2_stream *stream, int rst_error) 
{
    h2_task *task;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c, 
                  "h2_stream(%ld-%d): done", m->c->id, stream->id);
    /* Situation: we are, on the master connection, done with processing
     * the stream. Either we have handled it successfully, or the stream
     * was reset by the client or the connection is gone and we are 
     * shutting down the whole session.
     *
     * We possibly have created a task for this stream to be processed
     * on a slave connection. The processing might actually be ongoing
     * right now or has already finished. A finished task waits for its
     * stream to be done. This is the common case.
     * 
     * If the stream had input (e.g. the request had a body), a task
     * may have read, or is still reading buckets from the input beam.
     * This means that the task is referencing memory from the stream's
     * pool (or the master connection bucket alloc). Before we can free
     * the stream pool, we need to make sure that those references are
     * gone. This is what h2_beam_shutdown() on the input waits for.
     *
     * With the input handled, we can tear down that beam and care
     * about the output beam. The stream might still have buffered some
     * buckets read from the output, so we need to get rid of those. That
     * is done by h2_stream_cleanup().
     *
     * Now it is save to destroy the task (if it exists and is finished).
     * 
     * FIXME: we currently destroy the stream, even if the task is still
     * ongoing. This is not ok, since task->request is coming from stream
     * memory. We should either copy it on task creation or wait with the
     * stream destruction until the task is done. 
     */
    h2_iq_remove(m->q, stream->id);
    h2_ihash_remove(m->sready, stream->id);
    h2_ihash_remove(m->sresume, stream->id);
    h2_ihash_remove(m->streams, stream->id);
    if (stream->input) {
        m->tx_handles_reserved += h2_beam_get_files_beamed(stream->input);
        h2_beam_on_consumed(stream->input, NULL, NULL);
        /* Let anyone blocked reading know that there is no more to come */
        h2_beam_abort(stream->input);
        /* Remove mutex after, so that abort still finds cond to signal */
        h2_beam_mutex_set(stream->input, NULL, NULL, NULL);
    }
    h2_stream_cleanup(stream);

    task = h2_ihash_get(m->tasks, stream->id);
    if (task) {
        if (!task->worker_done) {
            /* task still running, cleanup once it is done */
            if (rst_error) {
                h2_task_rst(task, rst_error);
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
