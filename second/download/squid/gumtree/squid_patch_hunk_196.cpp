     if (srv->writebuf) {
         srv->writebuf->clean();
         delete srv->writebuf;
         srv->writebuf = NULL;
     }
 
-    if (srv->wfd != srv->rfd && srv->wfd != -1)
-        comm_close(srv->wfd);
+    if (Comm::IsConnOpen(srv->writePipe))
+        srv->closeWritePipeSafely();
 
     dlinkDelete(&srv->link, &hlp->servers);
 
-    hlp->n_running--;
-
-    assert(hlp->n_running >= 0);
+    assert(hlp->childs.n_running > 0);
+    -- hlp->childs.n_running;
 
     if (!srv->flags.shutdown) {
-        hlp->n_active--;
-        assert(hlp->n_active >= 0);
-        debugs(84, 0, "WARNING: " << hlp->id_name << " #" << srv->index + 1 <<
-               " (FD " << fd << ") exited");
+        assert(hlp->childs.n_active > 0);
+        -- hlp->childs.n_active;
+        debugs(84, DBG_CRITICAL, "WARNING: " << hlp->id_name << " #" << srv->index + 1 << " exited");
 
-        if (hlp->n_active < hlp->n_to_start / 2) {
-            debugs(80, 0, "Too few " << hlp->id_name << " processes are running");
+        if (hlp->childs.needNew() > 0) {
+            debugs(80, 1, "Too few " << hlp->id_name << " processes are running (need " << hlp->childs.needNew() << "/" << hlp->childs.n_max << ")");
 
-            if (hlp->last_restart > squid_curtime - 30)
+            if (hlp->childs.n_active < hlp->childs.n_startup && hlp->last_restart > squid_curtime - 30)
                 fatalf("The %s helpers are crashing too rapidly, need help!\n", hlp->id_name);
 
-            debugs(80, 0, "Starting new helpers");
-
+            debugs(80, 1, "Starting new helpers");
             helperOpenServers(hlp);
         }
     }
 
-    for (i = 0; i < concurrency; i++) {
+    for (i = 0; i < concurrency; ++i) {
         if ((r = srv->requests[i])) {
             void *cbdata;
 
             if (cbdataReferenceValidDone(r->data, &cbdata))
                 r->callback(cbdata, NULL);
 
