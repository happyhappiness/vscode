         local_auth_user->expiretime = current_time.tv_sec;
         auth_user_request->user()->credentials(Auth::Ok);
         debugs(29, 4, HERE << "Successfully validated user via Negotiate. Username '" << auth_user_request->user()->username() << "'");
     }
     break;
 
-    case HelperReply::Error: {
+    case Helper::Error: {
         const char *messageNote = reply.notes.find("message");
         const char *tokenNote = reply.notes.findFirst("token");
 
         /* authentication failure (wrong password, etc.) */
         if (messageNote != NULL)
             auth_user_request->denyMessage(messageNote);
