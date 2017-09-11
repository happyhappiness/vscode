@@ -579,7 +579,7 @@ int clientHasPendingReplies(client *c) {
 }
 
 #define MAX_ACCEPTS_PER_CALL 1000
-static void acceptCommonHandler(int fd, int flags) {
+static void acceptCommonHandler(int fd, int flags, char *ip) {
     client *c;
     if ((c = createClient(fd)) == NULL) {
         serverLog(LL_WARNING,
@@ -603,6 +603,48 @@ static void acceptCommonHandler(int fd, int flags) {
         freeClient(c);
         return;
     }
+
+    /* If the server is running in protected mode (the default) and there
+     * is no password set, nor a specific interface is bound, we don't accept
+     * requests from non loopback interfaces. Instead we try to explain the
+     * user what to do to fix it if needed. */
+    if (server.protected_mode &&
+        server.bindaddr_count == 0 &&
+        server.requirepass == NULL &&
+        !(flags & CLIENT_UNIX_SOCKET) &&
+        ip != NULL)
+    {
+        if (strcmp(ip,"127.0.0.1") && strcmp(ip,"::1")) {
+            char *err =
+                "-DENIED Redis is running in protected mode because protected "
+                "mode is enabled, no bind address was specified, no "
+                "authentication password is requested to clients. In this mode "
+                "connections are only accepted from the lookback interface. "
+                "If you want to connect from external computers to Redis you "
+                "may adopt one of the following solutions: "
+                "1) Just disable protected mode sending the command "
+                "'CONFIG SET protected-mode no' from the loopback interface "
+                "by connecting to Redis from the same host the server is "
+                " running, however MAKE SURE Redis is not publicly accessible "
+                "from internet if you do so. Use CONFIG REWRITE to make this "
+                "change permanent. "
+                "2) Alternatively you can just disable the protected mode by "
+                "editing the Redis configuration file, and setting the protected "
+                "mode option to 'no', and then restarting the server. "
+                "3) If you started the server manually just for testing, restart "
+                "it with the '--portected-mode no' option. "
+                "4) Setup a bind address or an authentication password. "
+                "NOTE: You only need to do one of the above things in order for "
+                "the server to start accepting connections from the outside.\r\n";
+            if (write(c->fd,err,strlen(err)) == -1) {
+                /* Nothing to do, Just to avoid the warning... */
+            }
+            server.stat_rejected_conn++;
+            freeClient(c);
+            return;
+        }
+    }
+
     server.stat_numconnections++;
     c->flags |= flags;
 }
@@ -623,7 +665,7 @@ void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
             return;
         }
         serverLog(LL_VERBOSE,"Accepted %s:%d", cip, cport);
-        acceptCommonHandler(cfd,0);
+        acceptCommonHandler(cfd,0,cip);
     }
 }
 
@@ -642,7 +684,7 @@ void acceptUnixHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
             return;
         }
         serverLog(LL_VERBOSE,"Accepted connection to %s", server.unixsocket);
-        acceptCommonHandler(cfd,CLIENT_UNIX_SOCKET);
+        acceptCommonHandler(cfd,CLIENT_UNIX_SOCKET,NULL);
     }
 }
 