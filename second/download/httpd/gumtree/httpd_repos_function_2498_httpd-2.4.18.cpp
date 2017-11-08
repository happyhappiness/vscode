apr_status_t h2_worker_setup_task(h2_worker *worker, h2_task *task) {
    apr_status_t status;
    
    
    status = h2_conn_setup(task, apr_bucket_alloc_create(task->pool),
                           worker->thread, worker->socket);
    
    return status;
}