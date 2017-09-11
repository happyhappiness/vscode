@@ -232,10 +232,10 @@ void setbitCommand(client *c) {
     byte = bitoffset >> 3;
     o = lookupKeyWrite(c->db,c->argv[1]);
     if (o == NULL) {
-        o = createObject(REDIS_STRING,sdsnewlen(NULL, byte+1));
+        o = createObject(OBJ_STRING,sdsnewlen(NULL, byte+1));
         dbAdd(c->db,c->argv[1],o);
     } else {
-        if (checkType(c,o,REDIS_STRING)) return;
+        if (checkType(c,o,OBJ_STRING)) return;
         o = dbUnshareStringValue(c->db,c->argv[1],o);
         o->ptr = sdsgrowzero(o->ptr,byte+1);
     }
@@ -267,7 +267,7 @@ void getbitCommand(client *c) {
         return;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,o,REDIS_STRING)) return;
+        checkType(c,o,OBJ_STRING)) return;
 
     byte = bitoffset >> 3;
     bit = 7 - (bitoffset & 0x7);
@@ -330,7 +330,7 @@ void bitopCommand(client *c) {
             continue;
         }
         /* Return an error if one of the keys is not a string. */
-        if (checkType(c,o,REDIS_STRING)) {
+        if (checkType(c,o,OBJ_STRING)) {
             unsigned long i;
             for (i = 0; i < j; i++) {
                 if (objects[i])
@@ -444,7 +444,7 @@ void bitopCommand(client *c) {
 
     /* Store the computed value into the target key */
     if (maxlen) {
-        o = createObject(REDIS_STRING,res);
+        o = createObject(OBJ_STRING,res);
         setKey(c->db,targetkey,o);
         notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",targetkey,c->db->id);
         decrRefCount(o);
@@ -465,11 +465,11 @@ void bitcountCommand(client *c) {
 
     /* Lookup, check for type, and return 0 for non existing keys. */
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,o,REDIS_STRING)) return;
+        checkType(c,o,OBJ_STRING)) return;
 
     /* Set the 'p' pointer to the string, that can be just a stack allocated
      * array if our string was integer encoded. */
-    if (o->encoding == REDIS_ENCODING_INT) {
+    if (o->encoding == OBJ_ENCODING_INT) {
         p = (unsigned char*) llbuf;
         strlen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
     } else {
@@ -534,11 +534,11 @@ void bitposCommand(client *c) {
         addReplyLongLong(c, bit ? -1 : 0);
         return;
     }
-    if (checkType(c,o,REDIS_STRING)) return;
+    if (checkType(c,o,OBJ_STRING)) return;
 
     /* Set the 'p' pointer to the string, that can be just a stack allocated
      * array if our string was integer encoded. */
-    if (o->encoding == REDIS_ENCODING_INT) {
+    if (o->encoding == OBJ_ENCODING_INT) {
         p = (unsigned char*) llbuf;
         strlen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
     } else {