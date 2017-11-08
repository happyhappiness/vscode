static apr_status_t write_brigade_raw(h2_task_output *output, 
                                      ap_filter_t* f, apr_bucket_brigade* bb)
{
    apr_off_t written, left;
    apr_status_t status;

    apr_brigade_length(bb, 0, &written);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, output->task->c,
                  "h2_task(%s): write response body (%ld bytes)", 
                  output->task->id, (long)written);
    
    status = h2_mplx_out_write(output->task->mplx, output->task->stream_id, 
                               f, output->task->blocking, bb, output->task->io);
    if (status == APR_INCOMPLETE) {
        apr_brigade_length(bb, 0, &left);
        written -= left;
        status = APR_SUCCESS;
    }

    if (status == APR_SUCCESS) {
        output->written += written;
        if (h2_task_logio_add_bytes_out) {
            h2_task_logio_add_bytes_out(output->task->c, written);
        }
    }
    return status;
}