@@ -545,10 +545,12 @@ void hincrbyCommand(client *c) {
     server.dirty++;
 }
 
+/* XXX From here. */
+
 void hincrbyfloatCommand(client *c) {
     double value, incr;
     long long ll;
-    robj *o, *doubleobj;
+    robj *o;
     sds new;
     unsigned char *vstr;
     unsigned int *lven;
@@ -569,22 +571,26 @@ void hincrbyfloatCommand(client *c) {
     }
 
     value += incr;
-    doubleobj = createStringObjectFromLongDouble(value,1);
-    decrRefCount(doubleobj);
+
+    char buf[256];
+    int len = ld2string(buf,sizeof(buf),value,humanfriendly);
+    new = sdsnewlen(buf,len);
     hashTypeSet(o,c->argv[2],new);
-    addReplyBulk(c,new);
+    addReplyBulkSds(c,new);
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
     rewriteClientCommandArgument(c,3,new);
-    decrRefCount(new);
+    decrRefCount(newobj);
 }
 
 static void addHashFieldToReply(client *c, robj *o, robj *field) {