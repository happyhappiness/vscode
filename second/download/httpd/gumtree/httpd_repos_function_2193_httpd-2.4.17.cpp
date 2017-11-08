void h2_task_output_close(h2_task_output *output)
{
    open_if_needed(output, NULL, NULL);
    if (output->state != H2_TASK_OUT_DONE) {
        h2_mplx_out_close(output->env->mplx, output->env->stream_id);
        output->state = H2_TASK_OUT_DONE;
    }
}