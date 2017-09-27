        
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
