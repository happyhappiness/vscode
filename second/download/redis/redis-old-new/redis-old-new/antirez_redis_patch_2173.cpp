@@ -5870,14 +5870,18 @@ static void hgetCommand(redisClient *c) {
         unsigned char *zm = o->ptr;
         unsigned char *val;
         unsigned int vlen;
+        robj *field;
 
-        if (zipmapGet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr), &val,&vlen)) {
+        field = getDecodedObject(c->argv[2]);
+        if (zipmapGet(zm,field->ptr,sdslen(field->ptr), &val,&vlen)) {
             addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
             addReplySds(c,sdsnewlen(val,vlen));
             addReply(c,shared.crlf);
+            decrRefCount(field);
             return;
         } else {
             addReply(c,shared.nullbulk);
+            decrRefCount(field);
             return;
         }
     } else {