static void * APR_THREAD_FUNC worker_thread(apr_thread_t *thd, void * dummy)
{
    proc_info * ti = dummy;
    int process_slot = ti->pid;
    int thread_slot = ti->tid;
    apr_bucket_alloc_t *bucket_alloc;
    apr_pool_t *tpool = apr_thread_pool_get(thd);
    apr_pool_t *ptrans;                /* Pool for per-transaction stuff */
    apr_allocator_t *allocator;
    apr_status_t rv;
    worker_wakeup_info *wakeup;

    free(ti);

    ap_update_child_status_from_indexes(process_slot, thread_slot, SERVER_STARTING, NULL);

    apr_allocator_create(&allocator);
    apr_allocator_max_free_set(allocator, ap_max_mem_free);
    apr_pool_create_ex(&ptrans, NULL, NULL, allocator);
    apr_allocator_owner_set(allocator, ptrans);

    /* XXX: What happens if this is allocated from the
     * single-thread-optimized ptrans pool? -aaron */
    bucket_alloc = apr_bucket_alloc_create(tpool);

    wakeup = (worker_wakeup_info *)apr_palloc(tpool, sizeof(*wakeup));
    wakeup->pool = ptrans;
    if ((rv = apr_thread_cond_create(&wakeup->cond, tpool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                     "apr_thread_cond_create failed. Attempting to shutdown "
                     "process gracefully.");
        signal_threads(ST_GRACEFUL);
        apr_thread_exit(thd, rv);
    }
    if ((rv = apr_thread_mutex_create(&wakeup->mutex, APR_THREAD_MUTEX_DEFAULT,
                                      tpool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                     "apr_thread_mutex_create failed. Attempting to shutdown "
                     "process gracefully.");
        signal_threads(ST_GRACEFUL);
        apr_thread_exit(thd, rv);
    }

    while (!workers_may_exit) {
        ap_update_child_status_from_indexes(process_slot, thread_slot, SERVER_READY, NULL);
        rv = worker_stack_wait(idle_worker_stack, wakeup);
        if (APR_STATUS_IS_EOF(rv)) {
            break; /* The queue has been terminated. */
        }
        else if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                         "worker_stack_wait failed");
            break; /* Treat all other errors as fatal. */
        }
        else if (wakeup->state == WORKER_TERMINATED) {
            break; /* They told us to quit. */
        }
        AP_DEBUG_ASSERT(wakeup->state != WORKER_IDLE);
        process_socket(ptrans, wakeup->csd,
                       process_slot, thread_slot, bucket_alloc);
        requests_this_child--; /* FIXME: should be synchronized - aaron */
        apr_pool_clear(ptrans);
    }

    ap_update_child_status_from_indexes(process_slot, thread_slot,
        (dying) ? SERVER_DEAD : SERVER_GRACEFUL, (request_rec *) NULL);

    apr_bucket_alloc_destroy(bucket_alloc);

    apr_thread_exit(thd, APR_SUCCESS);
    return NULL;
}