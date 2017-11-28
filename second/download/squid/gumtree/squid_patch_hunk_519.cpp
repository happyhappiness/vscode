 void
 Auth::Digest::UserRequest::addAuthenticationInfoHeader(HttpReply * rep, int accel)
 {
     http_hdr_type type;
 
     /* don't add to authentication error pages */
-
-    if ((!accel && rep->sline.status == HTTP_PROXY_AUTHENTICATION_REQUIRED)
-            || (accel && rep->sline.status == HTTP_UNAUTHORIZED))
+    if ((!accel && rep->sline.status() == Http::scProxyAuthenticationRequired)
+            || (accel && rep->sline.status() == Http::scUnauthorized))
         return;
 
     type = accel ? HDR_AUTHENTICATION_INFO : HDR_PROXY_AUTHENTICATION_INFO;
 
 #if WAITING_FOR_TE
     /* test for http/1.1 transfer chunked encoding */
     if (chunkedtest)
         return;
 #endif
 
     if ((static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->authenticateProgram) && authDigestNonceLastRequest(nonce)) {
-        flags.authinfo_sent = 1;
-        debugs(29, 9, HERE << "Sending type:" << type << " header: 'nextnonce=\"" << authenticateDigestNonceNonceb64(nonce) << "\"");
-        httpHeaderPutStrf(&rep->header, type, "nextnonce=\"%s\"", authenticateDigestNonceNonceb64(nonce));
+        flags.authinfo_sent = true;
+        Auth::Digest::User *digest_user = dynamic_cast<Auth::Digest::User *>(user().getRaw());
+        digest_nonce_h *nextnonce = digest_user->currentNonce();
+        if (!nextnonce || authDigestNonceLastRequest(nonce)) {
+            nextnonce = authenticateDigestNonceNew();
+            authDigestUserLinkNonce(digest_user, nextnonce);
+        }
+        debugs(29, 9, "Sending type:" << type << " header: 'nextnonce=\"" << authenticateDigestNonceNonceb64(nextnonce) << "\"");
+        httpHeaderPutStrf(&rep->header, type, "nextnonce=\"%s\"", authenticateDigestNonceNonceb64(nextnonce));
     }
 }
 
 #if WAITING_FOR_TE
 void
 Auth::Digest::UserRequest::addAuthenticationInfoTrailer(HttpReply * rep, int accel)
