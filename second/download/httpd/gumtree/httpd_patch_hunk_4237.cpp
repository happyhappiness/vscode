 {
     return ngn->shed;
 }
 
 void h2_ngn_shed_abort(h2_ngn_shed *shed)
 {
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, shed->c, APLOGNO(03394)
+                  "h2_ngn_shed(%ld): abort", shed->c->id);
     shed->aborted = 1;
 }
 
 static void ngn_add_task(h2_req_engine *ngn, h2_task *task)
 {
     h2_ngn_entry *entry = apr_pcalloc(task->pool, sizeof(*entry));
