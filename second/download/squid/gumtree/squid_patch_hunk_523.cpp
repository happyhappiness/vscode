             local_auth_user->addToNameCache();
         }
         /* set these to now because this is either a new login from an
          * existing user or a new user */
         local_auth_user->expiretime = current_time.tv_sec;
         auth_user_request->user()->credentials(Auth::Ok);
-        debugs(29, 4, HERE << "Successfully validated user via Negotiate. Username '" << blob << "'");
+        debugs(29, 4, HERE << "Successfully validated user via Negotiate. Username '" << auth_user_request->user()->username() << "'");
+    }
+    break;
 
-    } else if (strncasecmp(reply, "NA ", 3) == 0 && arg != NULL) {
-        /* authentication failure (wrong password, etc.) */
+    case HelperReply::Error: {
+        const char *messageNote = reply.notes.find("message");
+        const char *tokenNote = reply.notes.findFirst("token");
 
-        if (arg) {
-            *arg = '\0';
-            ++arg;
-        }
-
-        auth_user_request->denyMessage(arg);
+        /* authentication failure (wrong password, etc.) */
+        if (messageNote != NULL)
+            auth_user_request->denyMessage(messageNote);
+        else
+            auth_user_request->denyMessage("Negotiate Authentication denied with no reason given");
         auth_user_request->user()->credentials(Auth::Failed);
         safe_free(lm_request->server_blob);
-        lm_request->server_blob = xstrdup(blob);
+        if (tokenNote != NULL)
+            lm_request->server_blob = xstrdup(tokenNote);
         lm_request->releaseAuthServer();
-        debugs(29, 4, HERE << "Failed validating user via Negotiate. Error returned '" << blob << "'");
-    } else if (strncasecmp(reply, "BH ", 3) == 0) {
+        debugs(29, 4, "Failed validating user via Negotiate. Result: " << reply);
+    }
+    break;
+
+    case HelperReply::Unknown:
+        debugs(29, DBG_IMPORTANT, "ERROR: Negotiate Authentication Helper '" << reply.whichServer << "' crashed!.");
+        /* continue to the next case */
+
+    case HelperReply::BrokenHelper: {
         /* TODO kick off a refresh process. This can occur after a YR or after
          * a KK. If after a YR release the helper and resubmit the request via
          * Authenticate Negotiate start.
          * If after a KK deny the user's request w/ 407 and mark the helper as
          * Needing YR. */
-        auth_user_request->denyMessage(blob);
+        const char *errNote = reply.notes.find("message");
+        if (reply.result == HelperReply::Unknown)
+            auth_user_request->denyMessage("Internal Error");
+        else if (errNote != NULL)
+            auth_user_request->denyMessage(errNote);
+        else
+            auth_user_request->denyMessage("Negotiate Authentication failed with no reason given");
         auth_user_request->user()->credentials(Auth::Failed);
         safe_free(lm_request->server_blob);
         lm_request->releaseAuthServer();
-        debugs(29, DBG_IMPORTANT, "ERROR: Negotiate Authentication validating user. Error returned '" << reply << "'");
-    } else {
-        /* protocol error */
-        fatalf("authenticateNegotiateHandleReply: *** Unsupported helper response ***, '%s'\n", reply);
+        debugs(29, DBG_IMPORTANT, "ERROR: Negotiate Authentication validating user. Result: " << reply);
+    } // break;
     }
 
     if (lm_request->request) {
         HTTPMSGUNLOCK(lm_request->request);
         lm_request->request = NULL;
     }
     r->handler(r->data);
     delete r;
 }
 
-void
-Auth::Negotiate::UserRequest::addAuthenticationInfoHeader(HttpReply * rep, int accel)
-{
-    http_hdr_type type;
-
-    if (!server_blob)
-        return;
-
-    /* don't add to authentication error pages */
-    if ((!accel && rep->sline.status == HTTP_PROXY_AUTHENTICATION_REQUIRED)
-            || (accel && rep->sline.status == HTTP_UNAUTHORIZED))
-        return;
-
-    type = accel ? HDR_AUTHENTICATION_INFO : HDR_PROXY_AUTHENTICATION_INFO;
-    httpHeaderPutStrf(&rep->header, type, "Negotiate %s", server_blob);
-
-    safe_free(server_blob);
-}
