 
 /* Equal string objects return 1 if the two objects are the same from the
  * point of view of a string comparison, otherwise 0 is returned. Note that
  * this function is faster then checking for (compareStringObject(a,b) == 0)
  * because it can perform some more optimization. */
 int equalStringObjects(robj *a, robj *b) {
-    if (a->encoding == REDIS_ENCODING_INT &&
-        b->encoding == REDIS_ENCODING_INT){
+    if (a->encoding == OBJ_ENCODING_INT &&
+        b->encoding == OBJ_ENCODING_INT){
         /* If both strings are integer encoded just check if the stored
          * long is the same. */
         return a->ptr == b->ptr;
     } else {
         return compareStringObjects(a,b) == 0;
     }
 }
 
 size_t stringObjectLen(robj *o) {
-    redisAssertWithInfo(NULL,o,o->type == REDIS_STRING);
+    serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
     if (sdsEncodedObject(o)) {
         return sdslen(o->ptr);
     } else {
-        char buf[32];
-
-        return ll2string(buf,32,(long)o->ptr);
+        return sdigits10((long)o->ptr);
     }
 }
 
 int getDoubleFromObject(robj *o, double *target) {
     double value;
     char *eptr;
 
     if (o == NULL) {
         value = 0;
     } else {
-        redisAssertWithInfo(NULL,o,o->type == REDIS_STRING);
+        serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
         if (sdsEncodedObject(o)) {
             errno = 0;
             value = strtod(o->ptr, &eptr);
             if (isspace(((char*)o->ptr)[0]) ||
                 eptr[0] != '\0' ||
                 (errno == ERANGE &&
                     (value == HUGE_VAL || value == -HUGE_VAL || value == 0)) ||
                 errno == EINVAL ||
                 isnan(value))
-                return REDIS_ERR;
-        } else if (o->encoding == REDIS_ENCODING_INT) {
+                return C_ERR;
+        } else if (o->encoding == OBJ_ENCODING_INT) {
             value = (long)o->ptr;
         } else {
-            redisPanic("Unknown string encoding");
+            serverPanic("Unknown string encoding");
         }
     }
     *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
-int getDoubleFromObjectOrReply(redisClient *c, robj *o, double *target, const char *msg) {
+int getDoubleFromObjectOrReply(client *c, robj *o, double *target, const char *msg) {
     double value;
-    if (getDoubleFromObject(o, &value) != REDIS_OK) {
+    if (getDoubleFromObject(o, &value) != C_OK) {
         if (msg != NULL) {
             addReplyError(c,(char*)msg);
         } else {
             addReplyError(c,"value is not a valid float");
         }
-        return REDIS_ERR;
+        return C_ERR;
     }
     *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
 int getLongDoubleFromObject(robj *o, long double *target) {
     long double value;
     char *eptr;
 
     if (o == NULL) {
         value = 0;
     } else {
-        redisAssertWithInfo(NULL,o,o->type == REDIS_STRING);
+        serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
         if (sdsEncodedObject(o)) {
             errno = 0;
             value = strtold(o->ptr, &eptr);
             if (isspace(((char*)o->ptr)[0]) || eptr[0] != '\0' ||
                 errno == ERANGE || isnan(value))
-                return REDIS_ERR;
-        } else if (o->encoding == REDIS_ENCODING_INT) {
+                return C_ERR;
+        } else if (o->encoding == OBJ_ENCODING_INT) {
             value = (long)o->ptr;
         } else {
-            redisPanic("Unknown string encoding");
+            serverPanic("Unknown string encoding");
         }
     }
     *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
-int getLongDoubleFromObjectOrReply(redisClient *c, robj *o, long double *target, const char *msg) {
+int getLongDoubleFromObjectOrReply(client *c, robj *o, long double *target, const char *msg) {
     long double value;
-    if (getLongDoubleFromObject(o, &value) != REDIS_OK) {
+    if (getLongDoubleFromObject(o, &value) != C_OK) {
         if (msg != NULL) {
             addReplyError(c,(char*)msg);
         } else {
             addReplyError(c,"value is not a valid float");
         }
-        return REDIS_ERR;
+        return C_ERR;
     }
     *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
 int getLongLongFromObject(robj *o, long long *target) {
     long long value;
     char *eptr;
 
     if (o == NULL) {
         value = 0;
     } else {
-        redisAssertWithInfo(NULL,o,o->type == REDIS_STRING);
+        serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
         if (sdsEncodedObject(o)) {
             errno = 0;
             value = strtoll(o->ptr, &eptr, 10);
             if (isspace(((char*)o->ptr)[0]) || eptr[0] != '\0' ||
                 errno == ERANGE)
-                return REDIS_ERR;
-        } else if (o->encoding == REDIS_ENCODING_INT) {
+                return C_ERR;
+        } else if (o->encoding == OBJ_ENCODING_INT) {
             value = (long)o->ptr;
         } else {
-            redisPanic("Unknown string encoding");
+            serverPanic("Unknown string encoding");
         }
     }
     if (target) *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
-int getLongLongFromObjectOrReply(redisClient *c, robj *o, long long *target, const char *msg) {
+int getLongLongFromObjectOrReply(client *c, robj *o, long long *target, const char *msg) {
     long long value;
-    if (getLongLongFromObject(o, &value) != REDIS_OK) {
+    if (getLongLongFromObject(o, &value) != C_OK) {
         if (msg != NULL) {
             addReplyError(c,(char*)msg);
         } else {
             addReplyError(c,"value is not an integer or out of range");
         }
-        return REDIS_ERR;
+        return C_ERR;
     }
     *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
-int getLongFromObjectOrReply(redisClient *c, robj *o, long *target, const char *msg) {
+int getLongFromObjectOrReply(client *c, robj *o, long *target, const char *msg) {
     long long value;
 
-    if (getLongLongFromObjectOrReply(c, o, &value, msg) != REDIS_OK) return REDIS_ERR;
+    if (getLongLongFromObjectOrReply(c, o, &value, msg) != C_OK) return C_ERR;
     if (value < LONG_MIN || value > LONG_MAX) {
         if (msg != NULL) {
             addReplyError(c,(char*)msg);
         } else {
             addReplyError(c,"value is out of range");
         }
-        return REDIS_ERR;
+        return C_ERR;
     }
     *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
 char *strEncoding(int encoding) {
     switch(encoding) {
-    case REDIS_ENCODING_RAW: return "raw";
-    case REDIS_ENCODING_INT: return "int";
-    case REDIS_ENCODING_HT: return "hashtable";
-    case REDIS_ENCODING_LINKEDLIST: return "linkedlist";
-    case REDIS_ENCODING_ZIPLIST: return "ziplist";
-    case REDIS_ENCODING_INTSET: return "intset";
-    case REDIS_ENCODING_SKIPLIST: return "skiplist";
-    case REDIS_ENCODING_EMBSTR: return "embstr";
+    case OBJ_ENCODING_RAW: return "raw";
+    case OBJ_ENCODING_INT: return "int";
+    case OBJ_ENCODING_HT: return "hashtable";
+    case OBJ_ENCODING_QUICKLIST: return "quicklist";
+    case OBJ_ENCODING_ZIPLIST: return "ziplist";
+    case OBJ_ENCODING_INTSET: return "intset";
+    case OBJ_ENCODING_SKIPLIST: return "skiplist";
+    case OBJ_ENCODING_EMBSTR: return "embstr";
     default: return "unknown";
     }
 }
 
 /* Given an object returns the min number of milliseconds the object was never
  * requested, using an approximated LRU algorithm. */
 unsigned long long estimateObjectIdleTime(robj *o) {
     unsigned long long lruclock = LRU_CLOCK();
     if (lruclock >= o->lru) {
-        return (lruclock - o->lru) * REDIS_LRU_CLOCK_RESOLUTION;
+        return (lruclock - o->lru) * LRU_CLOCK_RESOLUTION;
     } else {
-        return (lruclock + (REDIS_LRU_CLOCK_MAX - o->lru)) *
-                    REDIS_LRU_CLOCK_RESOLUTION;
+        return (lruclock + (LRU_CLOCK_MAX - o->lru)) *
+                    LRU_CLOCK_RESOLUTION;
     }
 }
 
 /* This is a helper function for the OBJECT command. We need to lookup keys
  * without any modification of LRU or other parameters. */
-robj *objectCommandLookup(redisClient *c, robj *key) {
+robj *objectCommandLookup(client *c, robj *key) {
     dictEntry *de;
 
     if ((de = dictFind(c->db->dict,key->ptr)) == NULL) return NULL;
     return (robj*) dictGetVal(de);
 }
 
-robj *objectCommandLookupOrReply(redisClient *c, robj *key, robj *reply) {
+robj *objectCommandLookupOrReply(client *c, robj *key, robj *reply) {
     robj *o = objectCommandLookup(c,key);
 
     if (!o) addReply(c, reply);
     return o;
 }
 
 /* Object command allows to inspect the internals of an Redis Object.
  * Usage: OBJECT <refcount|encoding|idletime> <key> */
-void objectCommand(redisClient *c) {
+void objectCommand(client *c) {
     robj *o;
 
     if (!strcasecmp(c->argv[1]->ptr,"refcount") && c->argc == 3) {
         if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
                 == NULL) return;
         addReplyLongLong(c,o->refcount);
