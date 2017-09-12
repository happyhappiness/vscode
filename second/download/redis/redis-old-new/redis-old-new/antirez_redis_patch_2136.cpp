@@ -6470,16 +6470,16 @@ static redisSortOperation *createSortOperation(int type, robj *pattern) {
 /* Return the value associated to the key with a name obtained
  * substituting the first occurence of '*' in 'pattern' with 'subst' */
 static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
-    char *p;
+    char *p, *f;
     sds spat, ssub;
-    robj keyobj;
-    int prefixlen, sublen, postfixlen;
+    robj keyobj, fieldobj, *o;
+    int prefixlen, sublen, postfixlen, fieldlen;
     /* Expoit the internal sds representation to create a sds string allocated on the stack in order to make this function faster */
     struct {
         long len;
         long free;
         char buf[REDIS_SORTKEY_MAX+1];
-    } keyname;
+    } keyname, fieldname;
 
     /* If the pattern is "#" return the substitution object itself in order
      * to implement the "SORT ... GET #" feature. */
@@ -6501,20 +6501,40 @@ static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
         return NULL;
     }
 
+    /* Find out if we're dealing with a hash dereference. */
+    if ((f = strstr(p+1, "->")) != NULL) {
+        fieldlen = sdslen(spat)-(f-spat);
+        /* this also copies \0 character */
+        memcpy(fieldname.buf,f+2,fieldlen-1);
+        fieldname.len = fieldlen-2;
+    } else {
+        fieldlen = 0;
+    }
+
     prefixlen = p-spat;
     sublen = sdslen(ssub);
-    postfixlen = sdslen(spat)-(prefixlen+1);
+    postfixlen = sdslen(spat)-(prefixlen+1)-fieldlen;
     memcpy(keyname.buf,spat,prefixlen);
     memcpy(keyname.buf+prefixlen,ssub,sublen);
     memcpy(keyname.buf+prefixlen+sublen,p+1,postfixlen);
     keyname.buf[prefixlen+sublen+postfixlen] = '\0';
     keyname.len = prefixlen+sublen+postfixlen;
-
-    initStaticStringObject(keyobj,((char*)&keyname)+(sizeof(long)*2))
     decrRefCount(subst);
 
-    /* printf("lookup '%s' => %p\n", keyname.buf,de); */
-    return lookupKeyRead(db,&keyobj);
+    /* Lookup substituted key */
+    initStaticStringObject(keyobj,((char*)&keyname)+(sizeof(long)*2));
+    o = lookupKeyRead(db,&keyobj);
+
+    /* Retrieve value from hash by the field name */
+    if (o != NULL && fieldlen > 0) {
+        if (o->type != REDIS_HASH || fieldname.len < 1) {
+            return NULL;
+        }
+        initStaticStringObject(fieldobj,((char*)&fieldname)+(sizeof(long)*2));
+        o = hashGet(o, &fieldobj);
+    }
+
+    return o;
 }
 
 /* sortCompare() is used by qsort in sortCommand(). Given that qsort_r with
@@ -6683,36 +6703,37 @@ static void sortCommand(redisClient *c) {
     /* Now it's time to load the right scores in the sorting vector */
     if (dontsort == 0) {
         for (j = 0; j < vectorlen; j++) {
+            robj *byval;
             if (sortby) {
-                robj *byval;
-
+                /* lookup value to sort by */
                 byval = lookupKeyByPattern(c->db,sortby,vector[j].obj);
                 if (!byval || byval->type != REDIS_STRING) continue;
-                if (alpha) {
-                    vector[j].u.cmpobj = getDecodedObject(byval);
+            } else {
+                /* use object itself to sort by */
+                byval = vector[j].obj;
+            }
+
+            if (alpha) {
+                /* getDecodedObject increments refcount, so the corresponding
+                 * decrRefCount will clean up values coming from a zipmap. */
+                vector[j].u.cmpobj = getDecodedObject(byval);
+            } else {
+                if (byval->encoding == REDIS_ENCODING_RAW) {
+                    vector[j].u.score = strtod(byval->ptr,NULL);
                 } else {
-                    if (byval->encoding == REDIS_ENCODING_RAW) {
-                        vector[j].u.score = strtod(byval->ptr,NULL);
-                    } else {
-                        /* Don't need to decode the object if it's
-                         * integer-encoded (the only encoding supported) so
-                         * far. We can just cast it */
-                        if (byval->encoding == REDIS_ENCODING_INT) {
-                            vector[j].u.score = (long)byval->ptr;
-                        } else
-                            redisAssert(1 != 1);
-                    }
+                    /* Don't need to decode the object if it's
+                     * integer-encoded (the only encoding supported) so
+                     * far. We can just cast it */
+                    if (byval->encoding == REDIS_ENCODING_INT) {
+                        vector[j].u.score = (long)byval->ptr;
+                    } else
+                        redisAssert(1 != 1);
                 }
-            } else {
-                if (!alpha) {
-                    if (vector[j].obj->encoding == REDIS_ENCODING_RAW)
-                        vector[j].u.score = strtod(vector[j].obj->ptr,NULL);
-                    else {
-                        if (vector[j].obj->encoding == REDIS_ENCODING_INT)
-                            vector[j].u.score = (long) vector[j].obj->ptr;
-                        else
-                            redisAssert(1 != 1);
-                    }
+
+                /* clean up immediately if this value came from a zipmap */
+                if (byval->refcount == 0) {
+                    byval->refcount = 1;
+                    decrRefCount(byval);
                 }
             }
         }