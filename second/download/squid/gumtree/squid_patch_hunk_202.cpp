 
     delete readBuf;
 
     if (httpChunkDecoder)
         delete httpChunkDecoder;
 
-    HTTPMSGUNLOCK(orig_request);
+    cbdataReferenceDone(_peer);
 
-    debugs(11,5, HERE << "HttpStateData " << this << " destroyed; FD " << fd);
+    debugs(11,5, HERE << "HttpStateData " << this << " destroyed; " << serverConnection);
 }
 
-int
-HttpStateData::dataDescriptor() const
+const Comm::ConnectionPointer &
+HttpStateData::dataConnection() const
 {
-    return fd;
+    return serverConnection;
 }
-/*
-static void
-httpStateFree(int fd, void *data)
-{
-    HttpStateData *httpState = static_cast<HttpStateData *>(data);
-    debugs(11, 5, "httpStateFree: FD " << fd << ", httpState=" << data);
-    delete httpState;
-}*/
 
 void
 HttpStateData::httpStateConnClosed(const CommCloseCbParams &params)
 {
     debugs(11, 5, "httpStateFree: FD " << params.fd << ", httpState=" << params.data);
-    deleteThis("HttpStateData::httpStateConnClosed");
+    mustStop("HttpStateData::httpStateConnClosed");
 }
 
 int
 httpCachable(const HttpRequestMethod& method)
 {
     /* GET and HEAD are cachable. Others are not. */
