@@ -4745,16 +4745,22 @@ void migrateCommand(client *c) {
 
     /* Read the RESTORE replies. */
     int error_from_target = 0;
+    int del_idx = 1; /* Index of the key argument for the replicated DEL op. */
+    robj **newargv;
+
+    if (!copy) newargv = zmalloc(sizeof(robj*)*(num_keys+1));
+
     for (j = 0; j < num_keys; j++) {
         if (syncReadLine(cs->fd, buf2, sizeof(buf2), timeout) <= 0)
             goto socket_err;
-        if (error_from_target) continue; /* Just consume the replies. */
         if ((select && buf1[0] == '-') || buf2[0] == '-') {
             /* On error assume that last_dbid is no longer valid. */
-            cs->last_dbid = -1;
-            addReplyErrorFormat(c,"Target instance replied with error: %s",
-                (select && buf1[0] == '-') ? buf1+1 : buf2+1);
-            error_from_target = 1;
+            if (!error_from_target) {
+                cs->last_dbid = -1;
+                addReplyErrorFormat(c,"Target instance replied with error: %s",
+                    (select && buf1[0] == '-') ? buf1+1 : buf2+1);
+                error_from_target = 1;
+            }
         } else {
             if (!copy) {
                 robj *aux;
@@ -4764,17 +4770,23 @@ void migrateCommand(client *c) {
                 signalModifiedKey(c->db,kv[j]);
                 server.dirty++;
 
-                /* Translate MIGRATE as DEL for replication/AOF. */
-                if (j == 0) {
-                    aux = createStringObject("DEL",3);
-                    rewriteClientCommandArgument(c,0,aux);
-                    decrRefCount(aux);
-                }
-                rewriteClientCommandArgument(c,j+1,kv[j]);
+                /* Populate the argument vector to replace the old one. */
+                newargv[del_idx++] = kv[j];
             }
         }
     }
 
+    if (!copy) {
+        /* Translate MIGRATE as DEL for replication/AOF. */
+        if (del_idx > 1) {
+            newargv[0] = createStringObject("DEL",3);
+            replaceClientCommandVector(c,newargv,del_idx);
+        } else {
+            /* No key transfer acknowledged, no need to rewrite as DEL. */
+            zfree(newargv);
+        }
+    }
+
     if (!error_from_target) {
         /* Update the last_dbid in migrateCachedSocket and reply +OK. */
         cs->last_dbid = dbid;