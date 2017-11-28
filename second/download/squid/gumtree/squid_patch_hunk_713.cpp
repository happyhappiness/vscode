     /* this is okay since we only play with the Auth::Basic::User child fields below
      * and dont pass the pointer itself anywhere */
     Auth::Basic::User *basic_auth = dynamic_cast<Auth::Basic::User *>(r->auth_user_request->user().getRaw());
 
     assert(basic_auth != NULL);
 
-    if (reply.result == HelperReply::Okay)
+    if (reply.result == Helper::Okay)
         basic_auth->credentials(Auth::Ok);
     else {
         basic_auth->credentials(Auth::Failed);
 
         if (reply.other().hasContent())
             r->auth_user_request->setDenyMessage(reply.other().content());
