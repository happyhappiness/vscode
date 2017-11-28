     changeState(fssHandleEpsv, "handleEpsvRequest");
     setDataCommand();
     return true; // forward our fake PASV request
 }
 
 bool
-Ftp::Server::handleCwdRequest(String &cmd, String &params)
+Ftp::Server::handleCwdRequest(String &, String &)
 {
     changeState(fssHandleCwd, "handleCwdRequest");
     return true;
 }
 
 bool
-Ftp::Server::handlePassRequest(String &cmd, String &params)
+Ftp::Server::handlePassRequest(String &, String &)
 {
     changeState(fssHandlePass, "handlePassRequest");
     return true;
 }
 
 bool
-Ftp::Server::handleCdupRequest(String &cmd, String &params)
+Ftp::Server::handleCdupRequest(String &, String &)
 {
     changeState(fssHandleCdup, "handleCdupRequest");
     return true;
 }
 
 // Convert user PORT, EPRT, PASV, or EPSV data command to Squid PASV command.
 // Squid FTP client decides what data command to use with peers.
 void
 Ftp::Server::setDataCommand()
 {
-    ClientHttpRequest *const http = getCurrentContext()->http;
+    ClientHttpRequest *const http = pipeline.front()->http;
     assert(http != NULL);
     HttpRequest *const request = http->request;
     assert(request != NULL);
     HttpHeader &header = request->header;
-    header.delById(HDR_FTP_COMMAND);
-    header.putStr(HDR_FTP_COMMAND, "PASV");
-    header.delById(HDR_FTP_ARGUMENTS);
-    header.putStr(HDR_FTP_ARGUMENTS, "");
+    header.delById(Http::HdrType::FTP_COMMAND);
+    header.putStr(Http::HdrType::FTP_COMMAND, "PASV");
+    header.delById(Http::HdrType::FTP_ARGUMENTS);
+    header.putStr(Http::HdrType::FTP_ARGUMENTS, "");
     debugs(9, 5, "client data command converted to fake PASV");
 }
 
 /// check that client data connection is ready for future I/O or at least
 /// has a chance of becoming ready soon.
 bool
