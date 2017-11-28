     xfree(b);
 }
 
 static void
 logfileHandleWrite(int fd, void *data)
 {
-    Logfile *lf = (Logfile *) data;
-    l_daemon_t *ll = (l_daemon_t *) lf->data;
-    int ret;
-    logfile_buffer_t *b;
+    Logfile *lf = static_cast<Logfile *>(data);
+    l_daemon_t *ll = static_cast<l_daemon_t *>(lf->data);
 
     /*
      * We'll try writing the first entry until its done - if we
      * get a partial write then we'll re-schedule until its completed.
      * Its naive but it'll do for now.
      */
-    b = static_cast<logfile_buffer_t*>(ll->bufs.head->data);
+    if (!ll->bufs.head) // abort if there is nothing pending right now.
+        return;
+
+    logfile_buffer_t *b = static_cast<logfile_buffer_t*>(ll->bufs.head->data);
     assert(b != NULL);
     ll->flush_pending = 0;
 
-    ret = FD_WRITE_METHOD(ll->wfd, b->buf + b->written_len, b->len - b->written_len);
-    debugs(50, 3, "logfileHandleWrite: " << lf->path << ": write returned " << ret);
+    int ret = FD_WRITE_METHOD(ll->wfd, b->buf + b->written_len, b->len - b->written_len);
+    debugs(50, 3, lf->path << ": write returned " << ret);
     if (ret < 0) {
         if (ignoreErrno(errno)) {
             /* something temporary */
-            goto reschedule;
+            Comm::SetSelect(ll->wfd, COMM_SELECT_WRITE, logfileHandleWrite, lf, 0);
+            ll->flush_pending = 1;
+            return;
         }
         debugs(50, DBG_IMPORTANT,"logfileHandleWrite: " << lf->path << ": error writing (" << xstrerror() << ")");
         /* XXX should handle this better */
         fatal("I don't handle this error well!");
     }
     if (ret == 0) {
