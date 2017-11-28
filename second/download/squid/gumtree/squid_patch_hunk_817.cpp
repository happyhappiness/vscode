     if (io.size > 0) {
         fd_bytes(io.fd, io.size, FD_WRITE);
         kb_incr(&(statCounter.server.all.kbytes_out), io.size);
         kb_incr(&(statCounter.server.http.kbytes_out), io.size);
     }
 
-    if (io.flag == COMM_ERR_CLOSING)
+    if (io.flag == Comm::ERR_CLOSING)
         return;
 
     if (io.flag) {
         ErrorState *err = new ErrorState(ERR_WRITE_ERROR, Http::scBadGateway, fwd->request);
         err->xerrno = io.xerrno;
         fwd->fail(err);
-        serverConnection->close();
+        closeServer();
+        mustStop("HttpStateData::wroteLast");
         return;
     }
 
     sendComplete();
 }
 
