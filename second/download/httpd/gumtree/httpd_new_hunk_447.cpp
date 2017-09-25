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
                context->ba = apr_bucket_alloc_create(pchild);
                apr_atomic_inc(&num_completion_contexts); 

                apr_thread_mutex_unlock(child_lock);
                break;
            }
        } else {
            /* Got a context from the queue */
            break;
        }
