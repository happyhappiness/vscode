static apr_status_t h2_filter_slave_output(ap_filter_t* filter,
                                           apr_bucket_brigade* brigade)
{
    h2_task *task = h2_ctx_cget_task(filter->c);
    apr_status_t status;
    
    ap_assert(task);
    status = slave_out(task, filter, brigade);
    if (status != APR_SUCCESS) {
        h2_task_rst(task, H2_ERR_INTERNAL_ERROR);
    }
    return status;
}