     EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
 
     HttpReply *reply = new HttpReply;
     entry->buffer();
     reply->setHeaders(Http::scOkay, "Gatewaying", mime_type, -1, -1, -2);
     if (mime_enc)
-        reply->header.putStr(HDR_CONTENT_ENCODING, mime_enc);
+        reply->header.putStr(Http::HdrType::CONTENT_ENCODING, mime_enc);
 
     entry->replaceHttpReply(reply);
+    gopherState->reply_ = reply;
 }
 
 /**
- \ingroup ServerProtocolGopherInternal
  * Parse a gopher request into components.  By Anawat.
  */
 static void
 gopher_request_parse(const HttpRequest * req, char *type_id, char *request)
 {
-    const char *path = req->urlpath.termedBuf();
+    ::Parser::Tokenizer tok(req->url.path());
 
     if (request)
-        request[0] = '\0';
+        *request = 0;
 
-    if (path && (*path == '/'))
-        ++path;
+    tok.skip('/'); // ignore failures? path could be ab-empty
 
-    if (!path || !*path) {
+    if (tok.atEnd()) {
         *type_id = GOPHER_DIRECTORY;
         return;
     }
 
-    *type_id = path[0];
+    static const CharacterSet anyByte("UTF-8",0x00, 0xFF);
+
+    SBuf typeId;
+    (void)tok.prefix(typeId, anyByte, 1); // never fails since !atEnd()
+    *type_id = typeId[0];
 
     if (request) {
-        xstrncpy(request, path + 1, MAX_URL);
+        SBufToCstring(request, tok.remaining().substr(0, MAX_URL-1));
         /* convert %xx to char */
         rfc1738_unescape(request);
     }
 }
 
 /**
- \ingroup ServerProtocolGopherAPI
  * Parse the request to determine whether it is cachable.
  *
- \param req Request data.
- \retval 0  Not cachable.
- \retval 1  Cachable.
+ * \param req   Request data.
+ * \retval 0    Not cachable.
+ * \retval 1    Cachable.
  */
 int
 gopherCachable(const HttpRequest * req)
 {
     int cachable = 1;
     char type_id;
