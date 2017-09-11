@@ -509,12 +509,17 @@ void lremCommand(client *c) {
     }
     listTypeReleaseIterator(li);
 
+    if (removed) {
+        signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"lrem",c->argv[1],c->db->id);
+    }
+
     if (listTypeLength(subject) == 0) {
         dbDelete(c->db,c->argv[1]);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
     }
 
     addReplyLongLong(c,removed);
-    if (removed) signalModifiedKey(c->db,c->argv[1]);
 }
 
 /* This is the semantic of this command: