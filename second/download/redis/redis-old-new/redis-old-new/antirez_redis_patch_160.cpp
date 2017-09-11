@@ -1242,8 +1242,10 @@ void processInputBuffer(client *c) {
 
         /* CLIENT_CLOSE_AFTER_REPLY closes the connection once the reply is
          * written to the client. Make sure to not let the reply grow after
-         * this flag has been set (i.e. don't process more commands). */
-        if (c->flags & CLIENT_CLOSE_AFTER_REPLY) break;
+         * this flag has been set (i.e. don't process more commands).
+         *
+         * The same applies for clients we want to terminate ASAP. */
+        if (c->flags & (CLIENT_CLOSE_AFTER_REPLY|CLIENT_CLOSE_ASAP)) break;
 
         /* Determine request type when unknown. */
         if (!c->reqtype) {
@@ -1610,6 +1612,26 @@ void clientCommand(client *c) {
     }
 }
 
+/* This callback is bound to POST and "Host:" command names. Those are not
+ * really commands, but are used in security attacks in order to talk to
+ * Redis instances via HTTP, with a technique called "cross protocol scripting"
+ * which exploits the fact that services like Redis will discard invalid
+ * HTTP headers and will process what follows.
+ *
+ * As a protection against this attack, Redis will terminate the connection
+ * when a POST or "Host:" header is seen, and will log the event from
+ * time to time (to avoid creating a DOS as a result of too many logs). */
+void securityWarningCommand(client *c) {
+    static time_t logged_time;
+    time_t now = time(NULL);
+
+    if (labs(now-logged_time) > 60) {
+        serverLog(LL_WARNING,"Possible SECURITY ATTACK detected. It looks like somebody is sending POST or Host: commands to Redis. This is likely due to an attacker attempting to use Cross Protocol Scripting to compromise your Redis instance. Connection aborted.");
+        logged_time = now;
+    }
+    freeClientAsync(c);
+}
+
 /* Rewrite the command vector of the client. All the new objects ref count
  * is incremented. The old command vector is freed, and the old objects
  * ref count is decremented. */