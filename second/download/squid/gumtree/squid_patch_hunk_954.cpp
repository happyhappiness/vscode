  */
 allow_t
 AuthenticateAcl(ACLChecklist *ch)
 {
     ACLFilledChecklist *checklist = Filled(ch);
     HttpRequest *request = checklist->request;
-    http_hdr_type headertype;
+    Http::HdrType headertype;
 
     if (NULL == request) {
         fatal ("requiresRequest SHOULD have been true for this ACL!!");
         return ACCESS_DENIED;
     } else if (request->flags.sslBumped) {
         debugs(28, 5, "SslBumped request: It is an encapsulated request do not authenticate");
