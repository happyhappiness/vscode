 
     helperSubmit(digestauthenticators, buf, Auth::Digest::UserRequest::HandleReply,
                  new Auth::StateData(this, handler, data));
 }
 
 void
-Auth::Digest::UserRequest::HandleReply(void *data, char *reply)
+Auth::Digest::UserRequest::HandleReply(void *data, const HelperReply &reply)
 {
     Auth::StateData *replyData = static_cast<Auth::StateData *>(data);
-    char *t = NULL;
-    void *cbdata;
-    debugs(29, 9, HERE << "{" << (reply ? reply : "<NULL>") << "}");
-
-    if (reply) {
-        if ((t = strchr(reply, ' '))) {
-            *t = '\0';
-            ++t;
-        }
-
-        if (*reply == '\0' || *reply == '\n')
-            reply = NULL;
-    }
+    debugs(29, 9, HERE << "reply=" << reply);
 
     assert(replyData->auth_user_request != NULL);
     Auth::UserRequest::Pointer auth_user_request = replyData->auth_user_request;
 
-    if (reply && (strncasecmp(reply, "ERR", 3) == 0)) {
+    // add new helper kv-pair notes to the credentials object
+    // so that any transaction using those credentials can access them
+    auth_user_request->user()->notes.appendNewOnly(&reply.notes);
+    // remove any private credentials detail which got added.
+    auth_user_request->user()->notes.remove("ha1");
+
+    static bool oldHelperWarningDone = false;
+    switch (reply.result) {
+    case HelperReply::Unknown: {
+        // Squid 3.3 and older the digest helper only returns a HA1 hash (no "OK")
+        // the HA1 will be found in content() for these responses.
+        if (!oldHelperWarningDone) {
+            debugs(29, DBG_IMPORTANT, "WARNING: Digest auth helper returned old format HA1 response. It needs to be upgraded.");
+            oldHelperWarningDone=true;
+        }
+
         /* allow this because the digest_request pointer is purely local */
-        Auth::Digest::UserRequest *digest_request = dynamic_cast<Auth::Digest::UserRequest *>(auth_user_request.getRaw());
-        assert(digest_request);
+        Auth::Digest::User *digest_user = dynamic_cast<Auth::Digest::User *>(auth_user_request->user().getRaw());
+        assert(digest_user != NULL);
 
-        digest_request->user()->credentials(Auth::Failed);
-        digest_request->flags.invalid_password = 1;
+        CvtBin(reply.other().content(), digest_user->HA1);
+        digest_user->HA1created = 1;
+    }
+    break;
 
-        if (t && *t)
-            digest_request->setDenyMessage(t);
-    } else if (reply) {
+    case HelperReply::Okay: {
         /* allow this because the digest_request pointer is purely local */
         Auth::Digest::User *digest_user = dynamic_cast<Auth::Digest::User *>(auth_user_request->user().getRaw());
         assert(digest_user != NULL);
 
-        CvtBin(reply, digest_user->HA1);
-        digest_user->HA1created = 1;
+        const char *ha1Note = reply.notes.findFirst("ha1");
+        if (ha1Note != NULL) {
+            CvtBin(ha1Note, digest_user->HA1);
+            digest_user->HA1created = 1;
+        } else {
+            debugs(29, DBG_IMPORTANT, "ERROR: Digest auth helper did not produce a HA1. Using the wrong helper program? received: " << reply);
+        }
+    }
+    break;
+
+    case HelperReply::TT:
+        debugs(29, DBG_IMPORTANT, "ERROR: Digest auth does not support the result code received. Using the wrong helper program? received: " << reply);
+        // fall through to next case. Handle this as an ERR response.
+
+    case HelperReply::BrokenHelper:
+        // TODO retry the broken lookup on another helper?
+        // fall through to next case for now. Handle this as an ERR response silently.
+
+    case HelperReply::Error: {
+        /* allow this because the digest_request pointer is purely local */
+        Auth::Digest::UserRequest *digest_request = dynamic_cast<Auth::Digest::UserRequest *>(auth_user_request.getRaw());
+        assert(digest_request);
+
+        digest_request->user()->credentials(Auth::Failed);
+        digest_request->flags.invalid_password = true;
+
+        const char *msgNote = reply.notes.find("message");
+        if (msgNote != NULL) {
+            digest_request->setDenyMessage(msgNote);
+        } else if (reply.other().hasContent()) {
+            // old helpers did send ERR result but a bare message string instead of message= key name.
+            digest_request->setDenyMessage(reply.other().content());
+            if (!oldHelperWarningDone) {
+                debugs(29, DBG_IMPORTANT, "WARNING: Digest auth helper returned old format ERR response. It needs to be upgraded.");
+                oldHelperWarningDone=true;
+            }
+        }
+    }
+    break;
     }
 
+    void *cbdata = NULL;
     if (cbdataReferenceValidDone(replyData->data, &cbdata))
         replyData->handler(cbdata);
 
     delete replyData;
 }
