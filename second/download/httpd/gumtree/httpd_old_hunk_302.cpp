     */
    if (context) {
        apr_pool_clear(context->ptrans);
        context->next = NULL;
        ResetEvent(context->Overlapped.hEvent);
        apr_thread_mutex_lock(qlock);
        if (qtail)
            qtail->next = context;
        else
            qhead = context;
        qtail = context;
        apr_thread_mutex_unlock(qlock);
    }
}

AP_DECLARE(PCOMP_CONTEXT) mpm_get_completion_context(void)
{
    apr_status_t rv;
    PCOMP_CONTEXT context = NULL;

    /* Grab a context off the queue */
    apr_thread_mutex_lock(qlock);
    if (qhead) {
        context = qhead;
        qhead = qhead->next;
        if (!qhead)
            qtail = NULL;
    }
    apr_thread_mutex_unlock(qlock);

    /* If we failed to grab a context off the queue, alloc one out of 
     * the child pool. There may be up to ap_threads_per_child contexts
     * in the system at once.
     */
    if (!context) {
        if (num_completion_contexts >= ap_threads_per_child) {
            static int reported = 0;
            if (!reported) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
                             "Server ran out of threads to serve requests. Consider "
                             "raising the ThreadsPerChild setting");
                reported = 1;
            }
            return NULL;
        }
        /* Note:
         * Multiple failures in the next two steps will cause the pchild pool
         * to 'leak' storage. I don't think this is worth fixing...
         */
        context = (PCOMP_CONTEXT) apr_pcalloc(pchild, sizeof(COMP_CONTEXT));

        context->Overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (context->Overlapped.hEvent == NULL) {
            /* Hopefully this is a temporary condition ... */
            ap_log_error(APLOG_MARK,APLOG_WARNING, apr_get_os_error(), ap_server_conf,
                         "mpm_get_completion_context: CreateEvent failed.");
            return NULL;
        }

        /* Create the tranaction pool */
        if ((rv = apr_pool_create(&context->ptrans, pchild)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK,APLOG_WARNING, rv, ap_server_conf,
                         "mpm_get_completion_context: Failed to create the transaction pool.");
            CloseHandle(context->Overlapped.hEvent);
            return NULL;
        }
        apr_pool_tag(context->ptrans, "ptrans");

        context->accept_socket = INVALID_SOCKET;
        context->ba = apr_bucket_alloc_create(pchild);
        apr_atomic_inc(&num_completion_contexts);
    }

    return context;
}

AP_DECLARE(apr_status_t) mpm_post_completion_context(PCOMP_CONTEXT context, 
