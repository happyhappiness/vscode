apr_status_t h2_task_do(h2_task *task, h2_worker *worker)
{
    apr_status_t status = APR_SUCCESS;
    
    AP_DEBUG_ASSERT(task);
    
    task->serialize_headers = h2_config_geti(task->request->config, H2_CONF_SER_HEADERS);

    status = h2_worker_setup_task(worker, task);
    
    /* save in connection that this one is a pseudo connection */
    h2_ctx_create_for(task->c, task);

    if (status == APR_SUCCESS) {
        task->input = h2_task_input_create(task, task->pool, 
                                           task->c->bucket_alloc);
        task->output = h2_task_output_create(task, task->pool);
        
        ap_process_connection(task->c, h2_worker_get_socket(worker));
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_task(%s): processing done", task->id);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, task->c,
                      APLOGNO(02957) "h2_task(%s): error setting up h2_task", 
                      task->id);
    }
    
    if (task->input) {
        h2_task_input_destroy(task->input);
        task->input = NULL;
    }
    
    if (task->output) {
        h2_task_output_close(task->output);
        h2_task_output_destroy(task->output);
        task->output = NULL;
    }

    if (task->io) {
        apr_thread_cond_signal(task->io);
    }
    
    h2_worker_release_task(worker, task);
    h2_mplx_task_done(task->mplx, task->stream_id);
    
    return status;
}