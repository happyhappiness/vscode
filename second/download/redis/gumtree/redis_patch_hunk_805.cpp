 }
 
 /*-----------------------------------------------------------------------------
  * Hash type commands
  *----------------------------------------------------------------------------*/
 
-void hsetCommand(client *c) {
-    int update;
-    robj *o;
-
-    if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
-    hashTypeTryConversion(o,c->argv,2,3);
-    hashTypeTryObjectEncoding(o,&c->argv[2], &c->argv[3]);
-    update = hashTypeSet(o,c->argv[2],c->argv[3]);
-    addReply(c, update ? shared.czero : shared.cone);
-    signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(NOTIFY_HASH,"hset",c->argv[1],c->db->id);
-    server.dirty++;
-}
-
 void hsetnxCommand(client *c) {
     robj *o;
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     hashTypeTryConversion(o,c->argv,2,3);
 
-    if (hashTypeExists(o, c->argv[2])) {
+    if (hashTypeExists(o, c->argv[2]->ptr)) {
         addReply(c, shared.czero);
     } else {
-        hashTypeTryObjectEncoding(o,&c->argv[2], &c->argv[3]);
-        hashTypeSet(o,c->argv[2],c->argv[3]);
+        hashTypeSet(o,c->argv[2]->ptr,c->argv[3]->ptr,HASH_SET_COPY);
         addReply(c, shared.cone);
         signalModifiedKey(c->db,c->argv[1]);
         notifyKeyspaceEvent(NOTIFY_HASH,"hset",c->argv[1],c->db->id);
         server.dirty++;
     }
 }
 
-void hmsetCommand(client *c) {
-    int i;
+void hsetCommand(client *c) {
+    int i, created = 0;
     robj *o;
 
     if ((c->argc % 2) == 1) {
         addReplyError(c,"wrong number of arguments for HMSET");
         return;
     }
 
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     hashTypeTryConversion(o,c->argv,2,c->argc-1);
-    for (i = 2; i < c->argc; i += 2) {
-        hashTypeTryObjectEncoding(o,&c->argv[i], &c->argv[i+1]);
-        hashTypeSet(o,c->argv[i],c->argv[i+1]);
+
+    for (i = 2; i < c->argc; i += 2)
+        created += !hashTypeSet(o,c->argv[i]->ptr,c->argv[i+1]->ptr,HASH_SET_COPY);
+
+    /* HMSET (deprecated) and HSET return value is different. */
+    char *cmdname = c->argv[0]->ptr;
+    if (cmdname[1] == 's' || cmdname[1] == 'S') {
+        /* HSET */
+        addReplyLongLong(c, created);
+    } else {
+        /* HMSET */
+        addReply(c, shared.ok);
     }
-    addReply(c, shared.ok);
     signalModifiedKey(c->db,c->argv[1]);
     notifyKeyspaceEvent(NOTIFY_HASH,"hset",c->argv[1],c->db->id);
     server.dirty++;
 }
 
 void hincrbyCommand(client *c) {
     long long value, incr, oldvalue;
-    robj *o, *current, *new;
+    robj *o;
+    sds new;
+    unsigned char *vstr;
+    unsigned int vlen;
 
     if (getLongLongFromObjectOrReply(c,c->argv[3],&incr,NULL) != C_OK) return;
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
-    if ((current = hashTypeGetObject(o,c->argv[2])) != NULL) {
-        if (getLongLongFromObjectOrReply(c,current,&value,
-            "hash value is not an integer") != C_OK) {
-            decrRefCount(current);
-            return;
-        }
-        decrRefCount(current);
+    if (hashTypeGetValue(o,c->argv[2]->ptr,&vstr,&vlen,&value) == C_OK) {
+        if (vstr) {
+            if (string2ll((char*)vstr,vlen,&value) == 0) {
+                addReplyError(c,"hash value is not an integer");
+                return;
+            }
+        } /* Else hashTypeGetValue() already stored it into &value */
     } else {
         value = 0;
     }
 
     oldvalue = value;
     if ((incr < 0 && oldvalue < 0 && incr < (LLONG_MIN-oldvalue)) ||
         (incr > 0 && oldvalue > 0 && incr > (LLONG_MAX-oldvalue))) {
         addReplyError(c,"increment or decrement would overflow");
         return;
     }
     value += incr;
-    new = createStringObjectFromLongLong(value);
-    hashTypeTryObjectEncoding(o,&c->argv[2],NULL);
-    hashTypeSet(o,c->argv[2],new);
-    decrRefCount(new);
+    new = sdsfromlonglong(value);
+    hashTypeSet(o,c->argv[2]->ptr,new,HASH_SET_TAKE_VALUE);
     addReplyLongLong(c,value);
     signalModifiedKey(c->db,c->argv[1]);
     notifyKeyspaceEvent(NOTIFY_HASH,"hincrby",c->argv[1],c->db->id);
     server.dirty++;
 }
 
 void hincrbyfloatCommand(client *c) {
-    double long value, incr;
-    robj *o, *current, *new, *aux;
+    long double value, incr;
+    long long ll;
+    robj *o;
+    sds new;
+    unsigned char *vstr;
+    unsigned int vlen;
 
     if (getLongDoubleFromObjectOrReply(c,c->argv[3],&incr,NULL) != C_OK) return;
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
-    if ((current = hashTypeGetObject(o,c->argv[2])) != NULL) {
-        if (getLongDoubleFromObjectOrReply(c,current,&value,
-            "hash value is not a valid float") != C_OK) {
-            decrRefCount(current);
-            return;
+    if (hashTypeGetValue(o,c->argv[2]->ptr,&vstr,&vlen,&ll) == C_OK) {
+        if (vstr) {
+            if (string2ld((char*)vstr,vlen,&value) == 0) {
+                addReplyError(c,"hash value is not a float");
+                return;
+            }
+        } else {
+            value = (long double)ll;
         }
-        decrRefCount(current);
     } else {
         value = 0;
     }
 
     value += incr;
-    new = createStringObjectFromLongDouble(value,1);
-    hashTypeTryObjectEncoding(o,&c->argv[2],NULL);
-    hashTypeSet(o,c->argv[2],new);
-    addReplyBulk(c,new);
+
+    char buf[256];
+    int len = ld2string(buf,sizeof(buf),value,1);
+    new = sdsnewlen(buf,len);
+    hashTypeSet(o,c->argv[2]->ptr,new,HASH_SET_TAKE_VALUE);
+    addReplyBulkCBuffer(c,buf,len);
     signalModifiedKey(c->db,c->argv[1]);
     notifyKeyspaceEvent(NOTIFY_HASH,"hincrbyfloat",c->argv[1],c->db->id);
     server.dirty++;
 
     /* Always replicate HINCRBYFLOAT as an HSET command with the final value
      * in order to make sure that differences in float pricision or formatting
      * will not create differences in replicas or after an AOF restart. */
+    robj *aux, *newobj;
     aux = createStringObject("HSET",4);
+    newobj = createRawStringObject(buf,len);
     rewriteClientCommandArgument(c,0,aux);
     decrRefCount(aux);
-    rewriteClientCommandArgument(c,3,new);
-    decrRefCount(new);
+    rewriteClientCommandArgument(c,3,newobj);
+    decrRefCount(newobj);
 }
 
-static void addHashFieldToReply(client *c, robj *o, robj *field) {
+static void addHashFieldToReply(client *c, robj *o, sds field) {
     int ret;
 
     if (o == NULL) {
         addReply(c, shared.nullbulk);
         return;
     }
