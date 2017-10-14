static apr_status_t send_out(h2_task *task, apr_bucket_brigade* bb)
{
    apr_off_t written, left;
    apr_status_t status;

    apr_brigade_length(bb, 0, &written);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                  "h2_task(%s): write response body (%ld bytes)", 
                  task->id, (long)written);
    
    status = h2_beam_send(task->output.beam, bb, 
                          task->blocking? APR_BLOCK_READ
                          : APR_NONBLOCK_READ);
    if (APR_STATUS_IS_EAGAIN(status)) {
        apr_brigade_length(bb, 0, &left);
        written -= left;
        status = APR_SUCCESS;
    }
    if (status == APR_SUCCESS) {
        task->output.written += written;
        if (h2_task_logio_add_bytes_out) {
            h2_task_logio_add_bytes_out(task->c, written);
        }
    }
    return status;
}