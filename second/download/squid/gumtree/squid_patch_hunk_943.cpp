     }
 }
 
 void Adaptation::Icap::ModXact::makeUsernameHeader(const HttpRequest *request, MemBuf &buf)
 {
 #if USE_AUTH
+    struct base64_encode_ctx ctx;
+    base64_encode_init(&ctx);
+
+    const char *value = NULL;
     if (request->auth_user_request != NULL) {
-        char const *name = request->auth_user_request->username();
-        if (name) {
-            const char *value = TheConfig.client_username_encode ? old_base64_encode(name) : name;
-            buf.Printf("%s: %s\r\n", TheConfig.client_username_header, value);
-        }
+        value = request->auth_user_request->username();
     } else if (request->extacl_user.size() > 0) {
-        const char *value = TheConfig.client_username_encode ? old_base64_encode(request->extacl_user.termedBuf()) : request->extacl_user.termedBuf();
-        buf.Printf("%s: %s\r\n", TheConfig.client_username_header, value);
+        value = request->extacl_user.termedBuf();
+    }
+
+    if (value) {
+        if (TheConfig.client_username_encode) {
+            uint8_t base64buf[base64_encode_len(MAX_LOGIN_SZ)];
+            size_t resultLen = base64_encode_update(&ctx, base64buf, strlen(value), reinterpret_cast<const uint8_t*>(value));
+            resultLen += base64_encode_final(&ctx, base64buf+resultLen);
+            buf.appendf("%s: %.*s\r\n", TheConfig.client_username_header, (int)resultLen, base64buf);
+        } else
+            buf.appendf("%s: %s\r\n", TheConfig.client_username_header, value);
     }
 #endif
 }
 
 void Adaptation::Icap::ModXact::encapsulateHead(MemBuf &icapBuf, const char *section, MemBuf &httpBuf, const HttpMsg *head)
 {
     // update ICAP header
-    icapBuf.Printf("%s=%d, ", section, (int) httpBuf.contentSize());
+    icapBuf.appendf("%s=%d, ", section, (int) httpBuf.contentSize());
 
     // begin cloning
     HttpMsg::Pointer headClone;
 
     if (const HttpRequest* old_request = dynamic_cast<const HttpRequest*>(head)) {
         HttpRequest::Pointer new_request(new HttpRequest);
-        Must(old_request->canonical);
-        urlParse(old_request->method, old_request->canonical, new_request.getRaw());
+        // copy the requst-line details
+        new_request->method = old_request->method;
+        new_request->url = old_request->url;
         new_request->http_ver = old_request->http_ver;
         headClone = new_request.getRaw();
     } else if (const HttpReply *old_reply = dynamic_cast<const HttpReply*>(head)) {
         HttpReply::Pointer new_reply(new HttpReply);
         new_reply->sline = old_reply->sline;
         headClone = new_reply.getRaw();
     }
-    Must(headClone != NULL);
+    Must(headClone);
     headClone->inheritProperties(head);
 
     HttpHeaderPos pos = HttpHeaderInitPos;
-    HttpHeaderEntry* p_head_entry = NULL;
-    while (NULL != (p_head_entry = head->header.getEntry(&pos)) )
+    while (HttpHeaderEntry* p_head_entry = head->header.getEntry(&pos))
         headClone->header.addEntry(p_head_entry->clone());
 
     // end cloning
 
     // remove all hop-by-hop headers from the clone
-    headClone->header.delById(HDR_PROXY_AUTHENTICATE);
+    headClone->header.delById(Http::HdrType::PROXY_AUTHENTICATE);
     headClone->header.removeHopByHopEntries();
 
     // pack polished HTTP header
     packHead(httpBuf, headClone.getRaw());
 
     // headClone unlocks and, hence, deletes the message we packed
 }
 
 void Adaptation::Icap::ModXact::packHead(MemBuf &httpBuf, const HttpMsg *head)
 {
-    Packer p;
-    packerToMemInit(&p, &httpBuf);
-    head->packInto(&p, true);
-    packerClean(&p);
+    head->packInto(&httpBuf, true);
 }
 
 // decides whether to offer a preview and calculates its size
 void Adaptation::Icap::ModXact::decideOnPreview()
 {
     if (!TheConfig.preview_enable) {
         debugs(93, 5, HERE << "preview disabled by squid.conf");
         return;
     }
 
-    const String urlPath = virginRequest().urlpath;
+    const SBuf urlPath(virginRequest().url.path());
     size_t wantedSize;
     if (!service().wantsPreview(urlPath, wantedSize)) {
-        debugs(93, 5, HERE << "should not offer preview for " << urlPath);
+        debugs(93, 5, "should not offer preview for " << urlPath);
         return;
     }
 
     // we decided to do preview, now compute its size
 
     // cannot preview more than we can backup
