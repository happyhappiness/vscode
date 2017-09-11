@@ -1164,6 +1164,19 @@ void evalGenericCommand(client *c, int evalsha) {
         lua_pop(lua,1); /* Remove the error handler. */
     }
 
+    /* If we are using single commands replication, emit EXEC if there
+     * was at least a write. */
+    if (server.lua_replicate_commands) {
+        preventCommandPropagation(c);
+        if (server.lua_multi_emitted) {
+            robj *propargv[1];
+            propargv[0] = createStringObject("EXEC",4);
+            alsoPropagate(server.execCommand,c->db->id,propargv,1,
+                PROPAGATE_AOF|PROPAGATE_REPL);
+            decrRefCount(propargv[0]);
+        }
+    }
+
     /* EVALSHA should be propagated to Slave and AOF file as full EVAL, unless
      * we are sure that the script was already in the context of all the
      * attached slaves *and* the current AOF file if enabled.
@@ -1186,22 +1199,10 @@ void evalGenericCommand(client *c, int evalsha) {
             rewriteClientCommandArgument(c,0,
                 resetRefCount(createStringObject("EVAL",4)));
             rewriteClientCommandArgument(c,1,script);
+            printf("forceCommandPropagation\n");
             forceCommandPropagation(c,PROPAGATE_REPL|PROPAGATE_AOF);
         }
     }
-
-    /* If we are using single commands replication, emit EXEC if there
-     * was at least a write. */
-    if (server.lua_replicate_commands) {
-        preventCommandPropagation(c);
-        if (server.lua_multi_emitted) {
-            robj *propargv[1];
-            propargv[0] = createStringObject("EXEC",4);
-            alsoPropagate(server.execCommand,c->db->id,propargv,1,
-                PROPAGATE_AOF|PROPAGATE_REPL);
-            decrRefCount(propargv[0]);
-        }
-    }
 }
 
 void evalCommand(client *c) {