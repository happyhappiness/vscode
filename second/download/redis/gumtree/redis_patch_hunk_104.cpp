                 if (incr) {
                     score += curscore;
                     if (isnan(score)) {
                         addReplyError(c,nanerr);
                         /* Don't need to check if the sorted set is empty
                          * because we know it has at least one element. */
-                        zfree(scores);
-                        return;
+                        goto cleanup;
                     }
                 }
 
                 /* Remove and re-insert when score changed. We can safely
                  * delete the key object from the skiplist, since the
                  * dictionary still has a reference to it. */
                 if (score != curscore) {
                     redisAssertWithInfo(c,curobj,zslDelete(zs->zsl,curscore,curobj));
                     znode = zslInsert(zs->zsl,score,curobj);
                     incrRefCount(curobj); /* Re-inserted in skiplist. */
                     dictGetVal(de) = &znode->score; /* Update score ptr. */
-
-                    signalModifiedKey(c->db,key);
                     server.dirty++;
+                    updated++;
                 }
             } else {
                 znode = zslInsert(zs->zsl,score,ele);
                 incrRefCount(ele); /* Inserted in skiplist. */
                 redisAssertWithInfo(c,NULL,dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
                 incrRefCount(ele); /* Added to dictionary. */
-
-                signalModifiedKey(c->db,key);
                 server.dirty++;
-                if (!incr) added++;
+                added++;
             }
         } else {
             redisPanic("Unknown sorted set encoding");
         }
     }
-    zfree(scores);
     if (incr) /* ZINCRBY */
         addReplyDouble(c,score);
     else /* ZADD */
         addReplyLongLong(c,added);
+
+cleanup:
+    zfree(scores);
+    if (added || updated) {
+        signalModifiedKey(c->db,key);
+        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,
+            incr ? "zincr" : "zadd", key, c->db->id);
+    }
 }
 
 void zaddCommand(redisClient *c) {
     zaddGenericCommand(c,0);
 }
 
