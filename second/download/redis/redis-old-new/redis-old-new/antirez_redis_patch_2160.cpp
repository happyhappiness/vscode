@@ -4790,17 +4790,14 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long
         if (dictSize((dict*)dstset->ptr) > 0) {
             dictAdd(c->db->dict,dstkey,dstset);
             incrRefCount(dstkey);
+            addReplyLong(c,dictSize((dict*)dstset->ptr));
         } else {
             decrRefCount(dstset);
+            addReply(c,shared.czero);
         }
-    }
-
-    if (!dstkey) {
-        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
-    } else {
-        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",
-            dictSize((dict*)dstset->ptr)));
         server.dirty++;
+    } else {
+        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
     }
     zfree(dv);
 }
@@ -4873,7 +4870,8 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
         }
         dictReleaseIterator(di);
 
-        if (op == REDIS_OP_DIFF && cardinality == 0) break; /* result set is empty */
+        /* result set is empty? Exit asap. */
+        if (op == REDIS_OP_DIFF && cardinality == 0) break;
     }
 
     /* Output the content of the resulting set, if not in STORE mode */
@@ -4887,24 +4885,19 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
             addReplyBulk(c,ele);
         }
         dictReleaseIterator(di);
+        decrRefCount(dstset);
     } else {
         /* If we have a target key where to store the resulting set
          * create this key with the result set inside */
         deleteKey(c->db,dstkey);
         if (dictSize((dict*)dstset->ptr) > 0) {
             dictAdd(c->db->dict,dstkey,dstset);
             incrRefCount(dstkey);
+            addReplyLong(c,dictSize((dict*)dstset->ptr));
         } else {
             decrRefCount(dstset);
+            addReply(c,shared.czero);
         }
-    }
-
-    /* Cleanup */
-    if (!dstkey) {
-        decrRefCount(dstset);
-    } else {
-        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",
-            dictSize((dict*)dstset->ptr)));
         server.dirty++;
     }
     zfree(dv);