             lm_request->server_blob = xstrdup(tokenNote);
         lm_request->releaseAuthServer();
         debugs(29, 4, "Failed validating user via Negotiate. Result: " << reply);
     }
     break;
 
-    case HelperReply::Unknown:
+    case Helper::Unknown:
         debugs(29, DBG_IMPORTANT, "ERROR: Negotiate Authentication Helper '" << reply.whichServer << "' crashed!.");
-        /* continue to the next case */
+    /* continue to the next case */
 
-    case HelperReply::BrokenHelper: {
+    case Helper::BrokenHelper: {
         /* TODO kick off a refresh process. This can occur after a YR or after
          * a KK. If after a YR release the helper and resubmit the request via
          * Authenticate Negotiate start.
          * If after a KK deny the user's request w/ 407 and mark the helper as
          * Needing YR. */
         const char *errNote = reply.notes.find("message");
-        if (reply.result == HelperReply::Unknown)
+        if (reply.result == Helper::Unknown)
             auth_user_request->denyMessage("Internal Error");
         else if (errNote != NULL)
             auth_user_request->denyMessage(errNote);
         else
             auth_user_request->denyMessage("Negotiate Authentication failed with no reason given");
         auth_user_request->user()->credentials(Auth::Failed);
