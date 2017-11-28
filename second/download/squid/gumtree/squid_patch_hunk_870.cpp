         storeAppendPrintf(s, "out.offset %ld, out.size %lu\n",
                           (long int) http->out.offset, (unsigned long int) http->out.size);
         storeAppendPrintf(s, "req_sz %ld\n", (long int) http->req_sz);
         e = http->storeEntry();
         storeAppendPrintf(s, "entry %p/%s\n", e, e ? e->getMD5Text() : "N/A");
         storeAppendPrintf(s, "start %ld.%06d (%f seconds ago)\n",
-                          (long int) http->start_time.tv_sec,
-                          (int) http->start_time.tv_usec,
-                          tvSubDsec(http->start_time, current_time));
+                          (long int) http->al->cache.start_time.tv_sec,
+                          (int) http->al->cache.start_time.tv_usec,
+                          tvSubDsec(http->al->cache.start_time, current_time));
 #if USE_AUTH
         if (http->request->auth_user_request != NULL)
             p = http->request->auth_user_request->username();
         else
 #endif
-            if (http->request->extacl_user.defined()) {
+            if (http->request->extacl_user.size() > 0) {
                 p = http->request->extacl_user.termedBuf();
             }
 
         if (!p && conn != NULL && conn->clientConnection->rfc931[0])
             p = conn->clientConnection->rfc931;
 
-#if USE_SSL
+#if USE_OPENSSL
 
         if (!p && conn != NULL && Comm::IsConnOpen(conn->clientConnection))
             p = sslGetUserEmail(fd_table[conn->clientConnection->fd].ssl);
 
 #endif
 
