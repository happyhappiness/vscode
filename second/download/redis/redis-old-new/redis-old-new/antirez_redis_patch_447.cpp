@@ -80,7 +80,7 @@ int setTypeAdd(robj *subject, robj *value) {
             return 1;
         }
     } else {
-        redisPanic("Unknown set encoding");
+        serverPanic("Unknown set encoding");
     }
     return 0;
 }
@@ -99,7 +99,7 @@ int setTypeRemove(robj *setobj, robj *value) {
             if (success) return 1;
         }
     } else {
-        redisPanic("Unknown set encoding");
+        serverPanic("Unknown set encoding");
     }
     return 0;
 }
@@ -113,7 +113,7 @@ int setTypeIsMember(robj *subject, robj *value) {
             return intsetFind((intset*)subject->ptr,llval);
         }
     } else {
-        redisPanic("Unknown set encoding");
+        serverPanic("Unknown set encoding");
     }
     return 0;
 }
@@ -127,7 +127,7 @@ setTypeIterator *setTypeInitIterator(robj *subject) {
     } else if (si->encoding == OBJ_ENCODING_INTSET) {
         si->ii = 0;
     } else {
-        redisPanic("Unknown set encoding");
+        serverPanic("Unknown set encoding");
     }
     return si;
 }
@@ -164,7 +164,7 @@ int setTypeNext(setTypeIterator *si, robj **objele, int64_t *llele) {
             return -1;
         *objele = NULL; /* Not needed. Defensive. */
     } else {
-        redisPanic("Wrong set encoding in setTypeNext");
+        serverPanic("Wrong set encoding in setTypeNext");
     }
     return si->encoding;
 }
@@ -190,7 +190,7 @@ robj *setTypeNextObject(setTypeIterator *si) {
             incrRefCount(objele);
             return objele;
         default:
-            redisPanic("Unsupported encoding");
+            serverPanic("Unsupported encoding");
     }
     return NULL; /* just to suppress warnings */
 }
@@ -221,7 +221,7 @@ int setTypeRandomElement(robj *setobj, robj **objele, int64_t *llele) {
         *llele = intsetRandom(setobj->ptr);
         *objele = NULL; /* Not needed. Defensive. */
     } else {
-        redisPanic("Unknown set encoding");
+        serverPanic("Unknown set encoding");
     }
     return setobj->encoding;
 }
@@ -232,7 +232,7 @@ unsigned long setTypeSize(robj *subject) {
     } else if (subject->encoding == OBJ_ENCODING_INTSET) {
         return intsetLen((intset*)subject->ptr);
     } else {
-        redisPanic("Unknown set encoding");
+        serverPanic("Unknown set encoding");
     }
 }
 
@@ -265,7 +265,7 @@ void setTypeConvert(robj *setobj, int enc) {
         zfree(setobj->ptr);
         setobj->ptr = d;
     } else {
-        redisPanic("Unsupported set conversion");
+        serverPanic("Unsupported set conversion");
     }
 }
 
@@ -290,7 +290,7 @@ void saddCommand(client *c) {
     }
     if (added) {
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_SET,"sadd",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_SET,"sadd",c->argv[1],c->db->id);
     }
     server.dirty += added;
     addReplyLongLong(c,added);
@@ -315,9 +315,9 @@ void sremCommand(client *c) {
     }
     if (deleted) {
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_SET,"srem",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_SET,"srem",c->argv[1],c->db->id);
         if (keyremoved)
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],
+            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],
                                 c->db->id);
         server.dirty += deleted;
     }
@@ -352,12 +352,12 @@ void smoveCommand(client *c) {
         addReply(c,shared.czero);
         return;
     }
-    notifyKeyspaceEvent(REDIS_NOTIFY_SET,"srem",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_SET,"srem",c->argv[1],c->db->id);
 
     /* Remove the src set from the database when empty */
     if (setTypeSize(srcset) == 0) {
         dbDelete(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
     }
     signalModifiedKey(c->db,c->argv[1]);
     signalModifiedKey(c->db,c->argv[2]);
@@ -372,7 +372,7 @@ void smoveCommand(client *c) {
     /* An extra key has changed when ele was successfully added to dstset */
     if (setTypeAdd(dstset,ele)) {
         server.dirty++;
-        notifyKeyspaceEvent(REDIS_NOTIFY_SET,"sadd",c->argv[2],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_SET,"sadd",c->argv[2],c->db->id);
     }
     addReply(c,shared.cone);
 }
@@ -436,19 +436,19 @@ void spopWithCountCommand(client *c) {
     size = setTypeSize(set);
 
     /* Generate an SPOP keyspace notification */
-    notifyKeyspaceEvent(REDIS_NOTIFY_SET,"spop",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_SET,"spop",c->argv[1],c->db->id);
     server.dirty += count;
 
     /* CASE 1:
      * The number of requested elements is greater than or equal to
      * the number of elements inside the set: simply return the whole set. */
     if (count >= size) {
         /* We just return the entire set */
-        sunionDiffGenericCommand(c,c->argv+1,1,NULL,REDIS_OP_UNION);
+        sunionDiffGenericCommand(c,c->argv+1,1,NULL,SET_OP_UNION);
 
         /* Delete the set as it is now empty */
         dbDelete(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
 
         /* Propagate this command as an DEL operation */
         rewriteClientCommandVector(c,2,shared.del,c->argv[1]);
@@ -494,7 +494,7 @@ void spopWithCountCommand(client *c) {
             /* Replicate/AOF this command as an SREM operation */
             propargv[2] = objele;
             alsoPropagate(server.sremCommand,c->db->id,propargv,3,
-                REDIS_PROPAGATE_AOF|REDIS_PROPAGATE_REPL);
+                PROPAGATE_AOF|PROPAGATE_REPL);
             decrRefCount(objele);
         }
     } else {
@@ -540,7 +540,7 @@ void spopWithCountCommand(client *c) {
             /* Replicate/AOF this command as an SREM operation */
             propargv[2] = objele;
             alsoPropagate(server.sremCommand,c->db->id,propargv,3,
-                REDIS_PROPAGATE_AOF|REDIS_PROPAGATE_REPL);
+                PROPAGATE_AOF|PROPAGATE_REPL);
 
             decrRefCount(objele);
         }
@@ -586,7 +586,7 @@ void spopCommand(client *c) {
         setTypeRemove(set,ele);
     }
 
-    notifyKeyspaceEvent(REDIS_NOTIFY_SET,"spop",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_SET,"spop",c->argv[1],c->db->id);
 
     /* Replicate/AOF this command as an SREM operation */
     aux = createStringObject("SREM",4);
@@ -600,7 +600,7 @@ void spopCommand(client *c) {
     /* Delete the set if it's empty */
     if (setTypeSize(set) == 0) {
         dbDelete(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
     }
 
     /* Set has been modified */
@@ -667,7 +667,7 @@ void srandmemberWithCountCommand(client *c) {
      * The number of requested elements is greater than the number of
      * elements inside the set: simply return the whole set. */
     if (count >= size) {
-        sunionDiffGenericCommand(c,c->argv+1,1,NULL,REDIS_OP_UNION);
+        sunionDiffGenericCommand(c,c->argv+1,1,NULL,SET_OP_UNION);
         return;
     }
 
@@ -904,13 +904,13 @@ void sinterGenericCommand(client *c, robj **setkeys,
         if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,setTypeSize(dstset));
-            notifyKeyspaceEvent(REDIS_NOTIFY_SET,"sinterstore",
+            notifyKeyspaceEvent(NOTIFY_SET,"sinterstore",
                 dstkey,c->db->id);
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
             if (deleted)
-                notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+                notifyKeyspaceEvent(NOTIFY_GENERIC,"del",
                     dstkey,c->db->id);
         }
         signalModifiedKey(c->db,dstkey);
@@ -929,9 +929,9 @@ void sinterstoreCommand(client *c) {
     sinterGenericCommand(c,c->argv+2,c->argc-2,c->argv[1]);
 }
 
-#define REDIS_OP_UNION 0
-#define REDIS_OP_DIFF 1
-#define REDIS_OP_INTER 2
+#define SET_OP_UNION 0
+#define SET_OP_DIFF 1
+#define SET_OP_INTER 2
 
 void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
                               robj *dstkey, int op) {
@@ -965,7 +965,7 @@ void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
      * the sets.
      *
      * We compute what is the best bet with the current input here. */
-    if (op == REDIS_OP_DIFF && sets[0]) {
+    if (op == SET_OP_DIFF && sets[0]) {
         long long algo_one_work = 0, algo_two_work = 0;
 
         for (j = 0; j < setnum; j++) {
@@ -994,7 +994,7 @@ void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
      * this set object will be the resulting object to set into the target key*/
     dstset = createIntsetObject();
 
-    if (op == REDIS_OP_UNION) {
+    if (op == SET_OP_UNION) {
         /* Union is trivial, just add every element of every set to the
          * temporary set. */
         for (j = 0; j < setnum; j++) {
@@ -1007,7 +1007,7 @@ void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
             }
             setTypeReleaseIterator(si);
         }
-    } else if (op == REDIS_OP_DIFF && sets[0] && diff_algo == 1) {
+    } else if (op == SET_OP_DIFF && sets[0] && diff_algo == 1) {
         /* DIFF Algorithm 1:
          *
          * We perform the diff by iterating all the elements of the first set,
@@ -1031,7 +1031,7 @@ void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
             decrRefCount(ele);
         }
         setTypeReleaseIterator(si);
-    } else if (op == REDIS_OP_DIFF && sets[0] && diff_algo == 2) {
+    } else if (op == SET_OP_DIFF && sets[0] && diff_algo == 2) {
         /* DIFF Algorithm 2:
          *
          * Add all the elements of the first set to the auxiliary set.
@@ -1076,14 +1076,14 @@ void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
         if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,setTypeSize(dstset));
-            notifyKeyspaceEvent(REDIS_NOTIFY_SET,
-                op == REDIS_OP_UNION ? "sunionstore" : "sdiffstore",
+            notifyKeyspaceEvent(NOTIFY_SET,
+                op == SET_OP_UNION ? "sunionstore" : "sdiffstore",
                 dstkey,c->db->id);
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
             if (deleted)
-                notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+                notifyKeyspaceEvent(NOTIFY_GENERIC,"del",
                     dstkey,c->db->id);
         }
         signalModifiedKey(c->db,dstkey);
@@ -1093,19 +1093,19 @@ void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
 }
 
 void sunionCommand(client *c) {
-    sunionDiffGenericCommand(c,c->argv+1,c->argc-1,NULL,REDIS_OP_UNION);
+    sunionDiffGenericCommand(c,c->argv+1,c->argc-1,NULL,SET_OP_UNION);
 }
 
 void sunionstoreCommand(client *c) {
-    sunionDiffGenericCommand(c,c->argv+2,c->argc-2,c->argv[1],REDIS_OP_UNION);
+    sunionDiffGenericCommand(c,c->argv+2,c->argc-2,c->argv[1],SET_OP_UNION);
 }
 
 void sdiffCommand(client *c) {
-    sunionDiffGenericCommand(c,c->argv+1,c->argc-1,NULL,REDIS_OP_DIFF);
+    sunionDiffGenericCommand(c,c->argv+1,c->argc-1,NULL,SET_OP_DIFF);
 }
 
 void sdiffstoreCommand(client *c) {
-    sunionDiffGenericCommand(c,c->argv+2,c->argc-2,c->argv[1],REDIS_OP_DIFF);
+    sunionDiffGenericCommand(c,c->argv+2,c->argc-2,c->argv[1],SET_OP_DIFF);
 }
 
 void sscanCommand(client *c) {