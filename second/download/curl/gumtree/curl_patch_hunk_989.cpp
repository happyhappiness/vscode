   case PARAM_BAD_NUMERIC:
     return "expected a proper numerical parameter";
   case PARAM_NEGATIVE_NUMERIC:
     return "expected a positive numerical parameter";
   case PARAM_LIBCURL_DOESNT_SUPPORT:
     return "the installed libcurl version doesn't support this";
+  case PARAM_LIBCURL_UNSUPPORTED_PROTOCOL:
+    return "a specified protocol is unsupported by libcurl";
   case PARAM_NO_MEM:
     return "out of memory";
   default:
     return "unknown error";
   }
 }
 
 int SetHTTPrequest(struct OperationConfig *config, HttpReq req, HttpReq *store)
 {
+  /* this mirrors the HttpReq enum in tool_sdecls.h */
+  const char *reqname[]= {
+    "", /* unspec */
+    "GET (-G, --get)",
+    "HEAD (-I, --head)",
+    "multipart formpost (-F, --form)",
+    "POST (-d, --data)"
+  };
+
   if((*store == HTTPREQ_UNSPEC) ||
      (*store == req)) {
     *store = req;
     return 0;
   }
-
-  warnf(config->global, "You can only select one HTTP request!\n");
+  warnf(config->global, "You can only select one HTTP request method! "
+        "You asked for both %s and %s.\n",
+        reqname[req], reqname[*store]);
 
   return 1;
 }
+
+void customrequest_helper(struct OperationConfig *config, HttpReq req,
+                          char *method)
+{
+  /* this mirrors the HttpReq enum in tool_sdecls.h */
+  const char *dflt[]= {
+    "GET",
+    "GET",
+    "HEAD",
+    "POST",
+    "POST"
+  };
+
+  if(!method)
+    ;
+  else if(curl_strequal(method, dflt[req])) {
+    notef(config->global, "Unnecessary use of -X or --request, %s is already "
+          "inferred.\n", dflt[req]);
+  }
+  else if(curl_strequal(method, "head")) {
+    warnf(config->global,
+          "Setting custom HTTP method to HEAD may not work the way you "
+          "want.\n");
+  }
+}
