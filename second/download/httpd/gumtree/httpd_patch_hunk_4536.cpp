     if (task->assigned) {
         --task->assigned->no_assigned;
         --task->assigned->no_live;
         task->assigned = NULL;
     }
     
+    if (task->engine) {
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c, 
+                      "h2_ngn_shed(%ld): push task(%s) hosting engine %s " 
+                      "already with %d tasks", 
+                      shed->c->id, task->id, task->engine->id,
+                      task->engine->no_assigned);
+        task->assigned = task->engine;
+        ngn_add_task(task->engine, task, r);
+        return APR_SUCCESS;
+    }
+    
     ngn = apr_hash_get(shed->ngns, ngn_type, APR_HASH_KEY_STRING);
     if (ngn && !ngn->shutdown) {
         /* this task will be processed in another thread,
          * freeze any I/O for the time being. */
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                       "h2_ngn_shed(%ld): pushing request %s to %s", 
                       shed->c->id, task->id, ngn->id);
         if (!h2_task_has_thawed(task)) {
             h2_task_freeze(task);
         }
         ngn_add_task(ngn, task, r);
-        ngn->no_assigned++;
         return APR_SUCCESS;
     }
     
     /* no existing engine or being shut down, start a new one */
     if (einit) {
         apr_status_t status;
