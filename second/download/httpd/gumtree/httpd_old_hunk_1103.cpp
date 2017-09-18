            } else {
                /* Allocate another context.
                 * Note:
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
                break;
            }
        } else {
