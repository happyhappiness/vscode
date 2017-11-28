         Must(delayedReply == NULL);
         delayedReply = reply;
         return;
     }
 
     const HttpHeader &header = reply->header;
-    // adaptation and forwarding errors lack HDR_FTP_STATUS
-    if (!header.has(HDR_FTP_STATUS)) {
+    // adaptation and forwarding errors lack Http::HdrType::FTP_STATUS
+    if (!header.has(Http::HdrType::FTP_STATUS)) {
         writeForwardedForeign(reply); // will get to Ftp::Server::wroteReply
         return;
     }
 
     typedef CommCbMemFunT<Server, CommIoCbParams> Dialer;
     AsyncCall::Pointer call = JobCallback(33, 5, Dialer, this, Ftp::Server::wroteReply);
     writeForwardedReplyAndCall(reply, call);
 }
 
 void
 Ftp::Server::handleEprtReply(const HttpReply *reply, StoreIOBuffer)
 {
-    if (getCurrentContext()->http->request->errType != ERR_NONE) {
+    if (pipeline.front()->http->request->errType != ERR_NONE) {
         writeCustomReply(502, "Server does not support PASV (converted from EPRT)", reply);
         return;
     }
 
     writeCustomReply(200, "EPRT successfully converted to PASV.");
 
     // and wait for RETR
 }
 
 void
 Ftp::Server::handleEpsvReply(const HttpReply *reply, StoreIOBuffer)
 {
-    if (getCurrentContext()->http->request->errType != ERR_NONE) {
+    if (pipeline.front()->http->request->errType != ERR_NONE) {
         writeCustomReply(502, "Cannot connect to server", reply);
         return;
     }
 
     const unsigned short localPort = listenForDataConnection();
     if (!localPort)
         return;
 
     // In interception setups, we use a local port number and hope that data
     // traffic will be redirected to us.
     MemBuf mb;
     mb.init();
-    mb.Printf("229 Entering Extended Passive Mode (|||%u|)\r\n", localPort);
+    mb.appendf("229 Entering Extended Passive Mode (|||%u|)\r\n", localPort);
 
     debugs(9, 3, Raw("writing", mb.buf, mb.size));
     writeReply(mb);
 }
 
 /// writes FTP error response with given status and reply-derived error details
 void
 Ftp::Server::writeErrorReply(const HttpReply *reply, const int scode)
 {
-    const HttpRequest *request = getCurrentContext()->http->request;
+    const HttpRequest *request = pipeline.front()->http->request;
     assert(request);
 
     MemBuf mb;
     mb.init();
 
     if (request->errType != ERR_NONE)
-        mb.Printf("%i-%s\r\n", scode, errorPageName(request->errType));
+        mb.appendf("%i-%s\r\n", scode, errorPageName(request->errType));
 
     if (request->errDetail > 0) {
         // XXX: > 0 may not always mean that this is an errno
-        mb.Printf("%i-Error: (%d) %s\r\n", scode,
-                  request->errDetail,
-                  strerror(request->errDetail));
+        mb.appendf("%i-Error: (%d) %s\r\n", scode,
+                   request->errDetail,
+                   strerror(request->errDetail));
     }
 
 #if USE_ADAPTATION
     // XXX: Remove hard coded names. Use an error page template instead.
     const Adaptation::History::Pointer ah = request->adaptHistory();
     if (ah != NULL) { // XXX: add adapt::<all_h but use lastMeta here
         const String info = ah->allMeta.getByName("X-Response-Info");
         const String desc = ah->allMeta.getByName("X-Response-Desc");
         if (info.size())
-            mb.Printf("%i-Information: %s\r\n", scode, info.termedBuf());
+            mb.appendf("%i-Information: %s\r\n", scode, info.termedBuf());
         if (desc.size())
-            mb.Printf("%i-Description: %s\r\n", scode, desc.termedBuf());
+            mb.appendf("%i-Description: %s\r\n", scode, desc.termedBuf());
     }
 #endif
 
     Must(reply);
-    const char *reason = reply->header.has(HDR_FTP_REASON) ?
-                         reply->header.getStr(HDR_FTP_REASON):
+    const char *reason = reply->header.has(Http::HdrType::FTP_REASON) ?
+                         reply->header.getStr(Http::HdrType::FTP_REASON):
                          reply->sline.reason();
 
-    mb.Printf("%i %s\r\n", scode, reason); // error terminating line
+    mb.appendf("%i %s\r\n", scode, reason); // error terminating line
 
     // TODO: errorpage.cc should detect FTP client and use
     // configurable FTP-friendly error templates which we should
     // write to the client "as is" instead of hiding most of the info
 
     writeReply(mb);
