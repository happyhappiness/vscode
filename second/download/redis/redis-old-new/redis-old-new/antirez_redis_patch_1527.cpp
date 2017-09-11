@@ -1509,8 +1509,16 @@ void migrateCommand(redisClient *c) {
             addReplyErrorFormat(c,"Target instance replied with error: %s",
                 (buf1[0] == '-') ? buf1+1 : buf2+1);
         } else {
+            robj *aux;
+
             dbDelete(c->db,c->argv[3]);
             addReply(c,shared.ok);
+            server.dirty++;
+
+            /* Translate MIGRATE as DEL for replication/AOF. */
+            aux = createStringObject("DEL",2);
+            rewriteClientCommandVector(c,2,aux,c->argv[3]);
+            decrRefCount(aux);
         }
     }
 