     // In interception setups, we combine remote server address with a
     // local port number and hope that traffic will be redirected to us.
     // Do not use "227 =a,b,c,d,p1,p2" format or omit parens: some nf_ct_ftp
     // versions block responses that use those alternative syntax rules!
     MemBuf mb;
     mb.init();
-    mb.Printf("227 Entering Passive Mode (%s,%i,%i).\r\n",
-              addr,
-              static_cast<int>(localPort / 256),
-              static_cast<int>(localPort % 256));
+    mb.appendf("227 Entering Passive Mode (%s,%i,%i).\r\n",
+               addr,
+               static_cast<int>(localPort / 256),
+               static_cast<int>(localPort % 256));
     debugs(9, 3, Raw("writing", mb.buf, mb.size));
     writeReply(mb);
 }
 
 void
 Ftp::Server::handlePortReply(const HttpReply *reply, StoreIOBuffer)
 {
-    if (getCurrentContext()->http->request->errType != ERR_NONE) {
+    if (pipeline.front()->http->request->errType != ERR_NONE) {
         writeCustomReply(502, "Server does not support PASV (converted from PORT)", reply);
         return;
     }
 
     writeCustomReply(200, "PORT successfully converted to PASV.");
 
