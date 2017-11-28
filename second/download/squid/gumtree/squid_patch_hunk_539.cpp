         else
             pmtu = "transparent";
 
         storeAppendPrintf(e, " disable-pmtu-discovery=%s", pmtu);
     }
 
-    if (s->s.IsAnyAddr() && !s->s.IsIPv6())
+    if (s->s.isAnyAddr() && !s->s.isIPv6())
         storeAppendPrintf(e, " ipv4");
 
     if (s->tcp_keepalive.enabled) {
         if (s->tcp_keepalive.idle || s->tcp_keepalive.interval || s->tcp_keepalive.timeout) {
             storeAppendPrintf(e, " tcpkeepalive=%d,%d,%d", s->tcp_keepalive.idle, s->tcp_keepalive.interval, s->tcp_keepalive.timeout);
         } else {
             storeAppendPrintf(e, " tcpkeepalive");
         }
     }
 
 #if USE_SSL
-    if (s->sslBump)
+    if (s->flags.tunnelSslBumping)
         storeAppendPrintf(e, " ssl-bump");
 
     if (s->cert)
         storeAppendPrintf(e, " cert=%s", s->cert);
 
     if (s->key)
