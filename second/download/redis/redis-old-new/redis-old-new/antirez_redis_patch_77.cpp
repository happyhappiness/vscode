@@ -85,7 +85,7 @@ void setGenericCommand(client *c, int flags, robj *key, robj *val, robj *expire,
     }
     setKey(c->db,key,val);
     server.dirty++;
-    if (expire) setExpire(c->db,key,mstime()+milliseconds);
+    if (expire) setExpire(c,c->db,key,mstime()+milliseconds);
     notifyKeyspaceEvent(NOTIFY_STRING,"set",key,c->db->id);
     if (expire) notifyKeyspaceEvent(NOTIFY_GENERIC,
         "expire",key,c->db->id);