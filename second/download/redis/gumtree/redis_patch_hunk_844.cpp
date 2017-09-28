         addReply(c,shared.ok);
     } else {
         addReplyError(c, "Syntax error, try CLIENT (LIST | KILL | GETNAME | SETNAME | PAUSE | REPLY)");
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
 void rewriteClientCommandVector(client *c, int argc, ...) {
     va_list ap;
     int j;
