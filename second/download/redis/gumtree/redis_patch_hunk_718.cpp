         key = dictGetKey(de);
 
         if (val->type != OBJ_STRING || !sdsEncodedObject(val)) {
             addReplyError(c,"Not an sds encoded string.");
         } else {
             addReplyStatusFormat(c,
-                "key_sds_len:%lld, key_sds_avail:%lld, "
-                "val_sds_len:%lld, val_sds_avail:%lld",
+                "key_sds_len:%lld, key_sds_avail:%lld, key_zmalloc: %lld, "
+                "val_sds_len:%lld, val_sds_avail:%lld, val_zmalloc: %lld",
                 (long long) sdslen(key),
                 (long long) sdsavail(key),
+                (long long) sdsZmallocSize(key),
                 (long long) sdslen(val->ptr),
-                (long long) sdsavail(val->ptr));
+                (long long) sdsavail(val->ptr),
+                (long long) getStringObjectSdsUsedMemory(val));
+        }
+    } else if (!strcasecmp(c->argv[1]->ptr,"ziplist") && c->argc == 3) {
+        robj *o;
+
+        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nokeyerr))
+                == NULL) return;
+
+        if (o->encoding != OBJ_ENCODING_ZIPLIST) {
+            addReplyError(c,"Not an sds encoded string.");
+        } else {
+            ziplistRepr(o->ptr);
+            addReplyStatus(c,"Ziplist structure printed on stdout");
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"populate") &&
-               (c->argc == 3 || c->argc == 4)) {
+               c->argc >= 3 && c->argc <= 5) {
         long keys, j;
         robj *key, *val;
         char buf[128];
 
         if (getLongFromObjectOrReply(c, c->argv[2], &keys, NULL) != C_OK)
             return;
         dictExpand(c->db->dict,keys);
         for (j = 0; j < keys; j++) {
+            long valsize = 0;
             snprintf(buf,sizeof(buf),"%s:%lu",
                 (c->argc == 3) ? "key" : (char*)c->argv[3]->ptr, j);
             key = createStringObject(buf,strlen(buf));
+            if (c->argc == 5)
+                if (getLongFromObjectOrReply(c, c->argv[4], &valsize, NULL) != C_OK)
+                    return;
             if (lookupKeyWrite(c->db,key) != NULL) {
                 decrRefCount(key);
                 continue;
             }
             snprintf(buf,sizeof(buf),"value:%lu",j);
-            val = createStringObject(buf,strlen(buf));
+            if (valsize==0)
+                val = createStringObject(buf,strlen(buf));
+            else {
+                int buflen = strlen(buf);
+                val = createStringObject(NULL,valsize);
+                memcpy(val->ptr, buf, valsize<=buflen? valsize: buflen);
+            }
             dbAdd(c->db,key,val);
             signalModifiedKey(c->db,key);
             decrRefCount(key);
         }
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"digest") && c->argc == 2) {
