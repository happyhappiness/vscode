 
 int h2_beam_no_files(void *ctx, h2_bucket_beam *beam, apr_file_t *file)
 {
     return 0;
 }
 
+int h2_beam_report_consumption(h2_bucket_beam *beam)
+{
+    h2_beam_lock bl;
+    int rv = 0;
+    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
+        rv = report_consumption(beam, &bl);
+        leave_yellow(beam, &bl);
+    }
+    return rv;
+}
+
+void h2_beam_log(h2_bucket_beam *beam, conn_rec *c, int level, const char *msg)
+{
+    if (beam && APLOG_C_IS_LEVEL(c,level)) {
+        ap_log_cerror(APLOG_MARK, level, 0, c, 
+                      "beam(%ld-%d,%s,closed=%d,aborted=%d,empty=%d,buf=%ld): %s", 
+                      (c->master? c->master->id : c->id), beam->id, beam->tag, 
+                      beam->closed, beam->aborted, h2_beam_empty(beam), 
+                      (long)h2_beam_get_buffered(beam), msg);
+    }
+}
+
+
