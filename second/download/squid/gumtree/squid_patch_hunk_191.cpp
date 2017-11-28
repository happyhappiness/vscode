  *	including canceling close handlers
  */
 void
 FtpStateData::abortTransaction(const char *reason)
 {
     debugs(9, 3, HERE << "aborting transaction for " << reason <<
-           "; FD " << ctrl.fd << ", Data FD " << data.fd << ", this " << this);
-    if (ctrl.fd >= 0) {
-        comm_close(ctrl.fd);
+           "; FD " << (ctrl.conn!=NULL?ctrl.conn->fd:-1) << ", Data FD " << (data.conn!=NULL?data.conn->fd:-1) << ", this " << this);
+    if (Comm::IsConnOpen(ctrl.conn)) {
+        ctrl.conn->close();
         return;
     }
 
     fwd->handleUnregisteredServerEnd();
-    deleteThis("FtpStateData::abortTransaction");
+    mustStop("FtpStateData::abortTransaction");
 }
 
 /// creates a data channel Comm close callback
 AsyncCall::Pointer
 FtpStateData::dataCloser()
 {
     typedef CommCbMemFunT<FtpStateData, CommCloseCbParams> Dialer;
     return JobCallback(9, 5, Dialer, this, FtpStateData::dataClosed);
 }
 
 /// configures the channel with a descriptor and registers a close handler
 void
-FtpChannel::opened(int aFd, const AsyncCall::Pointer &aCloser)
+FtpChannel::opened(const Comm::ConnectionPointer &newConn, const AsyncCall::Pointer &aCloser)
 {
-    assert(fd < 0);
+    assert(!Comm::IsConnOpen(conn));
     assert(closer == NULL);
 
-    assert(aFd >= 0);
+    assert(Comm::IsConnOpen(newConn));
     assert(aCloser != NULL);
 
-    fd = aFd;
+    conn = newConn;
     closer = aCloser;
-    comm_add_close_handler(fd, closer);
+    comm_add_close_handler(conn->fd, closer);
 }
 
 /// planned close: removes the close handler and calls comm_close
 void
 FtpChannel::close()
 {
-    if (fd >= 0) {
-        comm_remove_close_handler(fd, closer);
-        closer = NULL;
-        comm_close(fd); // we do not expect to be called back
-        fd = -1;
+    // channels with active listeners will be closed when the listener handler dies.
+    if (Comm::IsConnOpen(conn)) {
+        comm_remove_close_handler(conn->fd, closer);
+        conn->close(); // we do not expect to be called back
     }
+    clear();
 }
 
-/// just resets fd and close handler
 void
 FtpChannel::clear()
 {
-    fd = -1;
+    conn = NULL;
     closer = NULL;
 }
