     if (s->flags.natIntercept)
         storeAppendPrintf(e, " intercept");
 
     else if (s->flags.tproxyIntercept)
         storeAppendPrintf(e, " tproxy");
 
+    else if (s->flags.proxySurrogate)
+        storeAppendPrintf(e, " require-proxy-header");
+
     else if (s->flags.accelSurrogate) {
         storeAppendPrintf(e, " accel");
 
         if (s->vhost)
             storeAppendPrintf(e, " vhost");
 
