void h2_task_rst(h2_task *task, int error)
{
    task->rst_error = error;
    if (task->input.beam) {
        h2_beam_leave(task->input.beam);
    }
    if (!task->worker_done) {
        h2_beam_abort(task->output.beam);
    }
    if (task->c) {
        task->c->aborted = 1;
    }
}