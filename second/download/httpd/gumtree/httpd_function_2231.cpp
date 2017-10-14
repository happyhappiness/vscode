PCOMP_CONTEXT mpm_get_completion_context(void)
{
    apr_status_t rv;
    PCOMP_CONTEXT context = NULL;

    while (1) {
        /* Grab a context off the queue */
        apr_thread_mutex_lock(qlock);
        if (qhead) {
            context = qhead;
            qhead = qhead->next;
            if (!qhead)
                qtail = NULL;
        } else {
            ResetEvent(qwait_event);
        }
        apr_thread_mutex_unlock(qlock);

        if (!context) {
            /* We failed to grab a context off the queue, consider allocating
             * a new one out of the child pool. There may be up to
             * (ap_threads_per_child + num_listeners) contexts in the system
             * at once.
             */
            if (num_completion_contexts >= max_num_completion_contexts) {
                /* All workers are busy, need to wait for one */
                static int reported = 0;
                if (!reported) {
                    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
                                 "Server ran out of threads to serve requests. Consider "
                                 "raising the ThreadsPerChild setting");
                    reported = 1;
                }

                /* Wait for a worker to free a context. Once per second, give
                 * the caller a chance to check for shutdown. If the wait
                 * succeeds, get the context off the queue. It must be available,
                 * since there's only one consumer.
                 */
                rv = WaitForSingleObject(qwait_event, 1000);
                if (rv == WAIT_OBJECT_0)
                    continue;
                else /* Hopefully, WAIT_TIMEOUT */
                    return NULL;
            } else {
                /* Allocate another context.
                 * Note:
                 * Multiple failures in the next two steps will cause the pchild pool
                 * to 'leak' storage. I don't think this is worth fixing...
                 */
                apr_allocator_t *allocator;

                apr_thread_mutex_lock(child_lock);
                context = (PCOMP_CONTEXT) apr_pcalloc(pchild, sizeof(COMP_CONTEXT));

                context->Overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
                if (context->Overlapped.hEvent == NULL) {
                    /* Hopefully this is a temporary condition ... */
                    ap_log_error(APLOG_MARK,APLOG_WARNING, apr_get_os_error(), ap_server_conf,
                                 "mpm_get_completion_context: CreateEvent failed.");

                    apr_thread_mutex_unlock(child_lock);
                    return NULL;
                }

                /* Create the tranaction pool */
                apr_allocator_create(&allocator);
                apr_allocator_max_free_set(allocator, ap_max_mem_free);
                rv = apr_pool_create_ex(&context->ptrans, pchild, NULL, allocator);
                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK,APLOG_WARNING, rv, ap_server_conf,
                                 "mpm_get_completion_context: Failed to create the transaction pool.");
                    CloseHandle(context->Overlapped.hEvent);

                    apr_thread_mutex_unlock(child_lock);
                    return NULL;
                }
                apr_allocator_owner_set(allocator, context->ptrans);
                apr_pool_tag(context->ptrans, "transaction");

                context->accept_socket = INVALID_SOCKET;
                context->ba = apr_bucket_alloc_create(context->ptrans);
                apr_atomic_inc32(&num_completion_contexts);

                apr_thread_mutex_unlock(child_lock);
                break;
            }
        } else {
            /* Got a context from the queue */
            break;
        }
    }

    return context;
}