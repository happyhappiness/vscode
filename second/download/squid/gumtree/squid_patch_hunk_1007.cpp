     }
 }
 
 void
 Ftp::Relay::sendCommand()
 {
-    if (!fwd->request->header.has(HDR_FTP_COMMAND)) {
+    if (!fwd->request->header.has(Http::HdrType::FTP_COMMAND)) {
         abortAll("Internal error: FTP relay request with no command");
         return;
     }
 
     HttpHeader &header = fwd->request->header;
-    assert(header.has(HDR_FTP_COMMAND));
-    const String &cmd = header.findEntry(HDR_FTP_COMMAND)->value;
-    assert(header.has(HDR_FTP_ARGUMENTS));
-    const String &params = header.findEntry(HDR_FTP_ARGUMENTS)->value;
+    assert(header.has(Http::HdrType::FTP_COMMAND));
+    const String &cmd = header.findEntry(Http::HdrType::FTP_COMMAND)->value;
+    assert(header.has(Http::HdrType::FTP_ARGUMENTS));
+    const String &params = header.findEntry(Http::HdrType::FTP_ARGUMENTS)->value;
 
     if (params.size() > 0)
         debugs(9, 5, "command: " << cmd << ", parameters: " << params);
     else
         debugs(9, 5, "command: " << cmd << ", no parameters");
 
