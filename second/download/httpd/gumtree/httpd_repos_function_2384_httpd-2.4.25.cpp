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