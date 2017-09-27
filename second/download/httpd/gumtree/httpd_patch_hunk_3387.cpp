 
                 context->overlapped.hEvent = CreateEvent(NULL, TRUE,
                                                          FALSE, NULL);
                 if (context->overlapped.hEvent == NULL) {
                     /* Hopefully this is a temporary condition ... */
                     ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_os_error(),
-                                 ap_server_conf,
+                                 ap_server_conf, APLOGNO(00329)
                                  "mpm_get_completion_context: "
                                  "CreateEvent failed.");
 
                     apr_thread_mutex_unlock(child_lock);
                     return NULL;
                 }
 
                 /* Create the transaction pool */
                 apr_allocator_create(&allocator);
                 apr_allocator_max_free_set(allocator, ap_max_mem_free);
-                rv = apr_pool_create_ex(&context->ptrans, pchild, NULL, 
+                rv = apr_pool_create_ex(&context->ptrans, pchild, NULL,
                                         allocator);
                 if (rv != APR_SUCCESS) {
-                    ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
+                    ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf, APLOGNO(00330)
                                  "mpm_get_completion_context: Failed "
                                  "to create the transaction pool.");
                     CloseHandle(context->overlapped.hEvent);
 
                     apr_thread_mutex_unlock(child_lock);
                     return NULL;
