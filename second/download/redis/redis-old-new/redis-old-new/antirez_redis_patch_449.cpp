@@ -1085,7 +1085,7 @@ unsigned int zsetLength(robj *zobj) {
     } else if (zobj->encoding == OBJ_ENCODING_SKIPLIST) {
         length = ((zset*)zobj->ptr)->zsl->length;
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
     return length;
 }
@@ -1105,7 +1105,7 @@ void zsetConvert(robj *zobj, int encoding) {
         long long vlong;
 
         if (encoding != OBJ_ENCODING_SKIPLIST)
-            redisPanic("Unknown target encoding");
+            serverPanic("Unknown target encoding");
 
         zs = zmalloc(sizeof(*zs));
         zs->dict = dictCreate(&zsetDictType,NULL);
@@ -1138,7 +1138,7 @@ void zsetConvert(robj *zobj, int encoding) {
         unsigned char *zl = ziplistNew();
 
         if (encoding != OBJ_ENCODING_ZIPLIST)
-            redisPanic("Unknown target encoding");
+            serverPanic("Unknown target encoding");
 
         /* Approach similar to zslFree(), since we want to free the skiplist at
          * the same time as creating the ziplist. */
@@ -1162,7 +1162,7 @@ void zsetConvert(robj *zobj, int encoding) {
         zobj->ptr = zl;
         zobj->encoding = OBJ_ENCODING_ZIPLIST;
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
 }
 
@@ -1181,7 +1181,7 @@ int zsetScore(robj *zobj, robj *member, double *score) {
         if (de == NULL) return C_ERR;
         *score = *(double*)dictGetVal(de);
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
     return C_OK;
 }
@@ -1365,7 +1365,7 @@ void zaddGenericCommand(client *c, int flags) {
                 processed++;
             }
         } else {
-            redisPanic("Unknown sorted set encoding");
+            serverPanic("Unknown sorted set encoding");
         }
     }
 
@@ -1383,7 +1383,7 @@ void zaddGenericCommand(client *c, int flags) {
     zfree(scores);
     if (added || updated) {
         signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,
+        notifyKeyspaceEvent(NOTIFY_ZSET,
             incr ? "zincr" : "zadd", key, c->db->id);
     }
 }
@@ -1443,13 +1443,13 @@ void zremCommand(client *c) {
             }
         }
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
 
     if (deleted) {
-        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,"zrem",key,c->db->id);
+        notifyKeyspaceEvent(NOTIFY_ZSET,"zrem",key,c->db->id);
         if (keyremoved)
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
+            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",key,c->db->id);
         signalModifiedKey(c->db,key);
         server.dirty += deleted;
     }
@@ -1542,16 +1542,16 @@ void zremrangeGenericCommand(client *c, int rangetype) {
             keyremoved = 1;
         }
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
 
     /* Step 4: Notifications and reply. */
     if (deleted) {
         char *event[3] = {"zremrangebyrank","zremrangebyscore","zremrangebylex"};
         signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,event[rangetype],key,c->db->id);
+        notifyKeyspaceEvent(NOTIFY_ZSET,event[rangetype],key,c->db->id);
         if (keyremoved)
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
+            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",key,c->db->id);
     }
     server.dirty += deleted;
     addReplyLongLong(c,deleted);
@@ -1645,7 +1645,7 @@ void zuiInitIterator(zsetopsrc *op) {
             it->ht.di = dictGetIterator(op->subject->ptr);
             it->ht.de = dictNext(it->ht.di);
         } else {
-            redisPanic("Unknown set encoding");
+            serverPanic("Unknown set encoding");
         }
     } else if (op->type == OBJ_ZSET) {
         iterzset *it = &op->iter.zset;
@@ -1660,10 +1660,10 @@ void zuiInitIterator(zsetopsrc *op) {
             it->sl.zs = op->subject->ptr;
             it->sl.node = it->sl.zs->zsl->header->level[0].forward;
         } else {
-            redisPanic("Unknown sorted set encoding");
+            serverPanic("Unknown sorted set encoding");
         }
     } else {
-        redisPanic("Unsupported type");
+        serverPanic("Unsupported type");
     }
 }
 
@@ -1674,23 +1674,23 @@ void zuiClearIterator(zsetopsrc *op) {
     if (op->type == OBJ_SET) {
         iterset *it = &op->iter.set;
         if (op->encoding == OBJ_ENCODING_INTSET) {
-            REDIS_NOTUSED(it); /* skip */
+            UNUSED(it); /* skip */
         } else if (op->encoding == OBJ_ENCODING_HT) {
             dictReleaseIterator(it->ht.di);
         } else {
-            redisPanic("Unknown set encoding");
+            serverPanic("Unknown set encoding");
         }
     } else if (op->type == OBJ_ZSET) {
         iterzset *it = &op->iter.zset;
         if (op->encoding == OBJ_ENCODING_ZIPLIST) {
-            REDIS_NOTUSED(it); /* skip */
+            UNUSED(it); /* skip */
         } else if (op->encoding == OBJ_ENCODING_SKIPLIST) {
-            REDIS_NOTUSED(it); /* skip */
+            UNUSED(it); /* skip */
         } else {
-            redisPanic("Unknown sorted set encoding");
+            serverPanic("Unknown sorted set encoding");
         }
     } else {
-        redisPanic("Unsupported type");
+        serverPanic("Unsupported type");
     }
 }
 
@@ -1705,7 +1705,7 @@ int zuiLength(zsetopsrc *op) {
             dict *ht = op->subject->ptr;
             return dictSize(ht);
         } else {
-            redisPanic("Unknown set encoding");
+            serverPanic("Unknown set encoding");
         }
     } else if (op->type == OBJ_ZSET) {
         if (op->encoding == OBJ_ENCODING_ZIPLIST) {
@@ -1714,10 +1714,10 @@ int zuiLength(zsetopsrc *op) {
             zset *zs = op->subject->ptr;
             return zs->zsl->length;
         } else {
-            redisPanic("Unknown sorted set encoding");
+            serverPanic("Unknown sorted set encoding");
         }
     } else {
-        redisPanic("Unsupported type");
+        serverPanic("Unsupported type");
     }
 }
 
@@ -1754,7 +1754,7 @@ int zuiNext(zsetopsrc *op, zsetopval *val) {
             /* Move to next element. */
             it->ht.de = dictNext(it->ht.di);
         } else {
-            redisPanic("Unknown set encoding");
+            serverPanic("Unknown set encoding");
         }
     } else if (op->type == OBJ_ZSET) {
         iterzset *it = &op->iter.zset;
@@ -1776,10 +1776,10 @@ int zuiNext(zsetopsrc *op, zsetopval *val) {
             /* Move to next element. */
             it->sl.node = it->sl.node->level[0].forward;
         } else {
-            redisPanic("Unknown sorted set encoding");
+            serverPanic("Unknown sorted set encoding");
         }
     } else {
-        redisPanic("Unsupported type");
+        serverPanic("Unsupported type");
     }
     return 1;
 }
@@ -1796,7 +1796,7 @@ int zuiLongLongFromValue(zsetopval *val) {
                 if (string2ll(val->ele->ptr,sdslen(val->ele->ptr),&val->ell))
                     val->flags |= OPVAL_VALID_LL;
             } else {
-                redisPanic("Unsupported element encoding");
+                serverPanic("Unsupported element encoding");
             }
         } else if (val->estr != NULL) {
             if (string2ll((char*)val->estr,val->elen,&val->ell))
@@ -1831,7 +1831,7 @@ int zuiBufferFromValue(zsetopval *val) {
                 val->elen = sdslen(val->ele->ptr);
                 val->estr = val->ele->ptr;
             } else {
-                redisPanic("Unsupported element encoding");
+                serverPanic("Unsupported element encoding");
             }
         } else {
             val->elen = ll2string((char*)val->_buf,sizeof(val->_buf),val->ell);
@@ -1867,7 +1867,7 @@ int zuiFind(zsetopsrc *op, zsetopval *val, double *score) {
                 return 0;
             }
         } else {
-            redisPanic("Unknown set encoding");
+            serverPanic("Unknown set encoding");
         }
     } else if (op->type == OBJ_ZSET) {
         zuiObjectFromValue(val);
@@ -1889,10 +1889,10 @@ int zuiFind(zsetopsrc *op, zsetopval *val, double *score) {
                 return 0;
             }
         } else {
-            redisPanic("Unknown sorted set encoding");
+            serverPanic("Unknown sorted set encoding");
         }
     } else {
-        redisPanic("Unsupported type");
+        serverPanic("Unsupported type");
     }
 }
 
@@ -1918,7 +1918,7 @@ inline static void zunionInterAggregate(double *target, double val, int aggregat
         *target = val > *target ? val : *target;
     } else {
         /* safety net */
-        redisPanic("Unknown ZUNION/INTER aggregate type");
+        serverPanic("Unknown ZUNION/INTER aggregate type");
     }
 }
 
@@ -2018,7 +2018,7 @@ void zunionInterGenericCommand(client *c, robj *dstkey, int op) {
     dstzset = dstobj->ptr;
     memset(&zval, 0, sizeof(zval));
 
-    if (op == REDIS_OP_INTER) {
+    if (op == SET_OP_INTER) {
         /* Skip everything if the smallest input is empty. */
         if (zuiLength(&src[0]) > 0) {
             /* Precondition: as src[0] is non-empty and the inputs are ordered
@@ -2060,7 +2060,7 @@ void zunionInterGenericCommand(client *c, robj *dstkey, int op) {
             }
             zuiClearIterator(&src[0]);
         }
-    } else if (op == REDIS_OP_UNION) {
+    } else if (op == SET_OP_UNION) {
         dict *accumulator = dictCreate(&setDictType,NULL);
         dictIterator *di;
         dictEntry *de;
@@ -2133,7 +2133,7 @@ void zunionInterGenericCommand(client *c, robj *dstkey, int op) {
         /* We can free the accumulator dictionary now. */
         dictRelease(accumulator);
     } else {
-        redisPanic("Unknown operator");
+        serverPanic("Unknown operator");
     }
 
     if (dbDelete(c->db,dstkey)) {
@@ -2150,25 +2150,25 @@ void zunionInterGenericCommand(client *c, robj *dstkey, int op) {
         dbAdd(c->db,dstkey,dstobj);
         addReplyLongLong(c,zsetLength(dstobj));
         if (!touched) signalModifiedKey(c->db,dstkey);
-        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,
-            (op == REDIS_OP_UNION) ? "zunionstore" : "zinterstore",
+        notifyKeyspaceEvent(NOTIFY_ZSET,
+            (op == SET_OP_UNION) ? "zunionstore" : "zinterstore",
             dstkey,c->db->id);
         server.dirty++;
     } else {
         decrRefCount(dstobj);
         addReply(c,shared.czero);
         if (touched)
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",dstkey,c->db->id);
+            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",dstkey,c->db->id);
     }
     zfree(src);
 }
 
 void zunionstoreCommand(client *c) {
-    zunionInterGenericCommand(c,c->argv[1], REDIS_OP_UNION);
+    zunionInterGenericCommand(c,c->argv[1], SET_OP_UNION);
 }
 
 void zinterstoreCommand(client *c) {
-    zunionInterGenericCommand(c,c->argv[1], REDIS_OP_INTER);
+    zunionInterGenericCommand(c,c->argv[1], SET_OP_INTER);
 }
 
 void zrangeGenericCommand(client *c, int reverse) {
@@ -2269,7 +2269,7 @@ void zrangeGenericCommand(client *c, int reverse) {
             ln = reverse ? ln->backward : ln->level[0].forward;
         }
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
 }
 
@@ -2458,7 +2458,7 @@ void genericZrangebyscoreCommand(client *c, int reverse) {
             }
         }
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
 
     if (withscores) {
@@ -2547,7 +2547,7 @@ void zcountCommand(client *c) {
             }
         }
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
 
     addReplyLongLong(c, count);
@@ -2625,7 +2625,7 @@ void zlexcountCommand(client *c) {
             }
         }
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
 
     zslFreeLexRange(&range);
@@ -2802,7 +2802,7 @@ void genericZrangebylexCommand(client *c, int reverse) {
             }
         }
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
 
     zslFreeLexRange(&range);
@@ -2900,7 +2900,7 @@ void zrankGenericCommand(client *c, int reverse) {
             addReply(c,shared.nullbulk);
         }
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
 }
 