void h2_task_output_close(h2_task_output *output)
{
    open_if_needed(output, NULL, NULL);
    if (output->state != H2_TASK_OUT_DONE) {
        h2_mplx_out_close(output->task->mplx, output->task->stream_id, 
                          get_trailers(output));
        output->state = H2_TASK_OUT_DONE;
    }
}