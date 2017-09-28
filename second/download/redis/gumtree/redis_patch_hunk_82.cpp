             dbAdd(c->db,c->argv[1],lobj);
         }
         listTypePush(lobj,c->argv[j],where);
         pushed++;
     }
     addReplyLongLong(c, waiting + (lobj ? listTypeLength(lobj) : 0));
-    if (pushed) signalModifiedKey(c->db,c->argv[1]);
+    if (pushed) {
+        char *event = (where == REDIS_HEAD) ? "lpush" : "rpush";
+
+        signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,c->argv[1],c->db->id);
+    }
     server.dirty += pushed;
 }
 
 void lpushCommand(redisClient *c) {
     pushGenericCommand(c,REDIS_HEAD);
 }
