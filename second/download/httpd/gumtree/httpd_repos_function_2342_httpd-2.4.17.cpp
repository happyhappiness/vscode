static apr_status_t h2_filter_stream_output(ap_filter_t* filter,
                                            apr_bucket_brigade* brigade) {
    h2_task_env *env = filter->ctx;
    AP_DEBUG_ASSERT(env);
    if (!env->output) {
        return APR_ECONNABORTED;
    }
    return h2_task_output_write(env->output, filter, brigade);
}