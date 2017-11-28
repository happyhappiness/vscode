     int len = io.size;
 
     flags.do_next_read = false;
 
     debugs(11, 5, HERE << io.conn << ": len " << len << ".");
 
-    // Bail out early on COMM_ERR_CLOSING - close handlers will tidy up for us
-    if (io.flag == COMM_ERR_CLOSING) {
+    // Bail out early on Comm::ERR_CLOSING - close handlers will tidy up for us
+    if (io.flag == Comm::ERR_CLOSING) {
         debugs(11, 3, "http socket closing");
         return;
     }
 
     if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
         abortTransaction("store entry aborted while reading reply");
         return;
     }
 
     // handle I/O errors
-    if (io.flag != COMM_OK || len < 0) {
+    if (io.flag != Comm::OK || len < 0) {
         debugs(11, 2, HERE << io.conn << ": read failure: " << xstrerror() << ".");
 
         if (ignoreErrno(io.xerrno)) {
             flags.do_next_read = true;
         } else {
             ErrorState *err = new ErrorState(ERR_READ_ERROR, Http::scBadGateway, fwd->request);
             err->xerrno = io.xerrno;
             fwd->fail(err);
             flags.do_next_read = false;
-            serverConnection->close();
+            closeServer();
+            mustStop("HttpStateData::readReply");
         }
 
         return;
     }
 
     // update I/O stats
