@@ -198,6 +198,10 @@
 #define APPENDFSYNC_ALWAYS 1
 #define APPENDFSYNC_EVERYSEC 2
 
+/* We can print the stacktrace, so our assert is defined this way: */
+#define redisAssert(_e) ((_e)?(void)0 : (_redisAssert(#_e),exit(1)))
+static void _redisAssert(char *estr);
+
 /*================================= Data types ============================== */
 
 /* A redis object, that is a type able to hold a string / list / set */
@@ -209,6 +213,17 @@ typedef struct redisObject {
     int refcount;
 } robj;
 
+/* Macro used to initalize a Redis object allocated on the stack.
+ * Note that this macro is taken near the structure definition to make sure
+ * we'll update it when the structure is changed, to avoid bugs like
+ * bug #85 introduced exactly in this way. */
+#define initStaticStringObject(_var,_ptr) do { \
+    _var.refcount = 1; \
+    _var.type = REDIS_STRING; \
+    _var.encoding = REDIS_ENCODING_RAW; \
+    _var.ptr = _ptr; \
+} while(0);
+
 typedef struct redisDb {
     dict *dict;
     dict *expires;
@@ -1397,14 +1412,14 @@ static void freeClient(redisClient *c) {
     freeClientArgv(c);
     close(c->fd);
     ln = listSearchKey(server.clients,c);
-    assert(ln != NULL);
+    redisAssert(ln != NULL);
     listDelNode(server.clients,ln);
     if (c->flags & REDIS_SLAVE) {
         if (c->replstate == REDIS_REPL_SEND_BULK && c->repldbfd != -1)
             close(c->repldbfd);
         list *l = (c->flags & REDIS_MONITOR) ? server.monitors : server.slaves;
         ln = listSearchKey(l,c);
-        assert(ln != NULL);
+        redisAssert(ln != NULL);
         listDelNode(l,ln);
     }
     if (c->flags & REDIS_MASTER) {
@@ -2155,7 +2170,7 @@ static void decrRefCount(void *obj) {
         case REDIS_SET: freeSetObject(o); break;
         case REDIS_ZSET: freeZsetObject(o); break;
         case REDIS_HASH: freeHashObject(o); break;
-        default: assert(0 != 0); break;
+        default: redisAssert(0 != 0); break;
         }
         if (listLength(server.objfreelist) > REDIS_OBJFREELIST_MAX ||
             !listAddNodeHead(server.objfreelist,o))
@@ -2200,7 +2215,7 @@ static robj *tryObjectSharing(robj *o) {
 
     if (o == NULL || server.shareobjects == 0) return o;
 
-    assert(o->type == REDIS_STRING);
+    redisAssert(o->type == REDIS_STRING);
     de = dictFind(server.sharingpool,o);
     if (de) {
         robj *shared = dictGetEntryKey(de);
@@ -2218,7 +2233,7 @@ static robj *tryObjectSharing(robj *o) {
         if (dictSize(server.sharingpool) >=
                 server.sharingpoolsize) {
             de = dictGetRandomKey(server.sharingpool);
-            assert(de != NULL);
+            redisAssert(de != NULL);
             c = ((unsigned long) dictGetEntryVal(de))-1;
             dictGetEntryVal(de) = (void*) c;
             if (c == 0) {
@@ -2231,7 +2246,7 @@ static robj *tryObjectSharing(robj *o) {
             int retval;
 
             retval = dictAdd(server.sharingpool,o,(void*)1);
-            assert(retval == DICT_OK);
+            redisAssert(retval == DICT_OK);
             incrRefCount(o);
         }
         return o;
@@ -2274,7 +2289,7 @@ static int tryObjectEncoding(robj *o) {
      if (o->refcount > 1) return REDIS_ERR;
 
     /* Currently we try to encode only strings */
-    assert(o->type == REDIS_STRING);
+    redisAssert(o->type == REDIS_STRING);
 
     /* Check if we can represent this string as a long integer */
     if (isStringRepresentableAsLong(s,&value) == REDIS_ERR) return REDIS_ERR;
@@ -2302,7 +2317,7 @@ static robj *getDecodedObject(robj *o) {
         dec = createStringObject(buf,strlen(buf));
         return dec;
     } else {
-        assert(1 != 1);
+        redisAssert(1 != 1);
     }
 }
 
@@ -2315,7 +2330,7 @@ static robj *getDecodedObject(robj *o) {
  * sdscmp() from sds.c will apply memcmp() so this function ca be considered
  * binary safe. */
 static int compareStringObjects(robj *a, robj *b) {
-    assert(a->type == REDIS_STRING && b->type == REDIS_STRING);
+    redisAssert(a->type == REDIS_STRING && b->type == REDIS_STRING);
     char bufa[128], bufb[128], *astr, *bstr;
     int bothsds = 1;
 
@@ -2338,7 +2353,7 @@ static int compareStringObjects(robj *a, robj *b) {
 }
 
 static size_t stringObjectLen(robj *o) {
-    assert(o->type == REDIS_STRING);
+    redisAssert(o->type == REDIS_STRING);
     if (o->encoding == REDIS_ENCODING_RAW) {
         return sdslen(o->ptr);
     } else {
@@ -2611,7 +2626,7 @@ static int rdbSave(char *filename) {
                 }
                 dictReleaseIterator(di);
             } else {
-                assert(0 != 0);
+                redisAssert(0 != 0);
             }
         }
         dictReleaseIterator(di);
@@ -2745,7 +2760,7 @@ static robj *rdbLoadIntegerObject(FILE *fp, int enctype) {
         val = (int32_t)v;
     } else {
         val = 0; /* anti-warning */
-        assert(0!=0);
+        redisAssert(0!=0);
     }
     return createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",val));
 }
@@ -2784,7 +2799,7 @@ static robj *rdbLoadStringObject(FILE*fp, int rdbver) {
         case REDIS_RDB_ENC_LZF:
             return tryObjectSharing(rdbLoadLzfStringObject(fp,rdbver));
         default:
-            assert(0!=0);
+            redisAssert(0!=0);
         }
     }
 
@@ -2910,7 +2925,7 @@ static int rdbLoad(char *filename) {
                 incrRefCount(ele); /* added to skiplist */
             }
         } else {
-            assert(0 != 0);
+            redisAssert(0 != 0);
         }
         /* Add the new object in the hash table */
         retval = dictAdd(d,keyobj,o);
@@ -3101,7 +3116,7 @@ static void incrDecrCommand(redisClient *c, long long incr) {
             else if (o->encoding == REDIS_ENCODING_INT)
                 value = (long)o->ptr;
             else
-                assert(1 != 1);
+                redisAssert(1 != 1);
         }
     }
 
@@ -4393,14 +4408,14 @@ static void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double scor
         
         /* case 2: Score update operation */
         de = dictFind(zs->dict,ele);
-        assert(de != NULL);
+        redisAssert(de != NULL);
         oldscore = dictGetEntryVal(de);
         if (*score != *oldscore) {
             int deleted;
 
             /* Remove and insert the element in the skip list with new score */
             deleted = zslDelete(zs->zsl,*oldscore,ele);
-            assert(deleted != 0);
+            redisAssert(deleted != 0);
             zslInsert(zs->zsl,*score,ele);
             incrRefCount(ele);
             /* Update the score in the hash table */
@@ -4455,7 +4470,7 @@ static void zremCommand(redisClient *c) {
         /* Delete from the skiplist */
         oldscore = dictGetEntryVal(de);
         deleted = zslDelete(zs->zsl,*oldscore,c->argv[2]);
-        assert(deleted != 0);
+        redisAssert(deleted != 0);
 
         /* Delete from the hash table */
         dictDelete(zs->dict,c->argv[2]);
@@ -4733,10 +4748,7 @@ static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
     keyname.buf[prefixlen+sublen+postfixlen] = '\0';
     keyname.len = prefixlen+sublen+postfixlen;
 
-    keyobj.refcount = 1;
-    keyobj.type = REDIS_STRING;
-    keyobj.ptr = ((char*)&keyname)+(sizeof(long)*2);
-
+    initStaticStringObject(keyobj,((char*)&keyname)+(sizeof(long)*2))
     decrRefCount(subst);
 
     /* printf("lookup '%s' => %p\n", keyname.buf,de); */
@@ -4865,7 +4877,7 @@ static void sortCommand(redisClient *c) {
     case REDIS_LIST: vectorlen = listLength((list*)sortval->ptr); break;
     case REDIS_SET: vectorlen =  dictSize((dict*)sortval->ptr); break;
     case REDIS_ZSET: vectorlen = dictSize(((zset*)sortval->ptr)->dict); break;
-    default: vectorlen = 0; assert(0); /* Avoid GCC warning */
+    default: vectorlen = 0; redisAssert(0); /* Avoid GCC warning */
     }
     vector = zmalloc(sizeof(redisSortObject)*vectorlen);
     j = 0;
@@ -4903,7 +4915,7 @@ static void sortCommand(redisClient *c) {
         }
         dictReleaseIterator(di);
     }
-    assert(j == vectorlen);
+    redisAssert(j == vectorlen);
 
     /* Now it's time to load the right scores in the sorting vector */
     if (dontsort == 0) {
@@ -4925,7 +4937,7 @@ static void sortCommand(redisClient *c) {
                         if (byval->encoding == REDIS_ENCODING_INT) {
                             vector[j].u.score = (long)byval->ptr;
                         } else
-                            assert(1 != 1);
+                            redisAssert(1 != 1);
                     }
                 }
             } else {
@@ -4936,7 +4948,7 @@ static void sortCommand(redisClient *c) {
                         if (vector[j].obj->encoding == REDIS_ENCODING_INT)
                             vector[j].u.score = (long) vector[j].obj->ptr;
                         else
-                            assert(1 != 1);
+                            redisAssert(1 != 1);
                     }
                 }
             }
@@ -4991,7 +5003,7 @@ static void sortCommand(redisClient *c) {
                         addReply(c,shared.crlf);
                     }
                 } else {
-                    assert(sop->type == REDIS_SORT_GET); /* always fails */
+                    redisAssert(sop->type == REDIS_SORT_GET); /* always fails */
                 }
             }
         }
@@ -5020,7 +5032,7 @@ static void sortCommand(redisClient *c) {
                         incrRefCount(val);
                     }
                 } else {
-                    assert(sop->type == REDIS_SORT_GET); /* always fails */
+                    redisAssert(sop->type == REDIS_SORT_GET); /* always fails */
                 }
             }
         }
@@ -5966,7 +5978,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                 }
                 dictReleaseIterator(di);
             } else {
-                assert(0 != 0);
+                redisAssert(0 != 0);
             }
             /* Save the expire time */
             if (expiretime != -1) {
@@ -6107,6 +6119,15 @@ static void debugCommand(redisClient *c) {
     }
 }
 
+static void _redisAssert(char *estr) {
+    redisLog(REDIS_WARNING,"=== ASSERTION FAILED ===");
+    redisLog(REDIS_WARNING,"==> %s\n",estr);
+#ifdef HAVE_BACKTRACE
+    redisLog(REDIS_WARNING,"(forcing SIGSEGV in order to print the stack trace)");
+    *((char*)-1) = 'x';
+#endif
+}
+
 /* =================================== Main! ================================ */
 
 #ifdef __linux__