    stream_iter_ctx_t *x = ctx;
    return x->cb(stream, x->ctx);
}

apr_status_t h2_mplx_stream_do(h2_mplx *m, h2_mplx_stream_cb *cb, void *ctx)
{
    apr_status_t status;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        stream_iter_ctx_t x;
        x.cb = cb;
        x.ctx = ctx;
        h2_ihash_iter(m->streams, stream_iter_wrap, &x);
        
        leave_mutex(m, acquired);
    }
    return status;
}

static int task_print(void *ctx, void *val)
{
    h2_mplx *m = ctx;
    h2_task *task = val;

    if (task) {
        h2_stream *stream = h2_ihash_get(m->streams, task->stream_id);

        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%s): %s %s %s"
                      "[orph=%d/started=%d/done=%d/frozen=%d]", 
                      task->id, task->request->method, 
                      task->request->authority, task->request->path,
                      (stream? 0 : 1), task->worker_started, 
                      task->worker_done, task->frozen);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%ld-NULL): NULL", m->id);
    }
    return 1;
}

static int task_abort_connection(void *ctx, void *val)
{
    h2_task *task = val;
    if (!task->worker_done) { 
        if (task->c) {
            task->c->aborted = 1;
        }
        h2_beam_abort(task->input.beam);
        h2_beam_abort(task->output.beam);
    }
    return 1;
}

static int report_stream_iter(void *ctx, void *val) {
    h2_mplx *m = ctx;
    h2_stream *stream = val;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  "h2_mplx(%ld-%d): exists, started=%d, scheduled=%d, ready=%d", 
                  m->id, stream->id, stream->started, stream->scheduled,
                  h2_stream_is_ready(stream));
    return 1;
}

static int task_done_iter(void *ctx, void *val);

apr_status_t h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
{
    apr_status_t status;
    int acquired;

    /* How to shut down a h2 connection:
     * 1. tell the workers that no more tasks will come from us */
    h2_workers_unregister(m->workers, m);
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        int i, wait_secs = 60;

        /* 2. disable WINDOW_UPDATEs and set the mplx to aborted, clear
         *    our TODO list and purge any streams we have collected */
        h2_mplx_set_consumed_cb(m, NULL, NULL);
        h2_mplx_abort(m);
        h2_iq_clear(m->q);
        purge_streams(m);

        /* 3. wakeup all sleeping tasks. Mark all still active streams as 'done'. 
         *    m->streams has to be empty afterwards with streams either in
         *    a) m->shold because a task is still active
         *    b) m->spurge because task is done, or was not started */
        h2_ihash_iter(m->tasks, task_abort_connection, m);
        apr_thread_cond_broadcast(m->task_thawed);
        while (!h2_ihash_iter(m->streams, stream_done_iter, m)) {
            /* iterate until all streams have been removed */
        }
        ap_assert(h2_ihash_empty(m->streams));

        /* 4. purge all streams we collected by marking them 'done' */
        purge_streams(m);
        
        /* 5. while workers are busy on this connection, meaning they
         *    are processing tasks from this connection, wait on them finishing
         *    to wake us and check again. Eventually, this has to succeed. */    
        m->join_wait = wait;
        for (i = 0; m->workers_busy > 0; ++i) {
            status = apr_thread_cond_timedwait(wait, m->lock, apr_time_from_sec(wait_secs));
            
            if (APR_STATUS_IS_TIMEUP(status)) {
                /* This can happen if we have very long running requests
                 * that do not time out on IO. */
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, APLOGNO(03198)
                              "h2_mplx(%ld): release, waiting for %d seconds now for "
                              "%d h2_workers to return, have still %d tasks outstanding", 
                              m->id, i*wait_secs, m->workers_busy,
                              (int)h2_ihash_count(m->tasks));
                h2_ihash_iter(m->shold, report_stream_iter, m);
                h2_ihash_iter(m->tasks, task_print, m);
            }
            purge_streams(m);
        }
        m->join_wait = NULL;
        
        /* 6. All workers for this connection are done, we are in 
         * single-threaded processing now effectively. */
        leave_mutex(m, acquired);

        if (!h2_ihash_empty(m->tasks)) {
            /* when we are here, we lost track of the tasks still present.
             * this currently happens with mod_proxy_http2 when we shut
             * down a h2_req_engine with tasks assigned. Since no parallel
             * processing is going on any more, we just clean them up. */ 
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c,  APLOGNO(03056)
                          "h2_mplx(%ld): 3. release_join with %d tasks",
                          m->id, (int)h2_ihash_count(m->tasks));
            h2_ihash_iter(m->tasks, task_print, m);
            
            while (!h2_ihash_iter(m->tasks, task_done_iter, m)) {
                /* iterate until all tasks have been removed */
            }
        }

        /* 7. With all tasks done, the stream hold should be empty and all
         *    remaining streams are ready for purging */
        ap_assert(h2_ihash_empty(m->shold));
        purge_streams(m);
        
        /* 8. close the h2_req_enginge shed and self destruct */
        h2_ngn_shed_destroy(m->ngn_shed);
        m->ngn_shed = NULL;
        h2_mplx_destroy(m);
    }
    return status;
}

void h2_mplx_abort(h2_mplx *m)
{
    int acquired;
    
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

h2_stream *h2_mplx_stream_get(h2_mplx *m, int id)
{
    h2_stream *s = NULL;
    int acquired;
    
    if ((enter_mutex(m, &acquired)) == APR_SUCCESS) {
        s = h2_ihash_get(m->streams, id);
        leave_mutex(m, acquired);
    }
    return s;
}

void h2_mplx_set_consumed_cb(h2_mplx *m, h2_mplx_consumed_cb *cb, void *ctx)
{
    m->input_consumed = cb;
    m->input_consumed_ctx = ctx;
}

static void output_produced(void *ctx, h2_bucket_beam *beam, apr_off_t bytes)
{
    h2_mplx *m = ctx;
    apr_status_t status;
    h2_stream *stream;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        stream = h2_ihash_get(m->streams, beam->id);
        if (stream) {
            have_out_data_for(m, stream, 0);
        }
        leave_mutex(m, acquired);
    }
}

static apr_status_t out_open(h2_mplx *m, int stream_id, h2_bucket_beam *beam)
{
    apr_status_t status = APR_SUCCESS;
    h2_task *task = h2_ihash_get(m->tasks, stream_id);
    h2_stream *stream = h2_ihash_get(m->streams, stream_id);
    apr_size_t beamed_count;
    
    if (!task || !stream) {
        return APR_ECONNABORTED;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, m->c,
                  "h2_mplx(%s): out open", task->id);
                      
    h2_beam_on_consumed(stream->output, stream_output_consumed, task);
    h2_beam_on_produced(stream->output, output_produced, m);
    beamed_count = h2_beam_get_files_beamed(stream->output);
    if (m->tx_handles_reserved >= beamed_count) {
        m->tx_handles_reserved -= beamed_count;
    }
    else {
        m->tx_handles_reserved = 0;
    }
    if (!task->output.copy_files) {
        h2_beam_on_file_beam(stream->output, can_beam_file, m);
    }
    
    /* time to protect the beam against multi-threaded use */
    h2_beam_mutex_set(stream->output, beam_enter, task->cond, m);
    
    /* we might see some file buckets in the output, see
     * if we have enough handles reserved. */
    check_tx_reservation(m);
    have_out_data_for(m, stream, 0);
    return status;
}

apr_status_t h2_mplx_out_open(h2_mplx *m, int stream_id, h2_bucket_beam *beam)
{
    apr_status_t status;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            status = out_open(m, stream_id, beam);
        }
        leave_mutex(m, acquired);
    }
    return status;
}

static apr_status_t out_close(h2_mplx *m, h2_task *task)
{
    apr_status_t status = APR_SUCCESS;
    h2_stream *stream;
    
    if (!task) {
        return APR_ECONNABORTED;
    }

    stream = h2_ihash_get(m->streams, task->stream_id);
    if (!stream) {
        return APR_ECONNABORTED;
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
                  "h2_mplx(%s): close", task->id);
    status = h2_beam_close(task->output.beam);
    h2_beam_log(task->output.beam, task->stream_id, "out_close", m->c, 
                APLOG_TRACE2);
    output_consumed_signal(m, task);
    have_out_data_for(m, stream, 0);
    return status;
}

apr_status_t h2_mplx_out_trywait(h2_mplx *m, apr_interval_time_t timeout,
                                 apr_thread_cond_t *iowait)
{
    apr_status_t status;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else if (!h2_iq_empty(m->readyq)) {
            status = APR_SUCCESS;
        }
        else {
            purge_streams(m);
            m->added_output = iowait;
            status = apr_thread_cond_timedwait(m->added_output, m->lock, timeout);
            if (APLOGctrace2(m->c)) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                              "h2_mplx(%ld): trywait on data for %f ms)",
                              m->id, timeout/1000.0);
            }
            m->added_output = NULL;
        }
        leave_mutex(m, acquired);
    }
    return status;
}

static void have_out_data_for(h2_mplx *m, h2_stream *stream, int response)
{
    ap_assert(m);
    ap_assert(stream);
    h2_iq_append(m->readyq, stream->id);
    if (m->added_output) {
        apr_thread_cond_signal(m->added_output);
    }
}

apr_status_t h2_mplx_reprioritize(h2_mplx *m, h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            h2_iq_sort(m->q, cmp, ctx);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          "h2_mplx(%ld): reprioritize tasks", m->id);
        }
        leave_mutex(m, acquired);
    }
    return status;
}

apr_status_t h2_mplx_process(h2_mplx *m, struct h2_stream *stream, 
                             h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    int do_registration = 0;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            h2_ihash_add(m->streams, stream);
            if (h2_stream_is_ready(stream)) {
                h2_iq_append(m->readyq, stream->id);
            }
            else {
                if (!m->need_registration) {
                    m->need_registration = h2_iq_empty(m->q);
                }
                if (m->workers_busy < m->workers_max) {
                    do_registration = m->need_registration;
                }
                h2_iq_add(m->q, stream->id, cmp, ctx);                
            }
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, m->c,
                          "h2_mplx(%ld-%d): process", m->c->id, stream->id);
        }
        leave_mutex(m, acquired);
    }
    if (do_registration) {
        m->need_registration = 0;
        h2_workers_register(m->workers, m);
    }
    return status;
}

static h2_task *next_stream_task(h2_mplx *m)
{
    h2_task *task = NULL;
    h2_stream *stream;
    int sid;
    while (!m->aborted && !task  && (m->workers_busy < m->workers_limit)
           && (sid = h2_iq_shift(m->q)) > 0) {
        
        stream = h2_ihash_get(m->streams, sid);
        if (stream) {
            conn_rec *slave, **pslave;
            int new_conn = 0;

            pslave = (conn_rec **)apr_array_pop(m->spare_slaves);
            if (pslave) {
                slave = *pslave;
            }
            else {
                slave = h2_slave_create(m->c, stream->id, m->pool);
                new_conn = 1;
            }
            
            slave->sbh = m->c->sbh;
            slave->aborted = 0;
            task = h2_task_create(slave, stream->id, stream->request, 
                                  stream->input, stream->output, m);
            h2_ihash_add(m->tasks, task);
            
            m->c->keepalives++;
            apr_table_setn(slave->notes, H2_TASK_ID_NOTE, task->id);
            if (new_conn) {
                h2_slave_run_pre_connection(slave, ap_get_conn_socket(slave));
            }
            stream->started = 1;
            stream->can_be_cleaned = 0;
            task->worker_started = 1;
            task->started_at = apr_time_now();
            if (sid > m->max_stream_started) {
                m->max_stream_started = sid;
            }

            h2_beam_timeout_set(stream->input, m->stream_timeout);
            h2_beam_on_consumed(stream->input, stream_input_consumed, m);
            h2_beam_on_file_beam(stream->input, can_beam_file, m);
            h2_beam_mutex_set(stream->input, beam_enter, task->cond, m);
            
            h2_beam_buffer_size_set(stream->output, m->stream_max_mem);
            h2_beam_timeout_set(stream->output, m->stream_timeout);
            ++m->workers_busy;
        }
    }
    return task;
}

h2_task *h2_mplx_pop_task(h2_mplx *m, int *has_more)
{
    h2_task *task = NULL;
    apr_status_t status;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            *has_more = 0;
        }
        else {
            task = next_stream_task(m);
            *has_more = !h2_iq_empty(m->q);
        }
        
        if (has_more && !task) {
            m->need_registration = 1;
        }
        leave_mutex(m, acquired);
    }
    return task;
}

static void task_done(h2_mplx *m, h2_task *task, h2_req_engine *ngn)
{
    if (task->frozen) {
        /* this task was handed over to an engine for processing 
         * and the original worker has finished. That means the 
         * engine may start processing now. */
        h2_task_thaw(task);
        apr_thread_cond_broadcast(m->task_thawed);
        return;
    }
    else {
        h2_stream *stream;
        
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
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c,
                              "h2_mplx(%ld): task(%s) has not-shutdown "
                              "engine(%s)", m->id, task->id, 
                              h2_req_engine_get_id(task->engine));
            }
            h2_ngn_shed_done_ngn(m->ngn_shed, task->engine);
        }
        
        stream = h2_ihash_get(m->streams, task->stream_id);
        if (!m->aborted && stream 
            && h2_ihash_get(m->redo_tasks, task->stream_id)) {
            /* reset and schedule again */
            h2_task_redo(task);
            h2_ihash_remove(m->redo_tasks, task->stream_id);
            h2_iq_add(m->q, task->stream_id, NULL, NULL);
            return;
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
                && m->workers_limit < m->workers_max) {
                /* Well behaving stream, allow it more workers */
                m->workers_limit = H2MIN(m->workers_limit * 2, 
                                         m->workers_max);
                m->last_limit_change = task->done_at;
                m->need_registration = 1;
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                              "h2_mplx(%ld): increase worker limit to %d",
                              m->id, m->workers_limit);
            }
        }
        
        if (stream) {
            /* hang around until the stream deregisters */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%s): task_done, stream still open", 
                          task->id);
            /* more data will not arrive, resume the stream */
            have_out_data_for(m, stream, 0);
            h2_beam_on_consumed(stream->output, NULL, NULL);
            h2_beam_mutex_set(stream->output, NULL, NULL, NULL);
        }
        else {
            /* stream no longer active, was it placed in hold? */
            stream = h2_ihash_get(m->shold, task->stream_id);
            if (stream) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                              "h2_mplx(%s): task_done, stream %d in hold", 
                              task->id, stream->id);
                /* We cannot destroy the stream here since this is 
                 * called from a worker thread and freeing memory pools
                 * is only safe in the only thread using it (and its
                 * parent pool / allocator) */
                h2_beam_on_consumed(stream->output, NULL, NULL);
                h2_beam_mutex_set(stream->output, NULL, NULL, NULL);
                h2_ihash_remove(m->shold, stream->id);
                h2_ihash_add(m->spurge, stream);
            }
            else {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                              "h2_mplx(%s): task_done, stream not found", 
                              task->id);
                task_destroy(m, task, 0);
            }
        }
    }
}

static int task_done_iter(void *ctx, void *val)
{
    task_done((h2_mplx*)ctx, val, 0);
    return 0;
}

void h2_mplx_task_done(h2_mplx *m, h2_task *task, h2_task **ptask)
{
    int acquired;
    
    if (enter_mutex(m, &acquired) == APR_SUCCESS) {
        task_done(m, task, NULL);
        --m->workers_busy;
        if (m->join_wait) {
            apr_thread_cond_signal(m->join_wait);
        }
        if (ptask) {
            /* caller wants another task */
            *ptask = next_stream_task(m);
        }
        leave_mutex(m, acquired);
    }
}

/*******************************************************************************
 * h2_mplx DoS protection
 ******************************************************************************/

static int latest_repeatable_unsubmitted_iter(void *data, void *val)
{
    task_iter_ctx *ctx = data;
    h2_stream *stream;
    h2_task *task = val;
    if (!task->worker_done && h2_task_can_redo(task) 
        && !h2_ihash_get(ctx->m->redo_tasks, task->stream_id)) {
        stream = h2_ihash_get(ctx->m->streams, task->stream_id);
        if (stream && !h2_stream_is_ready(stream)) {
            /* this task occupies a worker, the response has not been submitted 
             * yet, not been cancelled and it is a repeatable request
             * -> it can be re-scheduled later */
            if (!ctx->task || ctx->task->started_at < task->started_at) {
                /* we did not have one or this one was started later */
                ctx->task = task;
            }
        }
    }
    return 1;
}

static h2_task *get_latest_repeatable_unsubmitted_task(h2_mplx *m) 
{
    task_iter_ctx ctx;
    ctx.m = m;
    ctx.task = NULL;
    h2_ihash_iter(m->tasks, latest_repeatable_unsubmitted_iter, &ctx);
    return ctx.task;
}

static int timed_out_busy_iter(void *data, void *val)
{
    task_iter_ctx *ctx = data;
    h2_task *task = val;
    if (!task->worker_done
        && (ctx->now - task->started_at) > ctx->m->stream_timeout) {
        /* timed out stream occupying a worker, found */
        ctx->task = task;
        return 0;
    }
    return 1;
}

static h2_task *get_timed_out_busy_task(h2_mplx *m) 
{
    task_iter_ctx ctx;
    ctx.m = m;
    ctx.task = NULL;
    ctx.now = apr_time_now();
    h2_ihash_iter(m->tasks, timed_out_busy_iter, &ctx);
    return ctx.task;
}

static apr_status_t unschedule_slow_tasks(h2_mplx *m) 
{
    h2_task *task;
    int n;
    
    /* Try to get rid of streams that occupy workers. Look for safe requests
     * that are repeatable. If none found, fail the connection.
     */
    n = (m->workers_busy - m->workers_limit - (int)h2_ihash_count(m->redo_tasks));
    while (n > 0 && (task = get_latest_repeatable_unsubmitted_task(m))) {
        h2_task_rst(task, H2_ERR_CANCEL);
        h2_ihash_add(m->redo_tasks, task);
        --n;
    }
    
    if ((m->workers_busy - h2_ihash_count(m->redo_tasks)) > m->workers_limit) {
        task = get_timed_out_busy_task(m);
        if (task) {
            /* Too many busy workers, unable to cancel enough streams
             * and with a busy, timed out stream, we tell the client
             * to go away... */
            return APR_TIMEUP;
        }
    }
