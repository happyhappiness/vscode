static int output_consumed_signal(h2_mplx *m, h2_task *task)
{
    if (task->output.beam && task->worker_started && task->assigned) {
        /* trigger updates */
        h2_beam_send(task->output.beam, NULL, APR_NONBLOCK_READ);
    }
    return 0;
}