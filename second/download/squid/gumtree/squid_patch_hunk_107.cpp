 
 void
 ClientSocketContext::sendBody(HttpReply * rep, StoreIOBuffer bodyData)
 {
     assert(rep == NULL);
 
-    if (!multipartRangeRequest()) {
+    if (!multipartRangeRequest() && !http->request->flags.chunked_reply) {
         size_t length = lengthToSend(bodyData.range());
         noteSentBodyBytes (length);
         AsyncCall::Pointer call = commCbCall(33, 5, "clientWriteBodyComplete",
                                              CommIoCbPtrFun(clientWriteBodyComplete, this));
-        comm_write(fd(), bodyData.data, length, call );
+        Comm::Write(clientConnection, bodyData.data, length, call, NULL);
         return;
     }
 
     MemBuf mb;
     mb.init();
-    packRange(bodyData, &mb);
+    if (multipartRangeRequest())
+        packRange(bodyData, &mb);
+    else
+        packChunk(bodyData, mb);
 
     if (mb.contentSize()) {
         /* write */
         AsyncCall::Pointer call = commCbCall(33, 5, "clientWriteComplete",
                                              CommIoCbPtrFun(clientWriteComplete, this));
-        comm_write_mbuf(fd(), &mb, call);
+        Comm::Write(clientConnection, &mb, call);
     }  else
-        writeComplete(fd(), NULL, 0, COMM_OK);
+        writeComplete(clientConnection, NULL, 0, COMM_OK);
+}
+
+/**
+ * Packs bodyData into mb using chunked encoding. Packs the last-chunk
+ * if bodyData is empty.
+ */
+void
+ClientSocketContext::packChunk(const StoreIOBuffer &bodyData, MemBuf &mb)
+{
+    const uint64_t length =
+        static_cast<uint64_t>(lengthToSend(bodyData.range()));
+    noteSentBodyBytes(length);
+
+    mb.Printf("%" PRIX64 "\r\n", length);
+    mb.append(bodyData.data, length);
+    mb.Printf("\r\n");
 }
 
 /** put terminating boundary for multiparts */
 static void
 clientPackTermBound(String boundary, MemBuf * mb)
 {
