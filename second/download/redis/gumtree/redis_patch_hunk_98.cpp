         }
     }
 
     for (j = 1; j < c->argc; j += 2) {
         c->argv[j+1] = tryObjectEncoding(c->argv[j+1]);
         setKey(c->db,c->argv[j],c->argv[j+1]);
+        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",c->argv[j],c->db->id);
     }
     server.dirty += (c->argc-1)/2;
     addReply(c, nx ? shared.cone : shared.ok);
 }
 
 void msetCommand(redisClient *c) {
