     srv->stats.pending += 1;
     r->dispatch_time = current_time;
 
     if (srv->wqueue->isNull())
         srv->wqueue->init();
 
-    if (hlp->concurrency)
+    if (hlp->childs.concurrency)
         srv->wqueue->Printf("%d %s", slot, r->buf);
     else
         srv->wqueue->append(r->buf, strlen(r->buf));
 
     if (!srv->flags.writing) {
         assert(NULL == srv->writebuf);
         srv->writebuf = srv->wqueue;
         srv->wqueue = new MemBuf;
         srv->flags.writing = 1;
-        comm_write(srv->wfd,
-                   srv->writebuf->content(),
-                   srv->writebuf->contentSize(),
-                   helperDispatchWriteDone,	/* Handler */
-                   srv, NULL);			/* Handler-data, free func */
+        AsyncCall::Pointer call = commCbCall(5,5, "helperDispatchWriteDone",
+                                             CommIoCbPtrFun(helperDispatchWriteDone, srv));
+        Comm::Write(srv->writePipe, srv->writebuf->content(), srv->writebuf->contentSize(), call, NULL);
     }
 
     debugs(84, 5, "helperDispatch: Request sent to " << hlp->id_name << " #" << srv->index + 1 << ", " << strlen(r->buf) << " bytes");
 
-    srv->stats.uses++;
-    hlp->stats.requests++;
+    ++ srv->stats.uses;
+    ++ hlp->stats.requests;
 }
 
 static void
-helperStatefulDispatchWriteDone(int fd, char *buf, size_t len, comm_err_t flag,
+helperStatefulDispatchWriteDone(const Comm::ConnectionPointer &conn, char *buf, size_t len, comm_err_t flag,
                                 int xerrno, void *data)
 {
     /* nothing! */
 }
 
 
