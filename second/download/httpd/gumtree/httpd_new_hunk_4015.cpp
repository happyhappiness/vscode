    }
}

apr_status_t h2_mplx_reprioritize(h2_mplx *m, h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
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

static h2_io *open_io(h2_mplx *m, int stream_id, const h2_request *request)
{
    apr_pool_t *io_pool;
    h2_io *io;
    
    apr_pool_create(&io_pool, m->pool);
    apr_pool_tag(io_pool, "h2_io");
    io = h2_io_create(stream_id, io_pool, m->bucket_alloc, request);
    h2_io_set_add(m->stream_ios, io);
    
    return io;
}


apr_status_t h2_mplx_process(h2_mplx *m, int stream_id, 
                             const h2_request *req, 
                             h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    int do_registration = 0;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            h2_io *io = open_io(m, stream_id, req);
            
            if (!io->request->body) {
                status = h2_io_in_close(io);
            }
            
            m->need_registration = m->need_registration || h2_iq_empty(m->q);
            do_registration = (m->need_registration && m->workers_busy < m->workers_max);
            h2_iq_add(m->q, io->id, cmp, ctx);
            
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, m->c,
                          "h2_mplx(%ld-%d): process", m->c->id, stream_id);
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_process");
        }
        leave_mutex(m, acquired);
    }
    if (status == APR_SUCCESS && do_registration) {
        workers_register(m);
    }
    return status;
}

static h2_task *pop_task(h2_mplx *m)
{
    h2_task *task = NULL;
    int sid;
    while (!m->aborted && !task 
        && (m->workers_busy < m->workers_limit)
        && (sid = h2_iq_shift(m->q)) > 0) {
        h2_io *io = h2_io_set_get(m->stream_ios, sid);
        if (io && io->orphaned) {
            io_destroy(m, io, 0);
            if (m->join_wait) {
                apr_thread_cond_signal(m->join_wait);
            }
        }
        else if (io) {
            conn_rec *slave, **pslave;
            int new_conn = 0;
            
            pslave = (conn_rec **)apr_array_pop(m->spare_slaves);
            if (pslave) {
                slave = *pslave;
            }
            else {
                slave = h2_slave_create(m->c, m->pool, NULL);
                new_conn = 1;
            }
            
            slave->sbh = m->c->sbh;
            io->task = task = h2_task_create(m->id, io->request, slave, m);
            m->c->keepalives++;
            apr_table_setn(slave->notes, H2_TASK_ID_NOTE, task->id);
            if (new_conn) {
                h2_slave_run_pre_connection(slave, ap_get_conn_socket(slave));
            }
            io->worker_started = 1;
            io->started_at = apr_time_now();
            if (sid > m->max_stream_started) {
                m->max_stream_started = sid;
            }
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
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            *has_more = 0;
        }
        else {
            task = pop_task(m);
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
    if (task) {
        h2_io *io = h2_io_set_get(m->stream_ios, task->stream_id);
        
        if (task->frozen) {
            /* this task was handed over to an engine for processing 
             * and the original worker has finished. That means the 
             * engine may start processing now. */
            h2_task_thaw(task);
            /* we do not want the task to block on writing response
             * bodies into the mplx. */
            /* FIXME: this implementation is incomplete. */
            h2_task_set_io_blocking(task, 0);
            apr_thread_cond_broadcast(m->task_thawed);
        }
        else {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          "h2_mplx(%ld): task(%s) done", m->id, task->id);
            /* clean our references and report request as done. Signal
             * that we want another unless we have been aborted */
            /* TODO: this will keep a worker attached to this h2_mplx as
             * long as it has requests to handle. Might no be fair to
             * other mplx's. Perhaps leave after n requests? */
            h2_mplx_out_close(m, task->stream_id);
            
            if (ngn && io) {
                apr_off_t bytes = io->output_consumed + h2_io_out_length(io);
                if (bytes > 0) {
                    /* we need to report consumed and current buffered output
                     * to the engine. The request will be streamed out or cancelled,
                     * no more data is coming from it and the engine should update
                     * its calculations before we destroy this information. */
                    h2_req_engine_out_consumed(ngn, task->c, bytes);
                    io->output_consumed = 0;
                }
            }
            
            if (task->engine) {
                if (!h2_req_engine_is_shutdown(task->engine)) {
                    ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c,
                                  "h2_mplx(%ld): task(%s) has not-shutdown "
                                  "engine(%s)", m->id, task->id, 
                                  h2_req_engine_get_id(task->engine));
                }
                h2_ngn_shed_done_ngn(m->ngn_shed, task->engine);
            }
            
            if (io) {
                apr_time_t now = apr_time_now();
                if (!io->orphaned && m->redo_ios
                    && h2_io_set_get(m->redo_ios, io->id)) {
                    /* reset and schedule again */
                    h2_io_redo(io);
                    h2_io_set_remove(m->redo_ios, io);
                    h2_iq_add(m->q, io->id, NULL, NULL);
                }
                else {
                    io->worker_done = 1;
                    io->done_at = now;
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                                  "h2_mplx(%ld): request(%d) done, %f ms"
                                  " elapsed", m->id, io->id, 
                                  (io->done_at - io->started_at) / 1000.0);
                    if (io->started_at > m->last_idle_block) {
                        /* this task finished without causing an 'idle block', e.g.
                         * a block by flow control.
                         */
                        if (now - m->last_limit_change >= m->limit_change_interval
                            && m->workers_limit < m->workers_max) {
                            /* Well behaving stream, allow it more workers */
                            m->workers_limit = H2MIN(m->workers_limit * 2, 
                                                     m->workers_max);
                            m->last_limit_change = now;
                            m->need_registration = 1;
                            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                                          "h2_mplx(%ld): increase worker limit to %d",
                                          m->id, m->workers_limit);
                        }
                    }
                }
                
                if (io->orphaned) {
                    io_destroy(m, io, 0);
                    if (m->join_wait) {
                        apr_thread_cond_signal(m->join_wait);
                    }
                }
                else {
                    /* hang around until the stream deregisters */
                }
            }
            else {
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c,
                              "h2_mplx(%ld): task %s without corresp. h2_io",
                              m->id, task->id);
            }
        }
    }
}

void h2_mplx_task_done(h2_mplx *m, h2_task *task, h2_task **ptask)
{
    int acquired;
    
    if (enter_mutex(m, &acquired) == APR_SUCCESS) {
        task_done(m, task, NULL);
        --m->workers_busy;
        if (ptask) {
            /* caller wants another task */
            *ptask = pop_task(m);
        }
        leave_mutex(m, acquired);
    }
}

/*******************************************************************************
 * h2_mplx DoS protection
 ******************************************************************************/

typedef struct {
    h2_mplx *m;
    h2_io *io;
    apr_time_t now;
} io_iter_ctx;

static int latest_repeatable_busy_unsubmitted_iter(void *data, h2_io *io)
{
    io_iter_ctx *ctx = data;
    if (io->worker_started && !io->worker_done
        && h2_io_is_repeatable(io)
        && !h2_io_set_get(ctx->m->redo_ios, io->id)) {
        /* this io occupies a worker, the response has not been submitted yet,
         * not been cancelled and it is a repeatable request
         * -> it can be re-scheduled later */
        if (!ctx->io || ctx->io->started_at < io->started_at) {
            /* we did not have one or this one was started later */
            ctx->io = io;
        }
    }
    return 1;
}

static h2_io *get_latest_repeatable_busy_unsubmitted_io(h2_mplx *m) 
{
    io_iter_ctx ctx;
    ctx.m = m;
    ctx.io = NULL;
    h2_io_set_iter(m->stream_ios, latest_repeatable_busy_unsubmitted_iter, &ctx);
    return ctx.io;
}

static int timed_out_busy_iter(void *data, h2_io *io)
{
    io_iter_ctx *ctx = data;
    if (io->worker_started && !io->worker_done
        && (ctx->now - io->started_at) > ctx->m->stream_timeout) {
        /* timed out stream occupying a worker, found */
        ctx->io = io;
        return 0;
    }
    return 1;
}
static h2_io *get_timed_out_busy_stream(h2_mplx *m) 
{
    io_iter_ctx ctx;
    ctx.m = m;
    ctx.io = NULL;
    ctx.now = apr_time_now();
    h2_io_set_iter(m->stream_ios, timed_out_busy_iter, &ctx);
    return ctx.io;
}

static apr_status_t unschedule_slow_ios(h2_mplx *m) 
{
    h2_io *io;
    int n;
    
    if (!m->redo_ios) {
        m->redo_ios = h2_io_set_create(m->pool);
    }
    /* Try to get rid of streams that occupy workers. Look for safe requests
     * that are repeatable. If none found, fail the connection.
     */
    n = (m->workers_busy - m->workers_limit - h2_io_set_size(m->redo_ios));
    while (n > 0 && (io = get_latest_repeatable_busy_unsubmitted_io(m))) {
        h2_io_set_add(m->redo_ios, io);
        h2_io_rst(io, H2_ERR_CANCEL);
        --n;
    }
    
    if ((m->workers_busy - h2_io_set_size(m->redo_ios)) > m->workers_limit) {
        io = get_timed_out_busy_stream(m);
        if (io) {
            /* Too many busy workers, unable to cancel enough streams
             * and with a busy, timed out stream, we tell the client
             * to go away... */
            return APR_TIMEUP;
        }
    }
    return APR_SUCCESS;
}

apr_status_t h2_mplx_idle(h2_mplx *m)
{
    apr_status_t status = APR_SUCCESS;
    apr_time_t now;            
    int acquired;
    
    if (enter_mutex(m, &acquired) == APR_SUCCESS) {
        apr_size_t scount = h2_io_set_size(m->stream_ios);
        if (scount > 0 && m->workers_busy) {
            /* If we have streams in connection state 'IDLE', meaning
             * all streams are ready to sent data out, but lack
             * WINDOW_UPDATEs. 
             * 
             * This is ok, unless we have streams that still occupy
             * h2 workers. As worker threads are a scarce resource, 
             * we need to take measures that we do not get DoSed.
             * 
             * This is what we call an 'idle block'. Limit the amount 
             * of busy workers we allow for this connection until it
             * well behaves.
             */
            now = apr_time_now();
            m->last_idle_block = now;
            if (m->workers_limit > 2 
                && now - m->last_limit_change >= m->limit_change_interval) {
                if (m->workers_limit > 16) {
                    m->workers_limit = 16;
                }
                else if (m->workers_limit > 8) {
                    m->workers_limit = 8;
                }
                else if (m->workers_limit > 4) {
                    m->workers_limit = 4;
                }
                else if (m->workers_limit > 2) {
                    m->workers_limit = 2;
                }
                m->last_limit_change = now;
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                              "h2_mplx(%ld): decrease worker limit to %d",
                              m->id, m->workers_limit);
            }
            
            if (m->workers_busy > m->workers_limit) {
                status = unschedule_slow_ios(m);
            }
        }
        leave_mutex(m, acquired);
    }
    return status;
}

/*******************************************************************************
 * HTTP/2 request engines
 ******************************************************************************/

typedef struct {
    h2_mplx * m;
    h2_req_engine *ngn;
    int streams_updated;
} ngn_update_ctx;

static int ngn_update_window(void *ctx, h2_io *io)
{
    ngn_update_ctx *uctx = ctx;
    if (io && io->task && io->task->assigned == uctx->ngn
        && io_out_consumed_signal(uctx->m, io)) {
        ++uctx->streams_updated;
    }
    return 1;
}

static apr_status_t ngn_out_update_windows(h2_mplx *m, h2_req_engine *ngn)
{
    ngn_update_ctx ctx;
        
    ctx.m = m;
    ctx.ngn = ngn;
    ctx.streams_updated = 0;
    h2_io_set_iter(m->stream_ios, ngn_update_window, &ctx);
    
    return ctx.streams_updated? APR_SUCCESS : APR_EAGAIN;
}

apr_status_t h2_mplx_req_engine_push(const char *ngn_type, 
                                     request_rec *r,
                                     http2_req_engine_init *einit)
{
    apr_status_t status;
    h2_mplx *m;
    h2_task *task;
    int acquired;
    
    task = h2_ctx_rget_task(r);
    if (!task) {
        return APR_ECONNABORTED;
    }
    m = task->mplx;
    task->r = r;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, task->stream_id);
        if (!io || io->orphaned) {
            status = APR_ECONNABORTED;
        }
        else {
            status = h2_ngn_shed_push_task(m->ngn_shed, ngn_type, task, einit);
        }
        leave_mutex(m, acquired);
    }
    return status;
}

apr_status_t h2_mplx_req_engine_pull(h2_req_engine *ngn, 
                                     apr_read_type_e block, 
                                     apr_uint32_t capacity, 
                                     request_rec **pr)
{   
    h2_ngn_shed *shed = h2_ngn_shed_get_shed(ngn);
    h2_mplx *m = h2_ngn_shed_get_ctx(shed);
    apr_status_t status;
    h2_task *task = NULL;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        int want_shutdown = (block == APR_BLOCK_READ);

        /* Take this opportunity to update output consummation 
         * for this engine */
        ngn_out_update_windows(m, ngn);
        
        if (want_shutdown && !h2_iq_empty(m->q)) {
            /* For a blocking read, check first if requests are to be
             * had and, if not, wait a short while before doing the
             * blocking, and if unsuccessful, terminating read.
             */
            status = h2_ngn_shed_pull_task(shed, ngn, capacity, 1, &task);
            if (APR_STATUS_IS_EAGAIN(status)) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                              "h2_mplx(%ld): start block engine pull", m->id);
                apr_thread_cond_timedwait(m->task_thawed, m->lock, 
                                          apr_time_from_msec(20));
                status = h2_ngn_shed_pull_task(shed, ngn, capacity, 1, &task);
            }
        }
        else {
            status = h2_ngn_shed_pull_task(shed, ngn, capacity,
                                           want_shutdown, &task);
        }
        leave_mutex(m, acquired);
    }
    *pr = task? task->r : NULL;
    return status;
}
 
void h2_mplx_req_engine_done(h2_req_engine *ngn, conn_rec *r_conn)
{
    h2_task *task = h2_ctx_cget_task(r_conn);
    
    if (task) {
        h2_mplx *m = task->mplx;
        int acquired;

        if (enter_mutex(m, &acquired) == APR_SUCCESS) {
            ngn_out_update_windows(m, ngn);
            h2_ngn_shed_done_task(m->ngn_shed, ngn, task);
            if (task->engine) { 
                /* cannot report that as done until engine returns */
            }
            else {
                task_done(m, task, ngn);
            }
            /* Take this opportunity to update output consummation 
             * for this engine */
            leave_mutex(m, acquired);
        }
    }
}
                                
