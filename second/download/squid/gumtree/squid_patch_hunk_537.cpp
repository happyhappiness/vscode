 dump_generic_port(StoreEntry * e, const char *n, const AnyP::PortCfg * s)
 {
     char buf[MAX_IPSTRLEN];
 
     storeAppendPrintf(e, "%s %s",
                       n,
-                      s->s.ToURL(buf,MAX_IPSTRLEN));
+                      s->s.toUrl(buf,MAX_IPSTRLEN));
 
     // MODES and specific sub-options.
-    if (s->intercepted)
+    if (s->flags.natIntercept)
         storeAppendPrintf(e, " intercept");
 
-    else if (s->spoof_client_ip)
+    else if (s->flags.tproxyIntercept)
         storeAppendPrintf(e, " tproxy");
 
-    else if (s->accel) {
+    else if (s->flags.accelSurrogate) {
         storeAppendPrintf(e, " accel");
 
         if (s->vhost)
             storeAppendPrintf(e, " vhost");
 
         if (s->vport < 0)
