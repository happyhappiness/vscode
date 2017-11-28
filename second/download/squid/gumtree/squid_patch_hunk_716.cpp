         } else {
             auth_user_request->user()->credentials(Auth::Failed);
             auth_user_request->denyMessage("Negotiate authentication requires a persistent connection");
         }
         break;
 
-    case HelperReply::Okay: {
+    case Helper::Okay: {
         const char *userNote = reply.notes.findFirst("user");
         const char *tokenNote = reply.notes.findFirst("token");
         if (userNote == NULL || tokenNote == NULL) {
             // XXX: handle a success with no username better
             /* protocol error */
             fatalf("authenticateNegotiateHandleReply: *** Unsupported helper response ***, '%s'\n", reply.other().content());
