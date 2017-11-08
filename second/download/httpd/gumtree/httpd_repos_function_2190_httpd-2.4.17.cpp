h2_task_output *h2_task_output_create(h2_task_env *env, apr_pool_t *pool,
                                      apr_bucket_alloc_t *bucket_alloc)
{
    h2_task_output *output = apr_pcalloc(pool, sizeof(h2_task_output));
    
    (void)bucket_alloc;
    if (output) {
        output->env = env;
        output->state = H2_TASK_OUT_INIT;
        output->from_h1 = h2_from_h1_create(env->stream_id, pool);
        if (!output->from_h1) {
            return NULL;
        }
    }
    return output;
}