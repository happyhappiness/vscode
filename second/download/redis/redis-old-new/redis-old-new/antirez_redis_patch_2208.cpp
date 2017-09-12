@@ -954,10 +954,24 @@ static int dictEncObjKeyCompare(void *privdata, const void *key1,
 static unsigned int dictEncObjHash(const void *key) {
     robj *o = (robj*) key;
 
-    o = getDecodedObject(o);
-    unsigned int hash = dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
-    decrRefCount(o);
-    return hash;
+    if (o->encoding == REDIS_ENCODING_RAW) {
+        return dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
+    } else {
+        if (o->encoding == REDIS_ENCODING_INT) {
+            char buf[32];
+            int len;
+
+            len = snprintf(buf,32,"%ld",(long)o->ptr);
+            return dictGenHashFunction((unsigned char*)buf, len);
+        } else {
+            unsigned int hash;
+
+            o = getDecodedObject(o);
+            hash = dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
+            decrRefCount(o);
+            return hash;
+        }
+    }
 }
 
 /* Sets type and expires */