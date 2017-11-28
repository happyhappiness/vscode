 
     if (NULL == request) {
         fatal ("requiresRequest SHOULD have been true for this ACL!!");
         return ACCESS_DENIED;
     } else if (request->flags.sslBumped) {
         debugs(28, 5, "SslBumped request: It is an encapsulated request do not authenticate");
-        checklist->auth_user_request = checklist->conn() != NULL ? checklist->conn()->auth_user_request : request->auth_user_request;
+        checklist->auth_user_request = checklist->conn() != NULL ? checklist->conn()->getAuth() : request->auth_user_request;
         if (checklist->auth_user_request != NULL)
             return ACCESS_ALLOWED;
         else
             return ACCESS_DENIED;
     } else if (request->flags.accelerated) {
         /* WWW authorization on accelerated requests */
         headertype = HDR_AUTHORIZATION;
-    } else if (request->flags.intercepted || request->flags.spoofClientIp) {
+    } else if (request->flags.intercepted || request->flags.interceptTproxy) {
         debugs(28, DBG_IMPORTANT, "NOTICE: Authentication not applicable on intercepted requests.");
         return ACCESS_DENIED;
     } else {
         /* Proxy authorization on proxy requests */
         headertype = HDR_PROXY_AUTHORIZATION;
     }
