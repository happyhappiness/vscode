        h2_iq_clear(m->q);
        leave_mutex(m, acquired);
    }
    return max_stream_started;
}

static void workers_register(h2_mplx *m)
{
    /* h2_workers is only a hub for all the h2_worker instances.
     * At the end-of-life of this h2_mplx, we always unregister at
     * the workers. The thing to manage are all the h2_worker instances
     * out there. Those may hold a reference to this h2_mplx and we cannot
     * call them to unregister.
     * 
     * Therefore: ref counting for h2_workers in not needed, ref counting
     * for h2_worker using this is critical.
     */
    m->need_registration = 0;
    h2_workers_register(m->workers, m);
}

static int io_in_consumed_signal(h2_mplx *m, h2_io *io)
{
    if (io->input_consumed && m->input_consumed) {
        m->input_consumed(m->input_consumed_ctx, 
                          io->id, io->input_consumed);
        io->input_consumed = 0;
        return 1;
    }
    return 0;
}

static int io_out_consumed_signal(h2_mplx *m, h2_io *io)
{
    if (io->output_consumed && io->task && io->task->assigned) {
        h2_req_engine_out_consumed(io->task->assigned, io->task->c, 
                                   io->output_consumed);
        io->output_consumed = 0;
        return 1;
    }
    return 0;
}

static void io_destroy(h2_mplx *m, h2_io *io, int events)
{
    int reuse_slave;
    
    /* cleanup any buffered input */
    h2_io_in_shutdown(io);
    if (events) {
        /* Process outstanding events before destruction */
        io_in_consumed_signal(m, io);
    }
    
    /* The pool is cleared/destroyed which also closes all
     * allocated file handles. Give this count back to our
     * file handle pool. */
    m->tx_handles_reserved += io->files_handles_owned;

    h2_io_set_remove(m->stream_ios, io);
    h2_io_set_remove(m->ready_ios, io);
    if (m->redo_ios) {
        h2_io_set_remove(m->redo_ios, io);
    }

    reuse_slave = ((m->spare_slaves->nelts < m->spare_slaves->nalloc)
                    && !io->rst_error && io->eor);
    if (io->task) {
        conn_rec *slave = io->task->c;
        h2_task_destroy(io->task);
        io->task = NULL;
        
        if (reuse_slave && slave->keepalive == AP_CONN_KEEPALIVE) {
            apr_bucket_delete(io->eor);
            io->eor = NULL;
            APR_ARRAY_PUSH(m->spare_slaves, conn_rec*) = slave;
        }
        else {
            slave->sbh = NULL;
            h2_slave_destroy(slave, NULL);
        }
    }

    if (io->pool) {
        apr_pool_destroy(io->pool);
    }

    check_tx_free(m);
}

static int io_stream_done(h2_mplx *m, h2_io *io, int rst_error) 
{
    /* Remove io from ready set, we will never submit it */
    h2_io_set_remove(m->ready_ios, io);
    if (!io->worker_started || io->worker_done) {
        /* already finished or not even started yet */
        h2_iq_remove(m->q, io->id);
        io_destroy(m, io, 1);
        return 0;
    }
    else {
        /* cleanup once task is done */
        h2_io_make_orphaned(io, rst_error);
        return 1;
    }
}

static int stream_done_iter(void *ctx, h2_io *io)
{
    return io_stream_done((h2_mplx*)ctx, io, 0);
}

static int stream_print(void *ctx, h2_io *io)
{
    h2_mplx *m = ctx;
    if (io && io->request) {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%ld-%d): %s %s %s -> %s %d"
                      "[orph=%d/started=%d/done=%d/eos_in=%d/eos_out=%d]", 
                      m->id, io->id, 
                      io->request->method, io->request->authority, io->request->path,
                      io->response? "http" : (io->rst_error? "reset" : "?"),
                      io->response? io->response->http_status : io->rst_error,
                      io->orphaned, io->worker_started, io->worker_done,
                      io->eos_in, io->eos_out);
    }
    else if (io) {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%ld-%d): NULL -> %s %d"
                      "[orph=%d/started=%d/done=%d/eos_in=%d/eos_out=%d]", 
                      m->id, io->id, 
                      io->response? "http" : (io->rst_error? "reset" : "?"),
                      io->response? io->response->http_status : io->rst_error,
                      io->orphaned, io->worker_started, io->worker_done,
                      io->eos_in, io->eos_out);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%ld-NULL): NULL", m->id);
    }
    return 1;
}

apr_status_t h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
{
    apr_status_t status;
    int acquired;

    h2_workers_unregister(m->workers, m);
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        int i, wait_secs = 5;
        
        /* disable WINDOW_UPDATE callbacks */
        h2_mplx_set_consumed_cb(m, NULL, NULL);
        
        h2_iq_clear(m->q);
        apr_thread_cond_broadcast(m->task_thawed);
        while (!h2_io_set_iter(m->stream_ios, stream_done_iter, m)) {
            /* iterate until all ios have been orphaned or destroyed */
        }
    
        /* If we still have busy workers, we cannot release our memory
         * pool yet, as slave connections have child pools of their respective
         * h2_io's.
         * Any remaining ios are processed in these workers. Any operation 
         * they do on their input/outputs will be errored ECONNRESET/ABORTED, 
         * so processing them should fail and workers *should* return.
         */
        for (i = 0; m->workers_busy > 0; ++i) {
            m->join_wait = wait;
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          "h2_mplx(%ld): release_join, waiting on %d worker to report back", 
                          m->id, (int)h2_io_set_size(m->stream_ios));
                          
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
                                  "%d h2_workers to return, have still %d requests outstanding", 
                                  m->id, i*wait_secs, m->workers_busy,
                                  (int)h2_io_set_size(m->stream_ios));
                    if (i == 1) {
                        h2_io_set_iter(m->stream_ios, stream_print, m);
                    }
                }
                h2_mplx_abort(m);
                apr_thread_cond_broadcast(m->task_thawed);
            }
        }
        
        if (!h2_io_set_is_empty(m->stream_ios)) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, m->c, 
                          "h2_mplx(%ld): release_join, %d streams still open", 
                          m->id, (int)h2_io_set_size(m->stream_ios));
        }
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, APLOGNO(03056)
                      "h2_mplx(%ld): release_join -> destroy", m->id);
        leave_mutex(m, acquired);
        h2_mplx_destroy(m);
        /* all gone */
    }
    return status;
}
