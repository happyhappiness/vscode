         totlen += nwritten;
         buf += nwritten;
     }
     return totlen;
 }
 
-static int anetListen(char *err, int s, struct sockaddr *sa, socklen_t len) {
+static int anetListen(char *err, int s, struct sockaddr *sa, socklen_t len, int backlog) {
     if (bind(s,sa,len) == -1) {
         anetSetError(err, "bind: %s", strerror(errno));
         close(s);
         return ANET_ERR;
     }
 
-    /* Use a backlog of 512 entries. We pass 511 to the listen() call because
-     * the kernel does: backlogsize = roundup_pow_of_two(backlogsize + 1);
-     * which will thus give us a backlog of 512 entries */
-    if (listen(s, 511) == -1) {
+    if (listen(s, backlog) == -1) {
         anetSetError(err, "listen: %s", strerror(errno));
         close(s);
         return ANET_ERR;
     }
     return ANET_OK;
 }
