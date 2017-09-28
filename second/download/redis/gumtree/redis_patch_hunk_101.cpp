 
         /* Append the value */
         o->ptr = sdscatlen(o->ptr,append->ptr,sdslen(append->ptr));
         totlen = sdslen(o->ptr);
     }
     signalModifiedKey(c->db,c->argv[1]);
+    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"append",c->argv[1],c->db->id);
     server.dirty++;
     addReplyLongLong(c,totlen);
 }
 
 void strlenCommand(redisClient *c) {
     robj *o;
