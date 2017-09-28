      * with SLAVEOF NO ONE we must just return ASAP. */
     if (server.repl_state == REPL_STATE_NONE) {
         close(fd);
         return;
     }
 
-    /* Check for errors in the socket. */
+    /* Check for errors in the socket: after a non blocking connect() we
+     * may find that the socket is in error state. */
     if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &sockerr, &errlen) == -1)
         sockerr = errno;
     if (sockerr) {
         serverLog(LL_WARNING,"Error condition on socket for SYNC: %s",
             strerror(sockerr));
         goto error;
