-#include "squid-old.h"
+#include "squid.h"
 #include "acl/Acl.h"
 #include "acl/FilledChecklist.h"
 #include "auth/UserRequest.h"
 #include "auth/Acl.h"
 #include "auth/AclProxyAuth.h"
+#include "client_side.h"
 #include "HttpRequest.h"
 
-/** retval -1 user not authenticated (authentication error?)
-    retval  0 user not authorized OR user authentication is in pgrogress
-    retval +1 user authenticated and authorized */
-int
+/**
+ * \retval ACCESS_AUTH_REQUIRED credentials missing. challenge required.
+ * \retval ACCESS_DENIED        user not authenticated (authentication error?)
+ * \retval ACCESS_DUNNO         user authentication is in progress
+ * \retval ACCESS_DENIED        user not authorized
+ * \retval ACCESS_ALLOWED       user authenticated and authorized
+ */
+allow_t
 AuthenticateAcl(ACLChecklist *ch)
 {
     ACLFilledChecklist *checklist = Filled(ch);
     HttpRequest *request = checklist->request;
     http_hdr_type headertype;
 
     if (NULL == request) {
         fatal ("requiresRequest SHOULD have been true for this ACL!!");
-        return 0;
+        return ACCESS_DENIED;
     } else if (request->flags.sslBumped) {
         debugs(28, 5, "SslBumped request: It is an encapsulated request do not authenticate");
         checklist->auth_user_request = checklist->conn() != NULL ? checklist->conn()->auth_user_request : request->auth_user_request;
         if (checklist->auth_user_request != NULL)
-            return 1;
+            return ACCESS_ALLOWED;
         else
-            return 0;
+            return ACCESS_DENIED;
     } else if (request->flags.accelerated) {
         /* WWW authorization on accelerated requests */
         headertype = HDR_AUTHORIZATION;
-    } else if (request->flags.intercepted || request->flags.spoof_client_ip) {
-        debugs(28, DBG_IMPORTANT, HERE << " authentication not applicable on intercepted requests.");
-        return -1;
+    } else if (request->flags.intercepted || request->flags.spoofClientIp) {
+        debugs(28, DBG_IMPORTANT, "NOTICE: Authentication not applicable on intercepted requests.");
+        return ACCESS_DENIED;
     } else {
         /* Proxy authorization on proxy requests */
         headertype = HDR_PROXY_AUTHORIZATION;
     }
 
     /* get authed here */
