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