@@ -2841,7 +2841,7 @@ static void freeHashObject(robj *o) {
         zfree(o->ptr);
         break;
     default:
-        redisAssert(0);
+        redisPanic("Unknown hash encoding type");
         break;
     }
 }
@@ -2881,7 +2881,7 @@ static void decrRefCount(void *obj) {
         case REDIS_SET: freeSetObject(o); break;
         case REDIS_ZSET: freeZsetObject(o); break;
         case REDIS_HASH: freeHashObject(o); break;
-        default: redisAssert(0); break;
+        default: redisPanic("Unknown object type"); break;
         }
         if (server.vm_enabled) pthread_mutex_lock(&server.obj_freelist_mutex);
         if (listLength(server.objfreelist) > REDIS_OBJFREELIST_MAX ||
@@ -3411,7 +3411,7 @@ static int rdbSaveObject(FILE *fp, robj *o) {
             dictReleaseIterator(di);
         }
     } else {
-        redisAssert(0);
+        redisPanic("Unknown object type");
     }
     return 0;
 }
@@ -3632,7 +3632,7 @@ static robj *rdbLoadIntegerObject(FILE *fp, int enctype) {
         val = (int32_t)v;
     } else {
         val = 0; /* anti-warning */
-        redisAssert(0);
+        redisPanic("Unknown RDB integer encoding type");
     }
     return createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",val));
 }
@@ -3671,7 +3671,7 @@ static robj *rdbLoadStringObject(FILE*fp) {
         case REDIS_RDB_ENC_LZF:
             return rdbLoadLzfStringObject(fp);
         default:
-            redisAssert(0);
+            redisPanic("Unknown RDB encoding type");
         }
     }
 
@@ -3793,7 +3793,7 @@ static robj *rdbLoadObject(int type, FILE *fp) {
             }
         }
     } else {
-        redisAssert(0);
+        redisPanic("Unknown object type");
     }
     return o;
 }
@@ -5607,7 +5607,7 @@ inline static void zunionInterAggregate(double *target, double val, int aggregat
         *target = val > *target ? val : *target;
     } else {
         /* safety net */
-        redisAssert(0 != 0);
+        redisPanic("Unknown ZUNION/INTER aggregate type");
     }
 }
 
@@ -6666,7 +6666,7 @@ static void sortCommand(redisClient *c) {
     case REDIS_LIST: vectorlen = listLength((list*)sortval->ptr); break;
     case REDIS_SET: vectorlen =  dictSize((dict*)sortval->ptr); break;
     case REDIS_ZSET: vectorlen = dictSize(((zset*)sortval->ptr)->dict); break;
-    default: vectorlen = 0; redisAssert(0); /* Avoid GCC warning */
+    default: vectorlen = 0; redisPanic("Bad SORT type"); /* Avoid GCC warning */
     }
     vector = zmalloc(sizeof(redisSortObject)*vectorlen);
     j = 0;
@@ -8215,7 +8215,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                     dictReleaseIterator(di);
                 }
             } else {
-                redisAssert(0);
+                redisPanic("Unknown object type");
             }
             /* Save the expire time */
             if (expiretime != -1) {