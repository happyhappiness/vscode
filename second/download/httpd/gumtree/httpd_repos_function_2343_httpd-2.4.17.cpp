static apr_status_t h2_filter_read_response(ap_filter_t* f,
                                            apr_bucket_brigade* bb) {
    h2_task_env *env = f->ctx;
    AP_DEBUG_ASSERT(env);
    if (!env->output || !env->output->from_h1) {
        return APR_ECONNABORTED;
    }
    return h2_from_h1_read_response(env->output->from_h1, f, bb);
}