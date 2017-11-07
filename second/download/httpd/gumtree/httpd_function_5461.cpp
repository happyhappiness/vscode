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