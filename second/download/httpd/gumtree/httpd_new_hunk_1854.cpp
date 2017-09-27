             */
            if (num_completion_contexts >= max_num_completion_contexts) {
                /* All workers are busy, need to wait for one */
                static int reported = 0;
                if (!reported) {
                    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
                                 "Server ran out of threads to serve "
                                 "requests. Consider raising the "
                                 "ThreadsPerChild setting");
                    reported = 1;
                }

                /* Wait for a worker to free a context. Once per second, give
                 * the caller a chance to check for shutdown. If the wait
                 * succeeds, get the context off the queue. It must be
                 * available, since there's only one consumer.
                 */
                rv = WaitForSingleObject(qwait_event, 1000);
                if (rv == WAIT_OBJECT_0)
                    continue;
                else /* Hopefully, WAIT_TIMEOUT */
                    return NULL;
            } else {
                /* Allocate another context.
                 * Note: Multiple failures in the next two steps will cause
                 * the pchild pool to 'leak' storage. I don't think this
                 * is worth fixing...
                 */
                apr_allocator_t *allocator;

                apr_thread_mutex_lock(child_lock);
                context = (winnt_conn_ctx_t *)apr_pcalloc(pchild,
                                                     sizeof(winnt_conn_ctx_t));


                context->overlapped.hEvent = CreateEvent(NULL, TRUE,
                                                         FALSE, NULL);
                if (context->overlapped.hEvent == NULL) {
                    /* Hopefully this is a temporary condition ... */
                    ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_os_error(),
                                 ap_server_conf,
                                 "mpm_get_completion_context: "
                                 "CreateEvent failed.");

                    apr_thread_mutex_unlock(child_lock);
                    return NULL;
                }

                /* Create the transaction pool */
                apr_allocator_create(&allocator);
                apr_allocator_max_free_set(allocator, ap_max_mem_free);
                rv = apr_pool_create_ex(&context->ptrans, pchild, NULL, 
                                        allocator);
                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
                                 "mpm_get_completion_context: Failed "
                                 "to create the transaction pool.");
                    CloseHandle(context->overlapped.hEvent);

                    apr_thread_mutex_unlock(child_lock);
                    return NULL;
                }
                apr_allocator_owner_set(allocator, context->ptrans);
                apr_pool_tag(context->ptrans, "transaction");
