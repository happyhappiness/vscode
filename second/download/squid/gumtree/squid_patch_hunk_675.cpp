         ntlm_errno = NTLM_ERR_LOGON;
         return NULL;
     }
     memcpy(user, tmp.str, tmp.l);
     *(user + tmp.l) = '\0';
 
-    /* Authenticating against the NT response doesn't seem to work... */
-    tmp = ntlm_fetch_string(&(auth->hdr), auth_length, &auth->lmresponse, auth->flags);
-    if (tmp.str == NULL || tmp.l == 0) {
-        fprintf(stderr, "No auth at all. Returning no-auth\n");
-        ntlm_errno = NTLM_ERR_LOGON;
-        return NULL;
+    // grab the *response blobs. these are fixed length 24 bytes of binary
+    const ntlmhdr *packet = &(auth->hdr);
+    {
+        const strhdr * str = &auth->lmresponse;
+
+        int16_t len = le16toh(str->len);
+        int32_t offset = le32toh(str->offset);
+
+        if (len != ENCODED_PASS_LEN || offset + len > auth_length || offset == 0) {
+            debug("LM response: insane data (pkt-sz: %d, fetch len: %d, offset: %d)\n", auth_length, len, offset);
+            ntlm_errno = NTLM_ERR_LOGON;
+            return NULL;
+        }
+        tmp.str = (char *)packet + offset;
+        tmp.l = len;
     }
     if (tmp.l > MAX_PASSWD_LEN) {
         debug("Password string exceeds %d bytes, rejecting\n", MAX_PASSWD_LEN);
         ntlm_errno = NTLM_ERR_LOGON;
         return NULL;
     }
 
+    /* Authenticating against the NT response doesn't seem to work... in SMB LM helper. */
     memcpy(pass, tmp.str, tmp.l);
     pass[min(MAX_PASSWD_LEN,tmp.l)] = '\0';
 
-#if 1
     debug("Empty LM pass detection: user: '%s', ours:'%s', his: '%s' (length: %d)\n",
           user,lmencoded_empty_pass,tmp.str,tmp.l);
     if (memcmp(tmp.str,lmencoded_empty_pass,ENCODED_PASS_LEN)==0) {
         fprintf(stderr,"Empty LM password supplied for user %s\\%s. "
                 "No-auth\n",domain,user);
         ntlm_errno=NTLM_ERR_LOGON;
         return NULL;
     }
 
-    tmp = ntlm_fetch_string(&(auth->hdr), auth_length, &auth->ntresponse, auth->flags);
-    if (tmp.str != NULL && tmp.l != 0) {
-        debug("Empty NT pass detection: user: '%s', ours:'%s', his: '%s' (length: %d)\n",
-              user,ntencoded_empty_pass,tmp.str,tmp.l);
-        if (memcmp(tmp.str,lmencoded_empty_pass,ENCODED_PASS_LEN)==0) {
-            fprintf(stderr,"ERROR: Empty NT password supplied for user %s\\%s. No-auth\n", domain, user);
-            ntlm_errno = NTLM_ERR_LOGON;
-            return NULL;
+    /* still fetch the NT response and check validity against empty password */
+    {
+        const strhdr * str = &auth->ntresponse;
+        int16_t len = le16toh(str->len);
+        // NT response field may be absent. that is okay.
+        if (len != 0) {
+            int32_t offset = le32toh(str->offset);
+
+            if (len != ENCODED_PASS_LEN || offset + len > auth_length || offset == 0) {
+                debug("NT response: insane data (pkt-sz: %d, fetch len: %d, offset: %d)\n", auth_length, len, offset);
+                ntlm_errno = NTLM_ERR_LOGON;
+                return NULL;
+            }
+            tmp.str = (char *)packet + offset;
+            tmp.l = len;
+
+            debug("Empty NT pass detection: user: '%s', ours:'%s', his: '%s' (length: %d)\n",
+                  user,ntencoded_empty_pass,tmp.str,tmp.l);
+            if (memcmp(tmp.str,lmencoded_empty_pass,ENCODED_PASS_LEN)==0) {
+                fprintf(stderr,"ERROR: Empty NT password supplied for user %s\\%s. No-auth\n", domain, user);
+                ntlm_errno = NTLM_ERR_LOGON;
+                return NULL;
+            }
         }
     }
-#endif
-
-    /* TODO: check against empty password!!!!! */
 
     debug("checking domain: '%s', user: '%s', pass='%s'\n", domain, user, pass);
 
     rv = SMB_Logon_Server(handle, user, pass, domain, 1);
     debug("Login attempt had result %d\n", rv);
 
     if (rv != NTLM_ERR_NONE) {	/* failed */
         ntlm_errno = rv;
         return NULL;
     }
-    *(user - 1) = '\\';		/* hack. Performing, but ugly. */
+    *(user - 1) = '\\';     /* hack. Performing, but ugly. */
 
     debug("credentials: %s\n", credentials);
     return credentials;
 }
 
 extern "C" void timeout_during_auth(int signum);
