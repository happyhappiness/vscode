apr_status_t h2_task_do(h2_task *task, h2_worker *worker)
{
    apr_status_t status = APR_SUCCESS;
    h2_config *cfg = h2_config_get(task->mplx->c);
    h2_task_env env; 
    
    AP_DEBUG_ASSERT(task);
    
    memset(&env, 0, sizeof(env));
    
    env.id = task->id;
    env.stream_id = task->stream_id;
    env.mplx = task->mplx;
    task->mplx = NULL;
    
    env.input_eos = task->input_eos;
    env.serialize_headers = h2_config_geti(cfg, H2_CONF_SER_HEADERS);
    
    /* Create a subpool from the worker one to be used for all things
     * with life-time of this task_env execution.
     */
    apr_pool_create(&env.pool, h2_worker_get_pool(worker));

    /* Link the env to the worker which provides useful things such
     * as mutex, a socket etc. */
    env.io = h2_worker_get_cond(worker);
    
    /* Clone fields, so that lifetimes become (more) independent. */
    env.method    = apr_pstrdup(env.pool, task->method);
    env.scheme    = apr_pstrdup(env.pool, task->scheme);
    env.authority = apr_pstrdup(env.pool, task->authority);
    env.path      = apr_pstrdup(env.pool, task->path);
    env.headers   = apr_table_clone(env.pool, task->headers);
    
    /* Setup the pseudo connection to use our own pool and bucket_alloc */
    env.c = *task->c;
    task->c = NULL;
    status = h2_conn_setup(&env, worker);
    
    /* save in connection that this one is a pseudo connection, prevents
     * other hooks from messing with it. */
    h2_ctx_create_for(&env.c, &env);

    if (status == APR_SUCCESS) {
        env.input = h2_task_input_create(&env, env.pool, 
                                         env.c.bucket_alloc);
        env.output = h2_task_output_create(&env, env.pool,
                                           env.c.bucket_alloc);
        status = h2_conn_process(&env.c, h2_worker_get_socket(worker));
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, &env.c,
                      "h2_task(%s): processing done", env.id);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, &env.c,
                      APLOGNO(02957) "h2_task(%s): error setting up h2_task_env", 
                      env.id);
    }
    
    if (env.input) {
        h2_task_input_destroy(env.input);
        env.input = NULL;
    }
    
    if (env.output) {
        h2_task_output_close(env.output);
        h2_task_output_destroy(env.output);
        env.output = NULL;
    }

    h2_task_set_finished(task);
    if (env.io) {
        apr_thread_cond_signal(env.io);
    }
    
    if (env.pool) {
        apr_pool_destroy(env.pool);
        env.pool = NULL;
    }
    
    if (env.c.id) {
        h2_conn_post(&env.c, worker);
    }
    
    h2_mplx_task_done(env.mplx, env.stream_id);
    
    return status;
}