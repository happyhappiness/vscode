             packerClean(&pck);
         } else if (request_hdrs) {
             p = request_hdrs;
         } else {
             p = "[no request]";
         }
-
         break;
 
     case 's':
-        p = visible_appname_string;
+        /* for backward compat we make %s show the full URL. Drop this in some future release. */
+        if (building_deny_info_url) {
+            p = request ? urlCanonical(request) : url;
+            debugs(0,0, "WARNING: deny_info now accepts coded tags. Use %u to get the full URL instead of %s");
+        } else
+            p = visible_appname_string;
         break;
 
     case 'S':
+        if (building_deny_info_url) {
+            p = visible_appname_string;
+            break;
+        }
         /* signature may contain %-escapes, recursion */
-
         if (page_id != ERR_SQUID_SIGNATURE) {
             const int saved_id = page_id;
             page_id = ERR_SQUID_SIGNATURE;
             MemBuf *sign_mb = BuildContent();
             mb.Printf("%s", sign_mb->content());
             sign_mb->clean();
