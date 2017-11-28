     debugs(32,3,HERE << "sentRequestBody called");
 
     requestSender = NULL;
 
     if (io.size > 0) {
         fd_bytes(io.fd, io.size, FD_WRITE);
-        kb_incr(&statCounter.server.all.kbytes_out, io.size);
+        kb_incr(&(statCounter.server.all.kbytes_out), io.size);
         // kids should increment their counters
     }
 
     if (io.flag == COMM_ERR_CLOSING)
         return;
 
     if (!requestBodySource) {
         debugs(9,3, HERE << "detected while-we-were-sending abort");
         return; // do nothing;
     }
 
     if (io.flag) {
-        debugs(11, 1, "sentRequestBody error: FD " << io.fd << ": " << xstrerr(errno));
+        debugs(11, 1, "sentRequestBody error: FD " << io.fd << ": " << xstrerr(io.xerrno));
         ErrorState *err;
-        err = errorCon(ERR_WRITE_ERROR, HTTP_BAD_GATEWAY, fwd->request);
-        err->xerrno = errno;
+        err = new ErrorState(ERR_WRITE_ERROR, HTTP_BAD_GATEWAY, fwd->request);
+        err->xerrno = io.xerrno;
         fwd->fail(err);
         abortTransaction("I/O error while sending request body");
         return;
     }
 
     if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
         abortTransaction("store entry aborted while sending request body");
         return;
     }
 
-    if (requestBodySource->exhausted())
+    if (!requestBodySource->exhausted())
+        sendMoreRequestBody();
+    else if (receivedWholeRequestBody)
         doneSendingRequestBody();
     else
-        sendMoreRequestBody();
-}
-
-bool
-ServerStateData::canSend(int fd) const
-{
-    return fd >= 0 && !fd_table[fd].closing();
+        debugs(9,3, HERE << "waiting for body production end or abort");
 }
 
 void
 ServerStateData::sendMoreRequestBody()
 {
     assert(requestBodySource != NULL);
     assert(!requestSender);
 
-    const int fd = dataDescriptor();
+    const Comm::ConnectionPointer conn = dataConnection();
 
-    if (!canSend(fd)) {
-        debugs(9,3, HERE << "cannot send request body to closing FD " << fd);
+    if (!Comm::IsConnOpen(conn)) {
+        debugs(9,3, HERE << "cannot send request body to closing " << conn);
         return; // wait for the kid's close handler; TODO: assert(closer);
     }
 
     MemBuf buf;
-    if (requestBodySource->getMoreData(buf)) {
+    if (getMoreRequestBody(buf) && buf.contentSize() > 0) {
         debugs(9,3, HERE << "will write " << buf.contentSize() << " request body bytes");
         typedef CommCbMemFunT<ServerStateData, CommIoCbParams> Dialer;
-        requestSender = JobCallback(93,3,
-                                    Dialer, this, ServerStateData::sentRequestBody);
-        comm_write_mbuf(fd, &buf, requestSender);
+        requestSender = JobCallback(93,3, Dialer, this, ServerStateData::sentRequestBody);
+        Comm::Write(conn, &buf, requestSender);
     } else {
         debugs(9,3, HERE << "will wait for more request body bytes or eof");
         requestSender = NULL;
     }
 }
 
+/// either fill buf with available [encoded] request body bytes or return false
+bool
+ServerStateData::getMoreRequestBody(MemBuf &buf)
+{
+    // default implementation does not encode request body content
+    Must(requestBodySource != NULL);
+    return requestBodySource->getMoreData(buf);
+}
+
 // Compares hosts in urls, returns false if different, no sheme, or no host.
 static bool
 sameUrlHosts(const char *url1, const char *url2)
 {
     // XXX: Want urlHostname() here, but it uses static storage and copying
     const char *host1 = strchr(url1, ':');
