             }
 
         if (!p && conn != NULL && conn->clientConnection->rfc931[0])
             p = conn->clientConnection->rfc931;
 
 #if USE_OPENSSL
-
         if (!p && conn != NULL && Comm::IsConnOpen(conn->clientConnection))
-            p = sslGetUserEmail(fd_table[conn->clientConnection->fd].ssl);
-
+            p = sslGetUserEmail(fd_table[conn->clientConnection->fd].ssl.get());
 #endif
 
         if (!p)
             p = dash_str;
 
         storeAppendPrintf(s, "username %s\n", p);
