             fatalf("authenticateNegotiateHandleReply: *** Unsupported helper response ***, '%s'\n", reply.other().content());
             break;
         }
 
         /* we're finished, release the helper */
         auth_user_request->user()->username(userNote);
-        auth_user_request->denyMessage("Login successful");
+        auth_user_request->setDenyMessage("Login successful");
         safe_free(lm_request->server_blob);
         lm_request->server_blob = xstrdup(tokenNote);
         lm_request->releaseAuthServer();
 
         /* connection is authenticated */
         debugs(29, 4, HERE << "authenticated user " << auth_user_request->user()->username());
-        /* see if this is an existing user */
-        AuthUserHashPointer *usernamehash = static_cast<AuthUserHashPointer *>(hash_lookup(proxy_auth_username_cache, auth_user_request->user()->userKey()));
-        Auth::User::Pointer local_auth_user = lm_request->user();
-        while (usernamehash && (usernamehash->user()->auth_type != Auth::AUTH_NEGOTIATE ||
-                                strcmp(usernamehash->user()->userKey(), auth_user_request->user()->userKey()) != 0))
-            usernamehash = static_cast<AuthUserHashPointer *>(usernamehash->next);
-        if (usernamehash) {
+        auto local_auth_user = lm_request->user();
+        auto cached_user = Auth::Negotiate::User::Cache()->lookup(auth_user_request->user()->userKey());
+        if (!cached_user) {
+            local_auth_user->addToNameCache();
+        } else {
             /* we can't seamlessly recheck the username due to the
              * challenge-response nature of the protocol.
              * Just free the temporary auth_user after merging as
              * much of it new state into the existing one as possible */
-            usernamehash->user()->absorb(local_auth_user);
+            cached_user->absorb(local_auth_user);
             /* from here on we are working with the original cached credentials. */
-            local_auth_user = usernamehash->user();
+            local_auth_user = cached_user;
             auth_user_request->user(local_auth_user);
-        } else {
-            /* store user in hash's */
-            local_auth_user->addToNameCache();
         }
         /* set these to now because this is either a new login from an
          * existing user or a new user */
         local_auth_user->expiretime = current_time.tv_sec;
         auth_user_request->user()->credentials(Auth::Ok);
         debugs(29, 4, HERE << "Successfully validated user via Negotiate. Username '" << auth_user_request->user()->username() << "'");
     }
     break;
 
-    case Helper::Error: {
-        const char *messageNote = reply.notes.find("message");
-        const char *tokenNote = reply.notes.findFirst("token");
-
+    case Helper::Error:
         /* authentication failure (wrong password, etc.) */
-        if (messageNote != NULL)
-            auth_user_request->denyMessage(messageNote);
-        else
-            auth_user_request->denyMessage("Negotiate Authentication denied with no reason given");
+        auth_user_request->denyMessageFromHelper("Negotiate", reply);
         auth_user_request->user()->credentials(Auth::Failed);
         safe_free(lm_request->server_blob);
-        if (tokenNote != NULL)
+        if (const char *tokenNote = reply.notes.findFirst("token"))
             lm_request->server_blob = xstrdup(tokenNote);
         lm_request->releaseAuthServer();
         debugs(29, 4, "Failed validating user via Negotiate. Result: " << reply);
-    }
-    break;
+        break;
 
     case Helper::Unknown:
         debugs(29, DBG_IMPORTANT, "ERROR: Negotiate Authentication Helper '" << reply.whichServer << "' crashed!.");
     /* continue to the next case */
 
-    case Helper::BrokenHelper: {
+    case Helper::TimedOut:
+    case Helper::BrokenHelper:
         /* TODO kick off a refresh process. This can occur after a YR or after
          * a KK. If after a YR release the helper and resubmit the request via
          * Authenticate Negotiate start.
          * If after a KK deny the user's request w/ 407 and mark the helper as
          * Needing YR. */
-        const char *errNote = reply.notes.find("message");
         if (reply.result == Helper::Unknown)
-            auth_user_request->denyMessage("Internal Error");
-        else if (errNote != NULL)
-            auth_user_request->denyMessage(errNote);
+            auth_user_request->setDenyMessage("Internal Error");
         else
-            auth_user_request->denyMessage("Negotiate Authentication failed with no reason given");
+            auth_user_request->denyMessageFromHelper("Negotiate", reply);
         auth_user_request->user()->credentials(Auth::Failed);
         safe_free(lm_request->server_blob);
         lm_request->releaseAuthServer();
         debugs(29, DBG_IMPORTANT, "ERROR: Negotiate Authentication validating user. Result: " << reply);
-    } // break;
+        break;
     }
 
     if (lm_request->request) {
         HTTPMSGUNLOCK(lm_request->request);
         lm_request->request = NULL;
     }
