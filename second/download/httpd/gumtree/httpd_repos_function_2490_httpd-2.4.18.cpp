static void* APR_THREAD_FUNC execute(apr_thread_t *thread, void *wctx)
{
    h2_worker *worker = (h2_worker *)wctx;
    apr_status_t status = APR_SUCCESS;
    h2_mplx *m;
    (void)thread;
    
    /* Furthermore, other code might want to see the socket for
     * this connection. Allocate one without further function...
     */
    status = apr_socket_create(&worker->socket,
                               APR_INET, SOCK_STREAM,
                               APR_PROTO_TCP, worker->pool);
    if (status != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_ERR, status, worker->pool,
                      APLOGNO(02948) "h2_worker(%d): alloc socket", 
                      worker->id);
        worker->worker_done(worker, worker->ctx);
        return NULL;
    }
    
    worker->task = NULL;
    m = NULL;
    while (!worker->aborted) {
        status = worker->get_next(worker, &m, &worker->task, worker->ctx);
        
        if (worker->task) {            
            h2_task_do(worker->task, worker);
            worker->task = NULL;
            apr_thread_cond_signal(worker->io);
        }
    }

    status = worker->get_next(worker, &m, NULL, worker->ctx);
    m = NULL;
    
    if (worker->socket) {
        apr_socket_close(worker->socket);
        worker->socket = NULL;
    }
    
    worker->worker_done(worker, worker->ctx);
    return NULL;
}