     EXCEPTIONREGISTRATIONRECORD reg_rec = { NULL, thread_exception_handler };
     ap_sb_handle_t *sbh;
 
     /* Trap exceptions in this thread so we don't take down the whole process */
     DosSetExceptionHandler( &reg_rec );
 
+    osthd = apr_os_thread_current();
+    apr_os_thread_put(&thd, &osthd, pchild);
+
     rc = DosOpenQueue(&owner, &workq,
                       apr_psprintf(pchild, "/queues/httpd/work.%d", getpid()));
 
     if (rc) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf, APLOGNO(00196)
                      "unable to open work queue, exiting");
         ap_scoreboard_image->servers[child_slot][thread_slot].tid = 0;
     }
 
     conn_id = ID_FROM_CHILD_THREAD(child_slot, thread_slot);
     ap_update_child_status_from_indexes(child_slot, thread_slot, SERVER_READY,
