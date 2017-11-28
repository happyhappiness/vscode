     fclose (fp);
 }
 
 int
 getMyPort(void)
 {
-    if (Config.Sockaddr.http)
-        return Config.Sockaddr.http->s.GetPort();
+    AnyP::PortCfg *p = NULL;
+    if ((p = Config.Sockaddr.http)) {
+        // skip any special interception ports
+        while (p && (p->intercepted || p->spoof_client_ip))
+            p = p->next;
+        if (p)
+            return p->s.GetPort();
+    }
 
 #if USE_SSL
-
-    if (Config.Sockaddr.https)
-        return Config.Sockaddr.https->http.s.GetPort();
-
+    if ((p = Config.Sockaddr.https)) {
+        // skip any special interception ports
+        while (p && (p->intercepted || p->spoof_client_ip))
+            p = p->next;
+        if (p)
+            return p->s.GetPort();
+    }
 #endif
 
-    fatal("No port defined");
-
-    return 0;			/* NOT REACHED */
+    debugs(21, DBG_CRITICAL, "ERROR: No forward-proxy ports configured.");
+    return 0; // Invalid port. This will result in invalid URLs on bad configurations.
 }
 
 /*
  * Set the umask to at least the given mask. This is in addition
  * to the umask set at startup
  */
