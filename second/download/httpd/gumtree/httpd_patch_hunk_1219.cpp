         apr_ctime(timestamp, apr_time_now());
         apr_file_open_stderr(&se, dbc->pool);
         apr_file_printf(se, "[%s] %s\n", timestamp, dbc->lastError);
     }
 }
 
+static APR_INLINE int odbc_check_rollback(apr_dbd_t *handle)
+{
+    if (handle->can_commit == APR_DBD_TRANSACTION_ROLLBACK) {
+        handle->lasterrorcode = SQL_ERROR;
+        strcpy(handle->lastError, "[dbd_odbc] Rollback pending ");
+        return 1;
+    }
+    return 0;
+}
 /*
 *   public functions per DBD driver API
 */
 
 /** init: allow driver to perform once-only initialisation. **/
 static void odbc_init(apr_pool_t *pool)
