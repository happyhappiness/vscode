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