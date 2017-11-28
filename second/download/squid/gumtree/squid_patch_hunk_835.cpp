     if (user && !*user)
         safe_free(user);
 
     char clientip[MAX_IPSTRLEN];
     al->getLogClientIp(clientip, MAX_IPSTRLEN);
 
-    logfilePrintf(logfile, "%9ld.%03d %6d %s %s%s/%03d %" PRId64 " %s %s %s %s%s/%s %s%s",
+    static SBuf method;
+    if (al->_private.method_str)
+        method.assign(al->_private.method_str);
+    else
+        method = al->http.method.image();
+
+    logfilePrintf(logfile, "%9ld.%03d %6d %s %s%s/%03d %" PRId64 " " SQUIDSBUFPH " %s %s %s%s/%s %s%s",
                   (long int) current_time.tv_sec,
                   (int) current_time.tv_usec / 1000,
                   al->cache.msec,
                   clientip,
                   LogTags_str[al->cache.code],
                   al->http.statusSfx(),
                   al->http.code,
-                  al->cache.replySize,
-                  al->_private.method_str,
+                  al->http.clientReplySz.messageTotal(),
+                  SQUIDSBUFPRINT(method),
                   al->url,
                   user ? user : dash_str,
                   al->hier.ping.timedout ? "TIMEOUT_" : "",
                   hier_code_str[al->hier.code],
                   al->hier.tcpServer != NULL ? al->hier.tcpServer->remote.toStr(hierHost, sizeof(hierHost)) : "-",
                   al->http.content_type,
