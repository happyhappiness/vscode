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