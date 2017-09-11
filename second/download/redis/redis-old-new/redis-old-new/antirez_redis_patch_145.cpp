@@ -1644,19 +1644,24 @@ int listenToPort(int port, int *fds, int *count) {
             if (fds[*count] != ANET_ERR) {
                 anetNonBlock(NULL,fds[*count]);
                 (*count)++;
-            } else if (errno == EAFNOSUPPORT)
+            } else if (errno == EAFNOSUPPORT) {
                 unsupported++;
+                serverLog(LL_WARNING,"Not listening to IPv6: unsupproted");
+            }
 
-            /* Bind the IPv4 address as well. */
-            fds[*count] = anetTcpServer(server.neterr,port,NULL,
-                server.tcp_backlog);
-            if (fds[*count] != ANET_ERR) {
-                anetNonBlock(NULL,fds[*count]);
-                (*count)++;
-            } else if (errno == EAFNOSUPPORT)
-                unsupported++;
+            if (*count == 1 || unsupported) {
+                /* Bind the IPv4 address as well. */
+                fds[*count] = anetTcpServer(server.neterr,port,NULL,
+                    server.tcp_backlog);
+                if (fds[*count] != ANET_ERR) {
+                    anetNonBlock(NULL,fds[*count]);
+                    (*count)++;
+                } else if (errno == EAFNOSUPPORT) {
+                    unsupported++;
+                    serverLog(LL_WARNING,"Not listening to IPv4: unsupproted");
+                }
+            }
             /* Exit the loop if we were able to bind * on IPv4 and IPv6,
-             * or if one is unsupported by th OS.
              * otherwise fds[*count] will be ANET_ERR and we'll print an
              * error and return to the caller with an error. */
             if (*count + unsupported == 2) break;