@@ -1581,6 +1581,9 @@ int ldbStartSession(client *c) {
             freeClientAsync(c); /* Close the client in the parent side. */
             return 0;
         }
+    } else {
+        serverLog(LL_WARNING,
+            "Redis synchronous debugging eval session started");
     }
 
     /* Setup our debugging session. */
@@ -1615,6 +1618,9 @@ void ldbEndSession(client *c) {
         writeToClient(c->fd, c, 0);
         serverLog(LL_WARNING,"Lua debugging session child exiting");
         exitFromChild(0);
+    } else {
+        serverLog(LL_WARNING,
+            "Redis synchronous debugging eval session ended");
     }
 
     /* Otherwise let's restore client's state. */