static apr_status_t h2_filter_stream_output(ap_filter_t* filter,
                                            apr_bucket_brigade* brigade)
{
    h2_task *task = h2_ctx_cget_task(filter->c);
    AP_DEBUG_ASSERT(task);
    if (!task->output) {
        return APR_ECONNABORTED;
    }
    return h2_task_output_write(task->output, filter, brigade);
}