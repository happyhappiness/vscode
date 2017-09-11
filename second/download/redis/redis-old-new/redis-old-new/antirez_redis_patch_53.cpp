@@ -1007,6 +1007,16 @@ void configSetCommand(client *c) {
       "activerehashing",server.activerehashing) {
     } config_set_bool_field(
       "activedefrag",server.active_defrag_enabled) {
+#ifndef HAVE_DEFRAG
+        if (server.active_defrag_enabled) {
+            server.active_defrag_enabled = 0;
+            addReplyError(c,
+                "Active defragmentation cannot be enabled: it requires a "
+                "Redis server compiled with a modified Jemalloc like the "
+                "one shipped by default with the Redis source distribution");
+            return;
+        }
+#endif
     } config_set_bool_field(
       "protected-mode",server.protected_mode) {
     } config_set_bool_field(