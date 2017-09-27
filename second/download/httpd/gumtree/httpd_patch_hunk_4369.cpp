 static h2_ngn_entry *pop_detached(h2_req_engine *ngn)
 {
     h2_ngn_entry *entry;
     for (entry = H2_REQ_ENTRIES_FIRST(&ngn->entries);
          entry != H2_REQ_ENTRIES_SENTINEL(&ngn->entries);
          entry = H2_NGN_ENTRY_NEXT(entry)) {
-        if (h2_task_is_detached(entry->task) 
+        if (h2_task_has_thawed(entry->task) 
             || (entry->task->engine == ngn)) {
             /* The task hosting this engine can always be pulled by it.
              * For other task, they need to become detached, e.g. no longer
              * assigned to another worker. */
             H2_NGN_ENTRY_REMOVE(entry);
             return entry;
         }
     }
     return NULL;
 }
 
-apr_status_t h2_ngn_shed_pull_task(h2_ngn_shed *shed, 
-                                   h2_req_engine *ngn, 
-                                   apr_uint32_t capacity, 
-                                   int want_shutdown,
-                                   h2_task **ptask)
+apr_status_t h2_ngn_shed_pull_request(h2_ngn_shed *shed, 
+                                      h2_req_engine *ngn, 
+                                      int capacity, 
+                                      int want_shutdown,
+                                      request_rec **pr)
 {   
     h2_ngn_entry *entry;
     
-    AP_DEBUG_ASSERT(ngn);
-    *ptask = NULL;
-    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, shed->c, APLOGNO(03396)
+    ap_assert(ngn);
+    *pr = NULL;
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, shed->c, APLOGNO(03396)
                   "h2_ngn_shed(%ld): pull task for engine %s, shutdown=%d", 
                   shed->c->id, ngn->id, want_shutdown);
     if (shed->aborted) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, shed->c, APLOGNO(03397)
                       "h2_ngn_shed(%ld): abort while pulling requests %s", 
                       shed->c->id, ngn->id);
