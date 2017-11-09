static int output_consumed_signal(h2_mplx *m, h2_task *task)
{
    if (task->output.beam) {
        return h2_beam_report_consumption(task->output.beam);
    }
    return 0;
}