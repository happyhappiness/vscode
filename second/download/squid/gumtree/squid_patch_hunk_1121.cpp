 
     /* For IPv6 addresses also check for a colon */
     if (Config.appendDomain && !strchr(lc_host, '.') && !strchr(lc_host, ':'))
         strncat(lc_host, Config.appendDomain, SQUIDHOSTNAMELEN -
                 strlen(lc_host) - 1);
 
-    /* build uri in mb */
+    /* build URI */
+    URL tmp(AnyP::PROTO_HTTP);
+    tmp.host(lc_host);
+    if (port)
+        tmp.port(port);
+
     static MemBuf mb;
 
     mb.reset();
-
-    mb.Printf("http://%s", lc_host);
-
-    /* append port if not default */
-    if (port && port != urlDefaultPort(AnyP::PROTO_HTTP))
-        mb.Printf(":%d", port);
+    mb.appendf("http://" SQUIDSBUFPH, SQUIDSBUFPRINT(tmp.authority()));
 
     if (dir)
-        mb.Printf("%s", dir);
+        mb.append(dir, strlen(dir));
 
-    mb.Printf("%s", name);
+    mb.append(name.rawContent(), name.length());
 
     /* return a pointer to a local static buffer */
     return mb.buf;
 }
 
 /*
  * makes internal url with local host and port
  */
 char *
-internalLocalUri(const char *dir, const char *name)
+internalLocalUri(const char *dir, const SBuf &name)
 {
     return internalRemoteUri(getMyHostname(),
                              getMyPort(), dir, name);
 }
 
 const char *
