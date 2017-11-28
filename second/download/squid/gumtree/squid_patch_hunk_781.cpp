             p = "[not available]";
         break;
 
     case 'm':
         if (building_deny_info_url) break;
 #if USE_AUTH
-        p = auth_user_request->denyMessage("[not available]");
+        if (auth_user_request.getRaw())
+            p = auth_user_request->denyMessage("[not available]");
+        else
+            p = "[not available]";
 #else
         p = "-";
 #endif
         break;
 
     case 'M':
-        if (request)
-            p = RequestMethodStr(request->method);
-        else if (!building_deny_info_url)
-            p= "[unknown method]";
+        if (request) {
+            const SBuf &m = request->method.image();
+            mb.append(m.rawContent(), m.length());
+        } else if (!building_deny_info_url)
+            p = "[unknown method]";
         break;
 
     case 'o':
         p = request ? request->extacl_message.termedBuf() : external_acl_message;
         if (!p && !building_deny_info_url)
             p = "[not available]";
