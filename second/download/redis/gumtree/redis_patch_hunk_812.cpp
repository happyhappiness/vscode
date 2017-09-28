     {
         addReply(c, abort_reply ? abort_reply : shared.nullbulk);
         return;
     }
     setKey(c->db,key,val);
     server.dirty++;
-    if (expire) setExpire(c->db,key,mstime()+milliseconds);
+    if (expire) setExpire(c,c->db,key,mstime()+milliseconds);
     notifyKeyspaceEvent(NOTIFY_STRING,"set",key,c->db->id);
     if (expire) notifyKeyspaceEvent(NOTIFY_GENERIC,
         "expire",key,c->db->id);
     addReply(c, ok_reply ? ok_reply : shared.ok);
 }
 
