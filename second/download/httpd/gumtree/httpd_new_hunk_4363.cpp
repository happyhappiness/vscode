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
