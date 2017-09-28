     new = createStringObjectFromLongLong(value);
     if (o)
         dbOverwrite(c->db,c->argv[1],new);
     else
         dbAdd(c->db,c->argv[1],new);
     signalModifiedKey(c->db,c->argv[1]);
+    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"incrby",c->argv[1],c->db->id);
     server.dirty++;
     addReply(c,shared.colon);
     addReply(c,new);
     addReply(c,shared.crlf);
 }
 
