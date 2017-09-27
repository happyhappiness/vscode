    stream_iter_ctx_t *x = ctx;
    return x->cb(stream, x->ctx);
}

apr_status_t h2_mplx_stream_do(h2_mplx *m, h2_mplx_stream_cb *cb, void *ctx)
{
    stream_iter_ctx_t x;
    
    H2_MPLX_ENTER(m);

    x.cb = cb;
    x.ctx = ctx;
    h2_ihash_iter(m->streams, stream_iter_wrap, &x);
        
    H2_MPLX_LEAVE(m);
    return APR_SUCCESS;
}

static int report_stream_iter(void *ctx, void *val) {
    h2_mplx *m = ctx;
    h2_stream *stream = val;
    h2_task *task = stream->task;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  H2_STRM_MSG(stream, "started=%d, scheduled=%d, ready=%d, "
                              "out_buffer=%ld"), 
                  !!stream->task, stream->scheduled, h2_stream_is_ready(stream),
                  (long)h2_beam_get_buffered(stream->output));
    if (task) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, /* NO APLOGNO */
                      H2_STRM_MSG(stream, "->03198: %s %s %s"
                      "[started=%d/done=%d/frozen=%d]"), 
                      task->request->method, task->request->authority, 
                      task->request->path, task->worker_started, 
                      task->worker_done, task->frozen);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, /* NO APLOGNO */
                      H2_STRM_MSG(stream, "->03198: no task"));
    }
    return 1;
}

static int unexpected_stream_iter(void *ctx, void *val) {
    h2_mplx *m = ctx;
    h2_stream *stream = val;
    ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
                  H2_STRM_MSG(stream, "unexpected, started=%d, scheduled=%d, ready=%d"), 
                  !!stream->task, stream->scheduled, h2_stream_is_ready(stream));
    return 1;
}

static int stream_cancel_iter(void *ctx, void *val) {
    h2_mplx *m = ctx;
    h2_stream *stream = val;

    /* disabled input consumed reporting */
    if (stream->input) {
        h2_beam_on_consumed(stream->input, NULL, NULL, NULL);
    }
    /* take over event monitoring */
    h2_stream_set_monitor(stream, NULL);
    /* Reset, should transit to CLOSED state */
    h2_stream_rst(stream, H2_ERR_NO_ERROR);
    /* All connection data has been sent, simulate cleanup */
    h2_stream_dispatch(stream, H2_SEV_EOS_SENT);
    stream_cleanup(m, stream);  
    return 0;
}

void h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
{
    apr_status_t status;
    int i, wait_secs = 60;

    /* How to shut down a h2 connection:
     * 0. abort and tell the workers that no more tasks will come from us */
    m->aborted = 1;
    h2_workers_unregister(m->workers, m);
    
    H2_MPLX_ENTER_ALWAYS(m);

    /* How to shut down a h2 connection:
     * 1. cancel all streams still active */
    while (!h2_ihash_iter(m->streams, stream_cancel_iter, m)) {
        /* until empty */
    }
    
    /* 2. terminate ngn_shed, no more streams
     * should be scheduled or in the active set */
    h2_ngn_shed_abort(m->ngn_shed);
    ap_assert(h2_ihash_empty(m->streams));
    ap_assert(h2_iq_empty(m->q));
    
    /* 3. while workers are busy on this connection, meaning they
     *    are processing tasks from this connection, wait on them finishing
     *    in order to wake us and let us check again. 
     *    Eventually, this has to succeed. */    
    m->join_wait = wait;
    for (i = 0; h2_ihash_count(m->shold) > 0; ++i) {        
        status = apr_thread_cond_timedwait(wait, m->lock, apr_time_from_sec(wait_secs));
        
        if (APR_STATUS_IS_TIMEUP(status)) {
            /* This can happen if we have very long running requests
             * that do not time out on IO. */
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, APLOGNO(03198)
                          "h2_mplx(%ld): waited %d sec for %d tasks", 
                          m->id, i*wait_secs, (int)h2_ihash_count(m->shold));
            h2_ihash_iter(m->shold, report_stream_iter, m);
        }
    }
    m->join_wait = NULL;
    
    /* 4. close the h2_req_enginge shed */
    h2_ngn_shed_destroy(m->ngn_shed);
    m->ngn_shed = NULL;
    
    /* 4. With all workers done, all streams should be in spurge */
    if (!h2_ihash_empty(m->shold)) {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, APLOGNO(03516)
                      "h2_mplx(%ld): unexpected %d streams in hold", 
                      m->id, (int)h2_ihash_count(m->shold));
        h2_ihash_iter(m->shold, unexpected_stream_iter, m);
    }
    
    H2_MPLX_LEAVE(m);

    /* 5. unregister again, now that our workers are done */
    h2_workers_unregister(m->workers, m);

    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  "h2_mplx(%ld): released", m->id);
}

apr_status_t h2_mplx_stream_cleanup(h2_mplx *m, h2_stream *stream)
{
    H2_MPLX_ENTER(m);
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c, 
                  H2_STRM_MSG(stream, "cleanup"));
    stream_cleanup(m, stream);        
    
    H2_MPLX_LEAVE(m);
    return APR_SUCCESS;
}

h2_stream *h2_mplx_stream_get(h2_mplx *m, int id)
{
    h2_stream *s = NULL;
    
    H2_MPLX_ENTER_ALWAYS(m);

    s = h2_ihash_get(m->streams, id);

    H2_MPLX_LEAVE(m);
    return s;
}

static void output_produced(void *ctx, h2_bucket_beam *beam, apr_off_t bytes)
{
    h2_stream *stream = ctx;
    h2_mplx *m = stream->session->mplx;
    
    check_data_for(m, stream, 1);
}

static apr_status_t out_open(h2_mplx *m, int stream_id, h2_bucket_beam *beam)
{
    apr_status_t status = APR_SUCCESS;
    h2_stream *stream = h2_ihash_get(m->streams, stream_id);
    
    if (!stream || !stream->task || m->aborted) {
        return APR_ECONNABORTED;
    }
    
    ap_assert(stream->output == NULL);
    stream->output = beam;
    
    if (APLOGctrace2(m->c)) {
        h2_beam_log(beam, m->c, APLOG_TRACE2, "out_open");
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, m->c,
                      "h2_mplx(%s): out open", stream->task->id);
    }
    
    h2_beam_on_consumed(stream->output, NULL, stream_output_consumed, stream);
    h2_beam_on_produced(stream->output, output_produced, stream);
    if (stream->task->output.copy_files) {
        h2_beam_on_file_beam(stream->output, h2_beam_no_files, NULL);
    }
    
    /* time to protect the beam against multi-threaded use */
    h2_beam_mutex_enable(stream->output);
    
    /* we might see some file buckets in the output, see
     * if we have enough handles reserved. */
    check_data_for(m, stream, 0);
    return status;
}

apr_status_t h2_mplx_out_open(h2_mplx *m, int stream_id, h2_bucket_beam *beam)
{
    apr_status_t status;
    
    H2_MPLX_ENTER(m);

    if (m->aborted) {
        status = APR_ECONNABORTED;
    }
    else {
        status = out_open(m, stream_id, beam);
    }

    H2_MPLX_LEAVE(m);
    return status;
}

static apr_status_t out_close(h2_mplx *m, h2_task *task)
{
    apr_status_t status = APR_SUCCESS;
    h2_stream *stream;
    
    if (!task) {
        return APR_ECONNABORTED;
    }
    if (task->c) {
        ++task->c->keepalives;
    }
    
    stream = h2_ihash_get(m->streams, task->stream_id);
    if (!stream) {
        return APR_ECONNABORTED;
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
                  "h2_mplx(%s): close", task->id);
    status = h2_beam_close(task->output.beam);
    h2_beam_log(task->output.beam, m->c, APLOG_TRACE2, "out_close");
    output_consumed_signal(m, task);
    check_data_for(m, stream, 0);
    return status;
}

apr_status_t h2_mplx_out_trywait(h2_mplx *m, apr_interval_time_t timeout,
                                 apr_thread_cond_t *iowait)
{
    apr_status_t status;
    
    H2_MPLX_ENTER(m);

    if (m->aborted) {
        status = APR_ECONNABORTED;
    }
    else if (h2_mplx_has_master_events(m)) {
        status = APR_SUCCESS;
    }
    else {
        purge_streams(m, 0);
        h2_ihash_iter(m->streams, report_consumption_iter, m);
        m->added_output = iowait;
        status = apr_thread_cond_timedwait(m->added_output, m->lock, timeout);
        if (APLOGctrace2(m->c)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): trywait on data for %f ms)",
                          m->id, timeout/1000.0);
        }
        m->added_output = NULL;
    }

    H2_MPLX_LEAVE(m);
    return status;
}

static void check_data_for(h2_mplx *m, h2_stream *stream, int lock)
{
    if (h2_fifo_push(m->readyq, stream) == APR_SUCCESS) {
        apr_atomic_set32(&m->event_pending, 1);
        H2_MPLX_ENTER_MAYBE(m, lock);
        if (m->added_output) {
            apr_thread_cond_signal(m->added_output);
        }
        H2_MPLX_LEAVE_MAYBE(m, lock);
    }
}

apr_status_t h2_mplx_reprioritize(h2_mplx *m, h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    
    H2_MPLX_ENTER(m);

    if (m->aborted) {
        status = APR_ECONNABORTED;
    }
    else {
        h2_iq_sort(m->q, cmp, ctx);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                      "h2_mplx(%ld): reprioritize tasks", m->id);
        status = APR_SUCCESS;
    }

    H2_MPLX_LEAVE(m);
    return status;
}

static void register_if_needed(h2_mplx *m) 
{
    if (!m->is_registered && !h2_iq_empty(m->q)) {
        apr_status_t status = h2_workers_register(m->workers, m); 
        if (status == APR_SUCCESS) {
            m->is_registered = 1;
        }
        else {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, status, m->c, APLOGNO(10021)
                          "h2_mplx(%ld): register at workers", m->id);
        }
    }
}

apr_status_t h2_mplx_process(h2_mplx *m, struct h2_stream *stream, 
                             h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    
    H2_MPLX_ENTER(m);

    if (m->aborted) {
        status = APR_ECONNABORTED;
    }
    else {
        status = APR_SUCCESS;
        h2_ihash_add(m->streams, stream);
        if (h2_stream_is_ready(stream)) {
            /* already have a response */
            check_data_for(m, stream, 0);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          H2_STRM_MSG(stream, "process, add to readyq")); 
        }
        else {
            h2_iq_add(m->q, stream->id, cmp, ctx);
            register_if_needed(m);                
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          H2_STRM_MSG(stream, "process, added to q")); 
        }
    }

    H2_MPLX_LEAVE(m);
    return status;
}

static h2_task *next_stream_task(h2_mplx *m)
{
    h2_stream *stream;
    int sid;
    while (!m->aborted && (m->tasks_active < m->limit_active)
           && (sid = h2_iq_shift(m->q)) > 0) {
        
        stream = h2_ihash_get(m->streams, sid);
        if (stream) {
            conn_rec *slave, **pslave;

            pslave = (conn_rec **)apr_array_pop(m->spare_slaves);
            if (pslave) {
                slave = *pslave;
                slave->aborted = 0;
            }
            else {
                slave = h2_slave_create(m->c, stream->id, m->pool);
            }
            
            if (!stream->task) {

                if (sid > m->max_stream_started) {
                    m->max_stream_started = sid;
                }
                if (stream->input) {
                    h2_beam_on_consumed(stream->input, stream_input_ev, 
                                        stream_input_consumed, stream);
                }
                
                stream->task = h2_task_create(slave, stream->id, 
                                              stream->request, m, stream->input, 
                                              stream->session->s->timeout,
                                              m->stream_max_mem);
                if (!stream->task) {
                    ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, slave,
                                  H2_STRM_LOG(APLOGNO(02941), stream, 
                                  "create task"));
                    return NULL;
                }
                
            }
            
            ++m->tasks_active;
            return stream->task;
        }
    }
    return NULL;
}

h2_task *h2_mplx_pop_task(h2_mplx *m, int *has_more)
{
    h2_task *task = NULL;
    
    H2_MPLX_ENTER_ALWAYS(m);

    *has_more = 0;
    if (!m->aborted) {
        task = next_stream_task(m);
        if (task != NULL && !h2_iq_empty(m->q)) {
            *has_more = 1;
        }
        else {
            m->is_registered = 0; /* h2_workers will discard this mplx */
        }
    }

    H2_MPLX_LEAVE(m);
    return task;
}

static void task_done(h2_mplx *m, h2_task *task, h2_req_engine *ngn)
{
    h2_stream *stream;
    
    if (task->frozen) {
        /* this task was handed over to an engine for processing 
         * and the original worker has finished. That means the 
         * engine may start processing now. */
        h2_task_thaw(task);
        apr_thread_cond_broadcast(m->task_thawed);
        return;
    }
        
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  "h2_mplx(%ld): task(%s) done", m->id, task->id);
    out_close(m, task);
    
    if (ngn) {
        apr_off_t bytes = 0;
        h2_beam_send(task->output.beam, NULL, APR_NONBLOCK_READ);
        bytes += h2_beam_get_buffered(task->output.beam);
        if (bytes > 0) {
            /* we need to report consumed and current buffered output
             * to the engine. The request will be streamed out or cancelled,
             * no more data is coming from it and the engine should update
             * its calculations before we destroy this information. */
            h2_req_engine_out_consumed(ngn, task->c, bytes);
        }
    }
    
    if (task->engine) {
        if (!m->aborted && !task->c->aborted 
            && !h2_req_engine_is_shutdown(task->engine)) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, APLOGNO(10022)
                          "h2_mplx(%ld): task(%s) has not-shutdown "
                          "engine(%s)", m->id, task->id, 
                          h2_req_engine_get_id(task->engine));
        }
        h2_ngn_shed_done_ngn(m->ngn_shed, task->engine);
    }
    
    task->worker_done = 1;
    task->done_at = apr_time_now();
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                  "h2_mplx(%s): request done, %f ms elapsed", task->id, 
                  (task->done_at - task->started_at) / 1000.0);
    
    if (task->started_at > m->last_idle_block) {
        /* this task finished without causing an 'idle block', e.g.
         * a block by flow control.
         */
        if (task->done_at- m->last_limit_change >= m->limit_change_interval
            && m->limit_active < m->max_active) {
            /* Well behaving stream, allow it more workers */
            m->limit_active = H2MIN(m->limit_active * 2, 
                                     m->max_active);
            m->last_limit_change = task->done_at;
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          "h2_mplx(%ld): increase worker limit to %d",
                          m->id, m->limit_active);
        }
    }
    
    stream = h2_ihash_get(m->streams, task->stream_id);
    if (stream) {
        /* stream not done yet. */
        if (!m->aborted && h2_ihash_get(m->sredo, stream->id)) {
            /* reset and schedule again */
            h2_task_redo(task);
            h2_ihash_remove(m->sredo, stream->id);
            h2_iq_add(m->q, stream->id, NULL, NULL);
        }
        else {
            /* stream not cleaned up, stay around */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          H2_STRM_MSG(stream, "task_done, stream open")); 
            if (stream->input) {
                h2_beam_leave(stream->input);
                h2_beam_mutex_disable(stream->input);
            }
            if (stream->output) {
                h2_beam_mutex_disable(stream->output);
            }

            /* more data will not arrive, resume the stream */
            check_data_for(m, stream, 0);            
        }
    }
    else if ((stream = h2_ihash_get(m->shold, task->stream_id)) != NULL) {
        /* stream is done, was just waiting for this. */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                      H2_STRM_MSG(stream, "task_done, in hold"));
        if (stream->input) {
            h2_beam_leave(stream->input);
            h2_beam_mutex_disable(stream->input);
        }
        if (stream->output) {
            h2_beam_mutex_disable(stream->output);
        }
        stream_joined(m, stream);
    }
    else if ((stream = h2_ihash_get(m->spurge, task->stream_id)) != NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c,   
                      H2_STRM_LOG(APLOGNO(03517), stream, "already in spurge"));
        ap_assert("stream should not be in spurge" == NULL);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, APLOGNO(03518)
                      "h2_mplx(%s): task_done, stream not found", 
                      task->id);
        ap_assert("stream should still be available" == NULL);
    }
}

void h2_mplx_task_done(h2_mplx *m, h2_task *task, h2_task **ptask)
{
    H2_MPLX_ENTER_ALWAYS(m);

    task_done(m, task, NULL);
    --m->tasks_active;
    
    if (m->join_wait) {
        apr_thread_cond_signal(m->join_wait);
    }
    if (ptask) {
        /* caller wants another task */
        *ptask = next_stream_task(m);
    }
    register_if_needed(m);

    H2_MPLX_LEAVE(m);
}

/*******************************************************************************
 * h2_mplx DoS protection
 ******************************************************************************/

static int latest_repeatable_unsubmitted_iter(void *data, void *val)
{
    stream_iter_ctx *ctx = data;
    h2_stream *stream = val;
    
    if (stream->task && !stream->task->worker_done 
        && h2_task_can_redo(stream->task) 
        && !h2_ihash_get(ctx->m->sredo, stream->id)) {
        if (!h2_stream_is_ready(stream)) {
            /* this task occupies a worker, the response has not been submitted 
             * yet, not been cancelled and it is a repeatable request
             * -> it can be re-scheduled later */
            if (!ctx->stream 
                || (ctx->stream->task->started_at < stream->task->started_at)) {
                /* we did not have one or this one was started later */
                ctx->stream = stream;
            }
        }
    }
    return 1;
}

static h2_stream *get_latest_repeatable_unsubmitted_stream(h2_mplx *m) 
{
    stream_iter_ctx ctx;
    ctx.m = m;
    ctx.stream = NULL;
    h2_ihash_iter(m->streams, latest_repeatable_unsubmitted_iter, &ctx);
    return ctx.stream;
}

static int timed_out_busy_iter(void *data, void *val)
{
    stream_iter_ctx *ctx = data;
    h2_stream *stream = val;
    if (stream->task && !stream->task->worker_done
        && (ctx->now - stream->task->started_at) > stream->task->timeout) {
        /* timed out stream occupying a worker, found */
        ctx->stream = stream;
        return 0;
    }
    return 1;
}

static h2_stream *get_timed_out_busy_stream(h2_mplx *m) 
{
    stream_iter_ctx ctx;
    ctx.m = m;
    ctx.stream = NULL;
    ctx.now = apr_time_now();
    h2_ihash_iter(m->streams, timed_out_busy_iter, &ctx);
    return ctx.stream;
}

static apr_status_t unschedule_slow_tasks(h2_mplx *m) 
{
    h2_stream *stream;
    int n;
    
    /* Try to get rid of streams that occupy workers. Look for safe requests
     * that are repeatable. If none found, fail the connection.
     */
    n = (m->tasks_active - m->limit_active - (int)h2_ihash_count(m->sredo));
    while (n > 0 && (stream = get_latest_repeatable_unsubmitted_stream(m))) {
        h2_task_rst(stream->task, H2_ERR_CANCEL);
        h2_ihash_add(m->sredo, stream);
        --n;
    }
    
    if ((m->tasks_active - h2_ihash_count(m->sredo)) > m->limit_active) {
        h2_stream *stream = get_timed_out_busy_stream(m);
        if (stream) {
            /* Too many busy workers, unable to cancel enough streams
             * and with a busy, timed out stream, we tell the client
             * to go away... */
            return APR_TIMEUP;
        }
    }
