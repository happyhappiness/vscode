@@ -75,6 +75,7 @@
 #include "lzf.h"    /* LZF compression library */
 #include "pqsort.h" /* Partial qsort for SORT+LIMIT */
 #include "zipmap.h" /* Compact dictionary-alike data structure */
+#include "ziplist.h" /* Compact list data structure */
 #include "sha1.h"   /* SHA1 is used for DEBUG DIGEST */
 #include "release.h" /* Release and/or git repository information */
 
@@ -125,13 +126,15 @@
 /* Objects encoding. Some kind of objects like Strings and Hashes can be
  * internally represented in multiple ways. The 'encoding' field of the object
  * is set to one of this fields for this object. */
-#define REDIS_ENCODING_RAW 0    /* Raw representation */
-#define REDIS_ENCODING_INT 1    /* Encoded as integer */
-#define REDIS_ENCODING_ZIPMAP 2 /* Encoded as zipmap */
-#define REDIS_ENCODING_HT 3     /* Encoded as an hash table */
+#define REDIS_ENCODING_RAW 0     /* Raw representation */
+#define REDIS_ENCODING_INT 1     /* Encoded as integer */
+#define REDIS_ENCODING_HT 2      /* Encoded as hash table */
+#define REDIS_ENCODING_ZIPMAP 3  /* Encoded as zipmap */
+#define REDIS_ENCODING_LIST 4    /* Encoded as zipmap */
+#define REDIS_ENCODING_ZIPLIST 5 /* Encoded as ziplist */
 
 static char* strencoding[] = {
-    "raw", "int", "zipmap", "hashtable"
+    "raw", "int", "hashtable", "zipmap", "list", "ziplist"
 };
 
 /* Object types only used for dumping to disk */
@@ -234,9 +237,11 @@ static char* strencoding[] = {
 #define APPENDFSYNC_ALWAYS 1
 #define APPENDFSYNC_EVERYSEC 2
 
-/* Hashes related defaults */
+/* Zip structure related defaults */
 #define REDIS_HASH_MAX_ZIPMAP_ENTRIES 64
 #define REDIS_HASH_MAX_ZIPMAP_VALUE 512
+#define REDIS_LIST_MAX_ZIPLIST_ENTRIES 1024
+#define REDIS_LIST_MAX_ZIPLIST_VALUE 32
 
 /* We can print the stacktrace, so our assert is defined this way: */
 #define redisAssert(_e) ((_e)?(void)0 : (_redisAssert(#_e,__FILE__,__LINE__),_exit(1)))
@@ -422,9 +427,11 @@ struct redisServer {
     off_t vm_page_size;
     off_t vm_pages;
     unsigned long long vm_max_memory;
-    /* Hashes config */
+    /* Zip structure config */
     size_t hash_max_zipmap_entries;
     size_t hash_max_zipmap_value;
+    size_t list_max_ziplist_entries;
+    size_t list_max_ziplist_value;
     /* Virtual memory state */
     FILE *vm_fp;
     int vm_fd;
@@ -643,6 +650,7 @@ static struct redisCommand *lookupCommand(char *name);
 static void call(redisClient *c, struct redisCommand *cmd);
 static void resetClient(redisClient *c);
 static void convertToRealHash(robj *o);
+static void listTypeConvert(robj *o, int enc);
 static int pubsubUnsubscribeAllChannels(redisClient *c, int notify);
 static int pubsubUnsubscribeAllPatterns(redisClient *c, int notify);
 static void freePubsubPattern(void *p);
@@ -1752,6 +1760,8 @@ static void initServerConfig() {
     server.vm_blocked_clients = 0;
     server.hash_max_zipmap_entries = REDIS_HASH_MAX_ZIPMAP_ENTRIES;
     server.hash_max_zipmap_value = REDIS_HASH_MAX_ZIPMAP_VALUE;
+    server.list_max_ziplist_entries = REDIS_LIST_MAX_ZIPLIST_ENTRIES;
+    server.list_max_ziplist_value = REDIS_LIST_MAX_ZIPLIST_VALUE;
     server.shutdown_asap = 0;
 
     resetServerSaveParams();
@@ -2030,6 +2040,10 @@ static void loadServerConfig(char *filename) {
             server.hash_max_zipmap_entries = memtoll(argv[1], NULL);
         } else if (!strcasecmp(argv[0],"hash-max-zipmap-value") && argc == 2){
             server.hash_max_zipmap_value = memtoll(argv[1], NULL);
+        } else if (!strcasecmp(argv[0],"list-max-ziplist-entries") && argc == 2){
+            server.list_max_ziplist_entries = memtoll(argv[1], NULL);
+        } else if (!strcasecmp(argv[0],"list-max-ziplist-value") && argc == 2){
+            server.list_max_ziplist_value = memtoll(argv[1], NULL);
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
@@ -3035,9 +3049,17 @@ static robj *dupStringObject(robj *o) {
 
 static robj *createListObject(void) {
     list *l = listCreate();
-
+    robj *o = createObject(REDIS_LIST,l);
     listSetFreeMethod(l,decrRefCount);
-    return createObject(REDIS_LIST,l);
+    o->encoding = REDIS_ENCODING_LIST;
+    return o;
+}
+
+static robj *createZiplistObject(void) {
+    unsigned char *zl = ziplistNew();
+    robj *o = createObject(REDIS_LIST,zl);
+    o->encoding = REDIS_ENCODING_ZIPLIST;
+    return o;
 }
 
 static robj *createSetObject(void) {
@@ -3070,7 +3092,16 @@ static void freeStringObject(robj *o) {
 }
 
 static void freeListObject(robj *o) {
-    listRelease((list*) o->ptr);
+    switch (o->encoding) {
+    case REDIS_ENCODING_LIST:
+        listRelease((list*) o->ptr);
+        break;
+    case REDIS_ENCODING_ZIPLIST:
+        zfree(o->ptr);
+        break;
+    default:
+        redisPanic("Unknown list encoding type");
+    }
 }
 
 static void freeSetObject(robj *o) {
@@ -3644,38 +3675,32 @@ static int rdbSaveRawString(FILE *fp, unsigned char *s, size_t len) {
     return 0;
 }
 
+/* Save a long long value as either an encoded string or a string. */
+static int rdbSaveLongLongAsStringObject(FILE *fp, long long value) {
+    unsigned char buf[32];
+    int enclen = rdbEncodeInteger(value,buf);
+    if (enclen > 0) {
+        if (fwrite(buf,enclen,1,fp) == 0) return -1;
+    } else {
+        /* Encode as string */
+        enclen = ll2string((char*)buf,32,value);
+        redisAssert(enclen < 32);
+        if (rdbSaveLen(fp,enclen) == -1) return -1;
+        if (fwrite(buf,enclen,1,fp) == 0) return -1;
+    }
+    return 0;
+}
+
 /* Like rdbSaveStringObjectRaw() but handle encoded objects */
 static int rdbSaveStringObject(FILE *fp, robj *obj) {
-    int retval;
-
     /* Avoid to decode the object, then encode it again, if the
      * object is alrady integer encoded. */
     if (obj->encoding == REDIS_ENCODING_INT) {
-        long val = (long) obj->ptr;
-        unsigned char buf[5];
-        int enclen;
-
-        if ((enclen = rdbEncodeInteger(val,buf)) > 0) {
-            if (fwrite(buf,enclen,1,fp) == 0) return -1;
-            return 0;
-        }
-        /* otherwise... fall throught and continue with the usual
-         * code path. */
-    }
-
-    /* Avoid incr/decr ref count business when possible.
-     * This plays well with copy-on-write given that we are probably
-     * in a child process (BGSAVE). Also this makes sure key objects
-     * of swapped objects are not incRefCount-ed (an assert does not allow
-     * this in order to avoid bugs) */
-    if (obj->encoding != REDIS_ENCODING_RAW) {
-        obj = getDecodedObject(obj);
-        retval = rdbSaveRawString(fp,obj->ptr,sdslen(obj->ptr));
-        decrRefCount(obj);
+        return rdbSaveLongLongAsStringObject(fp,(long)obj->ptr);
     } else {
-        retval = rdbSaveRawString(fp,obj->ptr,sdslen(obj->ptr));
+        redisAssert(obj->encoding == REDIS_ENCODING_RAW);
+        return rdbSaveRawString(fp,obj->ptr,sdslen(obj->ptr));
     }
-    return retval;
 }
 
 /* Save a double value. Doubles are saved as strings prefixed by an unsigned
@@ -3728,16 +3753,37 @@ static int rdbSaveObject(FILE *fp, robj *o) {
         if (rdbSaveStringObject(fp,o) == -1) return -1;
     } else if (o->type == REDIS_LIST) {
         /* Save a list value */
-        list *list = o->ptr;
-        listIter li;
-        listNode *ln;
-
-        if (rdbSaveLen(fp,listLength(list)) == -1) return -1;
-        listRewind(list,&li);
-        while((ln = listNext(&li))) {
-            robj *eleobj = listNodeValue(ln);
+        if (o->encoding == REDIS_ENCODING_ZIPLIST) {
+            unsigned char *p;
+            unsigned char *vstr;
+            unsigned int vlen;
+            long long vlong;
+
+            if (rdbSaveLen(fp,ziplistLen(o->ptr)) == -1) return -1;
+            p = ziplistIndex(o->ptr,0);
+            while(ziplistGet(p,&vstr,&vlen,&vlong)) {
+                if (vstr) {
+                    if (rdbSaveRawString(fp,vstr,vlen) == -1)
+                        return -1;
+                } else {
+                    if (rdbSaveLongLongAsStringObject(fp,vlong) == -1)
+                        return -1;
+                }
+                p = ziplistNext(o->ptr,p);
+            }
+        } else if (o->encoding == REDIS_ENCODING_LIST) {
+            list *list = o->ptr;
+            listIter li;
+            listNode *ln;
 
-            if (rdbSaveStringObject(fp,eleobj) == -1) return -1;
+            if (rdbSaveLen(fp,listLength(list)) == -1) return -1;
+            listRewind(list,&li);
+            while((ln = listNext(&li))) {
+                robj *eleobj = listNodeValue(ln);
+                if (rdbSaveStringObject(fp,eleobj) == -1) return -1;
+            }
+        } else {
+            redisPanic("Unknown list encoding");
         }
     } else if (o->type == REDIS_SET) {
         /* Save a set value */
@@ -4107,34 +4153,60 @@ static int rdbLoadDoubleValue(FILE *fp, double *val) {
 /* Load a Redis object of the specified type from the specified file.
  * On success a newly allocated object is returned, otherwise NULL. */
 static robj *rdbLoadObject(int type, FILE *fp) {
-    robj *o;
+    robj *o, *ele, *dec;
+    size_t len;
 
     redisLog(REDIS_DEBUG,"LOADING OBJECT %d (at %d)\n",type,ftell(fp));
     if (type == REDIS_STRING) {
         /* Read string value */
         if ((o = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
         o = tryObjectEncoding(o);
-    } else if (type == REDIS_LIST || type == REDIS_SET) {
-        /* Read list/set value */
-        uint32_t listlen;
+    } else if (type == REDIS_LIST) {
+        /* Read list value */
+        if ((len = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
 
-        if ((listlen = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
-        o = (type == REDIS_LIST) ? createListObject() : createSetObject();
+        /* Use a real list when there are too many entries */
+        if (len > server.list_max_ziplist_entries) {
+            o = createListObject();
+        } else {
+            o = createZiplistObject();
+        }
+
+        /* Load every single element of the list */
+        while(len--) {
+            if ((ele = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
+
+            /* If we are using a ziplist and the value is too big, convert
+             * the object to a real list. */
+            if (o->encoding == REDIS_ENCODING_ZIPLIST &&
+                ele->encoding == REDIS_ENCODING_RAW &&
+                sdslen(ele->ptr) > server.list_max_ziplist_value)
+                    listTypeConvert(o,REDIS_ENCODING_LIST);
+
+            if (o->encoding == REDIS_ENCODING_ZIPLIST) {
+                dec = getDecodedObject(ele);
+                o->ptr = ziplistPush(o->ptr,dec->ptr,sdslen(dec->ptr),REDIS_TAIL);
+                decrRefCount(dec);
+                decrRefCount(ele);
+            } else {
+                ele = tryObjectEncoding(ele);
+                listAddNodeTail(o->ptr,ele);
+                incrRefCount(ele);
+            }
+        }
+    } else if (type == REDIS_SET) {
+        /* Read list/set value */
+        if ((len = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
+        o = createSetObject();
         /* It's faster to expand the dict to the right size asap in order
          * to avoid rehashing */
-        if (type == REDIS_SET && listlen > DICT_HT_INITIAL_SIZE)
-            dictExpand(o->ptr,listlen);
+        if (len > DICT_HT_INITIAL_SIZE)
+            dictExpand(o->ptr,len);
         /* Load every single element of the list/set */
-        while(listlen--) {
-            robj *ele;
-
+        while(len--) {
             if ((ele = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
             ele = tryObjectEncoding(ele);
-            if (type == REDIS_LIST) {
-                listAddNodeTail((list*)o->ptr,ele);
-            } else {
-                dictAdd((dict*)o->ptr,ele,NULL);
-            }
+            dictAdd((dict*)o->ptr,ele,NULL);
         }
     } else if (type == REDIS_ZSET) {
         /* Read list/set value */
@@ -4833,24 +4905,251 @@ static void moveCommand(redisClient *c) {
 }
 
 /* =================================== Lists ================================ */
-static void pushGenericCommand(redisClient *c, int where) {
-    robj *lobj;
-    list *list;
 
-    lobj = lookupKeyWrite(c->db,c->argv[1]);
+
+/* Check the argument length to see if it requires us to convert the ziplist
+ * to a real list. Only check raw-encoded objects because integer encoded
+ * objects are never too long. */
+static void listTypeTryConversion(robj *subject, robj *value) {
+    if (subject->encoding != REDIS_ENCODING_ZIPLIST) return;
+    if (value->encoding == REDIS_ENCODING_RAW &&
+        sdslen(value->ptr) > server.list_max_ziplist_value)
+            listTypeConvert(subject,REDIS_ENCODING_LIST);
+}
+
+static void listTypePush(robj *subject, robj *value, int where) {
+    /* Check if we need to convert the ziplist */
+    listTypeTryConversion(subject,value);
+    if (subject->encoding == REDIS_ENCODING_ZIPLIST &&
+        ziplistLen(subject->ptr) > server.list_max_ziplist_entries)
+            listTypeConvert(subject,REDIS_ENCODING_LIST);
+
+    if (subject->encoding == REDIS_ENCODING_ZIPLIST) {
+        int pos = (where == REDIS_HEAD) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
+        value = getDecodedObject(value);
+        subject->ptr = ziplistPush(subject->ptr,value->ptr,sdslen(value->ptr),pos);
+        decrRefCount(value);
+    } else if (subject->encoding == REDIS_ENCODING_LIST) {
+        if (where == REDIS_HEAD) {
+            listAddNodeHead(subject->ptr,value);
+        } else {
+            listAddNodeTail(subject->ptr,value);
+        }
+        incrRefCount(value);
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+}
+
+static robj *listTypePop(robj *subject, int where) {
+    robj *value = NULL;
+    if (subject->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *p;
+        unsigned char *vstr;
+        unsigned int vlen;
+        long long vlong;
+        int pos = (where == REDIS_HEAD) ? 0 : -1;
+        p = ziplistIndex(subject->ptr,pos);
+        if (ziplistGet(p,&vstr,&vlen,&vlong)) {
+            if (vstr) {
+                value = createStringObject((char*)vstr,vlen);
+            } else {
+                value = createStringObjectFromLongLong(vlong);
+            }
+            /* We only need to delete an element when it exists */
+            subject->ptr = ziplistDelete(subject->ptr,&p);
+        }
+    } else if (subject->encoding == REDIS_ENCODING_LIST) {
+        list *list = subject->ptr;
+        listNode *ln;
+        if (where == REDIS_HEAD) {
+            ln = listFirst(list);
+        } else {
+            ln = listLast(list);
+        }
+        if (ln != NULL) {
+            value = listNodeValue(ln);
+            incrRefCount(value);
+            listDelNode(list,ln);
+        }
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+    return value;
+}
+
+static unsigned long listTypeLength(robj *subject) {
+    if (subject->encoding == REDIS_ENCODING_ZIPLIST) {
+        return ziplistLen(subject->ptr);
+    } else if (subject->encoding == REDIS_ENCODING_LIST) {
+        return listLength((list*)subject->ptr);
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+}
+
+/* Structure to hold set iteration abstraction. */
+typedef struct {
+    robj *subject;
+    unsigned char encoding;
+    unsigned char direction; /* Iteration direction */
+    unsigned char *zi;
+    listNode *ln;
+} listTypeIterator;
+
+/* Structure for an entry while iterating over a list. */
+typedef struct {
+    listTypeIterator *li;
+    unsigned char *zi;  /* Entry in ziplist */
+    listNode *ln;       /* Entry in linked list */
+} listTypeEntry;
+
+/* Initialize an iterator at the specified index. */
+static listTypeIterator *listTypeInitIterator(robj *subject, int index, unsigned char direction) {
+    listTypeIterator *li = zmalloc(sizeof(listTypeIterator));
+    li->subject = subject;
+    li->encoding = subject->encoding;
+    li->direction = direction;
+    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
+        li->zi = ziplistIndex(subject->ptr,index);
+    } else if (li->encoding == REDIS_ENCODING_LIST) {
+        li->ln = listIndex(subject->ptr,index);
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+    return li;
+}
+
+/* Clean up the iterator. */
+static void listTypeReleaseIterator(listTypeIterator *li) {
+    zfree(li);
+}
+
+/* Stores pointer to current the entry in the provided entry structure
+ * and advances the position of the iterator. Returns 1 when the current
+ * entry is in fact an entry, 0 otherwise. */
+static int listTypeNext(listTypeIterator *li, listTypeEntry *entry) {
+    /* Protect from converting when iterating */
+    redisAssert(li->subject->encoding == li->encoding);
+
+    entry->li = li;
+    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
+        entry->zi = li->zi;
+        if (entry->zi != NULL) {
+            if (li->direction == REDIS_TAIL)
+                li->zi = ziplistNext(li->subject->ptr,li->zi);
+            else
+                li->zi = ziplistPrev(li->subject->ptr,li->zi);
+            return 1;
+        }
+    } else if (li->encoding == REDIS_ENCODING_LIST) {
+        entry->ln = li->ln;
+        if (entry->ln != NULL) {
+            if (li->direction == REDIS_TAIL)
+                li->ln = li->ln->next;
+            else
+                li->ln = li->ln->prev;
+            return 1;
+        }
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+    return 0;
+}
+
+/* Return entry or NULL at the current position of the iterator. */
+static robj *listTypeGet(listTypeEntry *entry) {
+    listTypeIterator *li = entry->li;
+    robj *value = NULL;
+    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *vstr;
+        unsigned int vlen;
+        long long vlong;
+        redisAssert(entry->zi != NULL);
+        if (ziplistGet(entry->zi,&vstr,&vlen,&vlong)) {
+            if (vstr) {
+                value = createStringObject((char*)vstr,vlen);
+            } else {
+                value = createStringObjectFromLongLong(vlong);
+            }
+        }
+    } else if (li->encoding == REDIS_ENCODING_LIST) {
+        redisAssert(entry->ln != NULL);
+        value = listNodeValue(entry->ln);
+        incrRefCount(value);
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+    return value;
+}
+
+/* Compare the given object with the entry at the current position. */
+static int listTypeEqual(listTypeEntry *entry, robj *o) {
+    listTypeIterator *li = entry->li;
+    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
+        redisAssert(o->encoding == REDIS_ENCODING_RAW);
+        return ziplistCompare(entry->zi,o->ptr,sdslen(o->ptr));
+    } else if (li->encoding == REDIS_ENCODING_LIST) {
+        return equalStringObjects(o,listNodeValue(entry->ln));
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+}
+
+/* Delete the element pointed to. */
+static void listTypeDelete(listTypeEntry *entry) {
+    listTypeIterator *li = entry->li;
+    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *p = entry->zi;
+        li->subject->ptr = ziplistDelete(li->subject->ptr,&p);
+
+        /* Update position of the iterator depending on the direction */
+        if (li->direction == REDIS_TAIL)
+            li->zi = p;
+        else
+            li->zi = ziplistPrev(li->subject->ptr,p);
+    } else if (entry->li->encoding == REDIS_ENCODING_LIST) {
+        listNode *next;
+        if (li->direction == REDIS_TAIL)
+            next = entry->ln->next;
+        else
+            next = entry->ln->prev;
+        listDelNode(li->subject->ptr,entry->ln);
+        li->ln = next;
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+}
+
+static void listTypeConvert(robj *subject, int enc) {
+    listTypeIterator *li;
+    listTypeEntry entry;
+    redisAssert(subject->type == REDIS_LIST);
+
+    if (enc == REDIS_ENCODING_LIST) {
+        list *l = listCreate();
+
+        /* listTypeGet returns a robj with incremented refcount */
+        li = listTypeInitIterator(subject,0,REDIS_TAIL);
+        while (listTypeNext(li,&entry)) listAddNodeTail(l,listTypeGet(&entry));
+        listTypeReleaseIterator(li);
+
+        subject->encoding = REDIS_ENCODING_LIST;
+        zfree(subject->ptr);
+        subject->ptr = l;
+    } else {
+        redisPanic("Unsupported list conversion");
+    }
+}
+
+static void pushGenericCommand(redisClient *c, int where) {
+    robj *lobj = lookupKeyWrite(c->db,c->argv[1]);
     if (lobj == NULL) {
         if (handleClientsWaitingListPush(c,c->argv[1],c->argv[2])) {
             addReply(c,shared.cone);
             return;
         }
-        lobj = createListObject();
-        list = lobj->ptr;
-        if (where == REDIS_HEAD) {
-            listAddNodeHead(list,c->argv[2]);
-        } else {
-            listAddNodeTail(list,c->argv[2]);
-        }
-        incrRefCount(c->argv[2]);
+        lobj = createZiplistObject();
         dbAdd(c->db,c->argv[1],lobj);
     } else {
         if (lobj->type != REDIS_LIST) {
@@ -4861,16 +5160,10 @@ static void pushGenericCommand(redisClient *c, int where) {
             addReply(c,shared.cone);
             return;
         }
-        list = lobj->ptr;
-        if (where == REDIS_HEAD) {
-            listAddNodeHead(list,c->argv[2]);
-        } else {
-            listAddNodeTail(list,c->argv[2]);
-        }
-        incrRefCount(c->argv[2]);
     }
+    listTypePush(lobj,c->argv[2],where);
+    addReplyLongLong(c,listTypeLength(lobj));
     server.dirty++;
-    addReplyLongLong(c,listLength(list));
 }
 
 static void lpushCommand(redisClient *c) {
@@ -4882,80 +5175,94 @@ static void rpushCommand(redisClient *c) {
 }
 
 static void llenCommand(redisClient *c) {
-    robj *o;
-    list *l;
-
-    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,o,REDIS_LIST)) return;
-
-    l = o->ptr;
-    addReplyUlong(c,listLength(l));
+    robj *o = lookupKeyReadOrReply(c,c->argv[1],shared.czero);
+    if (o == NULL || checkType(c,o,REDIS_LIST)) return;
+    addReplyUlong(c,listTypeLength(o));
 }
 
 static void lindexCommand(redisClient *c) {
-    robj *o;
+    robj *o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk);
+    if (o == NULL || checkType(c,o,REDIS_LIST)) return;
     int index = atoi(c->argv[2]->ptr);
-    list *list;
-    listNode *ln;
-
-    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
-        checkType(c,o,REDIS_LIST)) return;
-    list = o->ptr;
+    robj *value = NULL;
 
-    ln = listIndex(list, index);
-    if (ln == NULL) {
-        addReply(c,shared.nullbulk);
+    if (o->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *p;
+        unsigned char *vstr;
+        unsigned int vlen;
+        long long vlong;
+        p = ziplistIndex(o->ptr,index);
+        if (ziplistGet(p,&vstr,&vlen,&vlong)) {
+            if (vstr) {
+                value = createStringObject((char*)vstr,vlen);
+            } else {
+                value = createStringObjectFromLongLong(vlong);
+            }
+            addReplyBulk(c,value);
+            decrRefCount(value);
+        } else {
+            addReply(c,shared.nullbulk);
+        }
+    } else if (o->encoding == REDIS_ENCODING_LIST) {
+        listNode *ln = listIndex(o->ptr,index);
+        if (ln != NULL) {
+            value = listNodeValue(ln);
+            addReplyBulk(c,value);
+        } else {
+            addReply(c,shared.nullbulk);
+        }
     } else {
-        robj *ele = listNodeValue(ln);
-        addReplyBulk(c,ele);
+        redisPanic("Unknown list encoding");
     }
 }
 
 static void lsetCommand(redisClient *c) {
-    robj *o;
+    robj *o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr);
+    if (o == NULL || checkType(c,o,REDIS_LIST)) return;
     int index = atoi(c->argv[2]->ptr);
-    list *list;
-    listNode *ln;
-
-    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr)) == NULL ||
-        checkType(c,o,REDIS_LIST)) return;
-    list = o->ptr;
-
-    ln = listIndex(list, index);
-    if (ln == NULL) {
-        addReply(c,shared.outofrangeerr);
+    robj *value = c->argv[3];
+
+    listTypeTryConversion(o,value);
+    if (o->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *p, *zl = o->ptr;
+        p = ziplistIndex(zl,index);
+        if (p == NULL) {
+            addReply(c,shared.outofrangeerr);
+        } else {
+            o->ptr = ziplistDelete(o->ptr,&p);
+            value = getDecodedObject(value);
+            o->ptr = ziplistInsert(o->ptr,p,value->ptr,sdslen(value->ptr));
+            decrRefCount(value);
+            addReply(c,shared.ok);
+            server.dirty++;
+        }
+    } else if (o->encoding == REDIS_ENCODING_LIST) {
+        listNode *ln = listIndex(o->ptr,index);
+        if (ln == NULL) {
+            addReply(c,shared.outofrangeerr);
+        } else {
+            decrRefCount((robj*)listNodeValue(ln));
+            listNodeValue(ln) = value;
+            incrRefCount(value);
+            addReply(c,shared.ok);
+            server.dirty++;
+        }
     } else {
-        robj *ele = listNodeValue(ln);
-
-        decrRefCount(ele);
-        listNodeValue(ln) = c->argv[3];
-        incrRefCount(c->argv[3]);
-        addReply(c,shared.ok);
-        server.dirty++;
+        redisPanic("Unknown list encoding");
     }
 }
 
 static void popGenericCommand(redisClient *c, int where) {
-    robj *o;
-    list *list;
-    listNode *ln;
-
-    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
-        checkType(c,o,REDIS_LIST)) return;
-    list = o->ptr;
-
-    if (where == REDIS_HEAD)
-        ln = listFirst(list);
-    else
-        ln = listLast(list);
+    robj *o = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk);
+    if (o == NULL || checkType(c,o,REDIS_LIST)) return;
 
-    if (ln == NULL) {
+    robj *value = listTypePop(o,where);
+    if (value == NULL) {
         addReply(c,shared.nullbulk);
     } else {
-        robj *ele = listNodeValue(ln);
-        addReplyBulk(c,ele);
-        listDelNode(list,ln);
-        if (listLength(list) == 0) dbDelete(c->db,c->argv[1]);
+        addReplyBulk(c,value);
+        decrRefCount(value);
+        if (listTypeLength(o) == 0) dbDelete(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -4969,19 +5276,16 @@ static void rpopCommand(redisClient *c) {
 }
 
 static void lrangeCommand(redisClient *c) {
-    robj *o;
+    robj *o, *value;
     int start = atoi(c->argv[2]->ptr);
     int end = atoi(c->argv[3]->ptr);
     int llen;
     int rangelen, j;
-    list *list;
-    listNode *ln;
-    robj *ele;
+    listTypeEntry entry;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
          || checkType(c,o,REDIS_LIST)) return;
-    list = o->ptr;
-    llen = listLength(list);
+    llen = listTypeLength(o);
 
     /* convert negative indexes */
     if (start < 0) start = llen+start;
@@ -4999,13 +5303,15 @@ static void lrangeCommand(redisClient *c) {
     rangelen = (end-start)+1;
 
     /* Return the result in form of a multi-bulk reply */
-    ln = listIndex(list, start);
     addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
+    listTypeIterator *li = listTypeInitIterator(o,start,REDIS_TAIL);
     for (j = 0; j < rangelen; j++) {
-        ele = listNodeValue(ln);
-        addReplyBulk(c,ele);
-        ln = ln->next;
+        redisAssert(listTypeNext(li,&entry));
+        value = listTypeGet(&entry);
+        addReplyBulk(c,value);
+        decrRefCount(value);
     }
+    listTypeReleaseIterator(li);
 }
 
 static void ltrimCommand(redisClient *c) {
@@ -5019,8 +5325,7 @@ static void ltrimCommand(redisClient *c) {
 
     if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.ok)) == NULL ||
         checkType(c,o,REDIS_LIST)) return;
-    list = o->ptr;
-    llen = listLength(list);
+    llen = listTypeLength(o);
 
     /* convert negative indexes */
     if (start < 0) start = llen+start;
@@ -5040,49 +5345,63 @@ static void ltrimCommand(redisClient *c) {
     }
 
     /* Remove list elements to perform the trim */
-    for (j = 0; j < ltrim; j++) {
-        ln = listFirst(list);
-        listDelNode(list,ln);
-    }
-    for (j = 0; j < rtrim; j++) {
-        ln = listLast(list);
-        listDelNode(list,ln);
+    if (o->encoding == REDIS_ENCODING_ZIPLIST) {
+        o->ptr = ziplistDeleteRange(o->ptr,0,ltrim);
+        o->ptr = ziplistDeleteRange(o->ptr,-rtrim,rtrim);
+    } else if (o->encoding == REDIS_ENCODING_LIST) {
+        list = o->ptr;
+        for (j = 0; j < ltrim; j++) {
+            ln = listFirst(list);
+            listDelNode(list,ln);
+        }
+        for (j = 0; j < rtrim; j++) {
+            ln = listLast(list);
+            listDelNode(list,ln);
+        }
+    } else {
+        redisPanic("Unknown list encoding");
     }
-    if (listLength(list) == 0) dbDelete(c->db,c->argv[1]);
+    if (listTypeLength(o) == 0) dbDelete(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.ok);
 }
 
 static void lremCommand(redisClient *c) {
-    robj *o;
-    list *list;
-    listNode *ln, *next;
+    robj *subject, *obj = c->argv[3];
     int toremove = atoi(c->argv[2]->ptr);
     int removed = 0;
-    int fromtail = 0;
+    listTypeEntry entry;
 
-    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,o,REDIS_LIST)) return;
-    list = o->ptr;
+    subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero);
+    if (subject == NULL || checkType(c,subject,REDIS_LIST)) return;
+
+    /* Make sure obj is raw when we're dealing with a ziplist */
+    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
+        obj = getDecodedObject(obj);
 
+    listTypeIterator *li;
     if (toremove < 0) {
         toremove = -toremove;
-        fromtail = 1;
+        li = listTypeInitIterator(subject,-1,REDIS_HEAD);
+    } else {
+        li = listTypeInitIterator(subject,0,REDIS_TAIL);
     }
-    ln = fromtail ? list->tail : list->head;
-    while (ln) {
-        robj *ele = listNodeValue(ln);
 
-        next = fromtail ? ln->prev : ln->next;
-        if (equalStringObjects(ele,c->argv[3])) {
-            listDelNode(list,ln);
+    while (listTypeNext(li,&entry)) {
+        if (listTypeEqual(&entry,obj)) {
+            listTypeDelete(&entry);
             server.dirty++;
             removed++;
             if (toremove && removed == toremove) break;
         }
-        ln = next;
     }
-    if (listLength(list) == 0) dbDelete(c->db,c->argv[1]);
+    listTypeReleaseIterator(li);
+
+    /* Clean up raw encoded object */
+    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
+        decrRefCount(obj);
+
+    if (listTypeLength(subject) == 0) dbDelete(c->db,c->argv[1]);
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
 }
 
@@ -5102,46 +5421,36 @@ static void lremCommand(redisClient *c) {
  * as well. This command was originally proposed by Ezra Zygmuntowicz.
  */
 static void rpoplpushcommand(redisClient *c) {
-    robj *sobj;
-    list *srclist;
-    listNode *ln;
-
+    robj *sobj, *value;
     if ((sobj = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
         checkType(c,sobj,REDIS_LIST)) return;
-    srclist = sobj->ptr;
-    ln = listLast(srclist);
 
-    if (ln == NULL) {
+    if (listTypeLength(sobj) == 0) {
         addReply(c,shared.nullbulk);
     } else {
         robj *dobj = lookupKeyWrite(c->db,c->argv[2]);
-        robj *ele = listNodeValue(ln);
-        list *dstlist;
-
-        if (dobj && dobj->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerr);
-            return;
-        }
+        if (dobj && checkType(c,dobj,REDIS_LIST)) return;
+        value = listTypePop(sobj,REDIS_TAIL);
 
         /* Add the element to the target list (unless it's directly
          * passed to some BLPOP-ing client */
-        if (!handleClientsWaitingListPush(c,c->argv[2],ele)) {
-            if (dobj == NULL) {
-                /* Create the list if the key does not exist */
-                dobj = createListObject();
+        if (!handleClientsWaitingListPush(c,c->argv[2],value)) {
+            /* Create the list if the key does not exist */
+            if (!dobj) {
+                dobj = createZiplistObject();
                 dbAdd(c->db,c->argv[2],dobj);
             }
-            dstlist = dobj->ptr;
-            listAddNodeHead(dstlist,ele);
-            incrRefCount(ele);
+            listTypePush(dobj,value,REDIS_HEAD);
         }
 
         /* Send the element to the client as reply as well */
-        addReplyBulk(c,ele);
+        addReplyBulk(c,value);
 
-        /* Finally remove the element from the source list */
-        listDelNode(srclist,ln);
-        if (listLength(srclist) == 0) dbDelete(c->db,c->argv[1]);
+        /* listTypePop returns an object with its refcount incremented */
+        decrRefCount(value);
+
+        /* Delete the source list when it is empty */
+        if (listTypeLength(sobj) == 0) dbDelete(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -5764,7 +6073,7 @@ static zskiplistNode *zslFirstWithScore(zskiplist *zsl, double score) {
  * Returns 0 when the element cannot be found, rank otherwise.
  * Note that the rank is 1-based due to the span of zsl->header to the
  * first element. */
-static unsigned long zslGetRank(zskiplist *zsl, double score, robj *o) {
+static unsigned long zslistTypeGetRank(zskiplist *zsl, double score, robj *o) {
     zskiplistNode *x;
     unsigned long rank = 0;
     int i;
@@ -5788,7 +6097,7 @@ static unsigned long zslGetRank(zskiplist *zsl, double score, robj *o) {
 }
 
 /* Finds an element by its rank. The rank argument needs to be 1-based. */
-zskiplistNode* zslGetElementByRank(zskiplist *zsl, unsigned long rank) {
+zskiplistNode* zslistTypeGetElementByRank(zskiplist *zsl, unsigned long rank) {
     zskiplistNode *x;
     unsigned long traversed = 0;
     int i;
@@ -6254,10 +6563,10 @@ static void zrangeGenericCommand(redisClient *c, int reverse) {
     /* check if starting point is trivial, before searching
      * the element in log(N) time */
     if (reverse) {
-        ln = start == 0 ? zsl->tail : zslGetElementByRank(zsl, llen-start);
+        ln = start == 0 ? zsl->tail : zslistTypeGetElementByRank(zsl, llen-start);
     } else {
         ln = start == 0 ?
-            zsl->header->forward[0] : zslGetElementByRank(zsl, start+1);
+            zsl->header->forward[0] : zslistTypeGetElementByRank(zsl, start+1);
     }
 
     /* Return the result in form of a multi-bulk reply */
@@ -6454,7 +6763,7 @@ static void zrankGenericCommand(redisClient *c, int reverse) {
     }
 
     score = dictGetEntryVal(de);
-    rank = zslGetRank(zsl, *score, c->argv[2]);
+    rank = zslistTypeGetRank(zsl, *score, c->argv[2]);
     if (rank) {
         if (reverse) {
             addReplyLongLong(c, zsl->length - rank);
@@ -7031,7 +7340,7 @@ static int sortCompare(const void *s1, const void *s2) {
  * is optimized for speed and a bit less for readability */
 static void sortCommand(redisClient *c) {
     list *operations;
-    int outputlen = 0;
+    unsigned int outputlen = 0;
     int desc = 0, alpha = 0;
     int limit_start = 0, limit_count = -1, start, end;
     int j, dontsort = 0, vectorlen;
@@ -7101,7 +7410,7 @@ static void sortCommand(redisClient *c) {
 
     /* Load the sorting vector with all the objects to sort */
     switch(sortval->type) {
-    case REDIS_LIST: vectorlen = listLength((list*)sortval->ptr); break;
+    case REDIS_LIST: vectorlen = listTypeLength(sortval); break;
     case REDIS_SET: vectorlen =  dictSize((dict*)sortval->ptr); break;
     case REDIS_ZSET: vectorlen = dictSize(((zset*)sortval->ptr)->dict); break;
     default: vectorlen = 0; redisPanic("Bad SORT type"); /* Avoid GCC warning */
@@ -7110,18 +7419,15 @@ static void sortCommand(redisClient *c) {
     j = 0;
 
     if (sortval->type == REDIS_LIST) {
-        list *list = sortval->ptr;
-        listNode *ln;
-        listIter li;
-
-        listRewind(list,&li);
-        while((ln = listNext(&li))) {
-            robj *ele = ln->value;
-            vector[j].obj = ele;
+        listTypeIterator *li = listTypeInitIterator(sortval,0,REDIS_TAIL);
+        listTypeEntry entry;
+        while(listTypeNext(li,&entry)) {
+            vector[j].obj = listTypeGet(&entry);
             vector[j].u.score = 0;
             vector[j].u.cmpobj = NULL;
             j++;
         }
+        listTypeReleaseIterator(li);
     } else {
         dict *set;
         dictIterator *di;
@@ -7231,40 +7537,38 @@ static void sortCommand(redisClient *c) {
             }
         }
     } else {
-        robj *listObject = createListObject();
-        list *listPtr = (list*) listObject->ptr;
+        robj *sobj = createZiplistObject();
 
         /* STORE option specified, set the sorting result as a List object */
         for (j = start; j <= end; j++) {
             listNode *ln;
             listIter li;
 
             if (!getop) {
-                listAddNodeTail(listPtr,vector[j].obj);
-                incrRefCount(vector[j].obj);
-            }
-            listRewind(operations,&li);
-            while((ln = listNext(&li))) {
-                redisSortOperation *sop = ln->value;
-                robj *val = lookupKeyByPattern(c->db,sop->pattern,
-                    vector[j].obj);
+                listTypePush(sobj,vector[j].obj,REDIS_TAIL);
+            } else {
+                listRewind(operations,&li);
+                while((ln = listNext(&li))) {
+                    redisSortOperation *sop = ln->value;
+                    robj *val = lookupKeyByPattern(c->db,sop->pattern,
+                        vector[j].obj);
 
-                if (sop->type == REDIS_SORT_GET) {
-                    if (!val) {
-                        listAddNodeTail(listPtr,createStringObject("",0));
+                    if (sop->type == REDIS_SORT_GET) {
+                        if (!val) val = createStringObject("",0);
+
+                        /* listTypePush does an incrRefCount, so we should take care
+                         * care of the incremented refcount caused by either
+                         * lookupKeyByPattern or createStringObject("",0) */
+                        listTypePush(sobj,val,REDIS_TAIL);
+                        decrRefCount(val);
                     } else {
-                        /* We should do a incrRefCount on val because it is
-                         * added to the list, but also a decrRefCount because
-                         * it is returned by lookupKeyByPattern. This results
-                         * in doing nothing at all. */
-                        listAddNodeTail(listPtr,val);
+                        /* always fails */
+                        redisAssert(sop->type == REDIS_SORT_GET);
                     }
-                } else {
-                    redisAssert(sop->type == REDIS_SORT_GET); /* always fails */
                 }
             }
         }
-        dbReplace(c->db,storekey,listObject);
+        dbReplace(c->db,storekey,sobj);
         /* Note: we add 1 because the DB is dirty anyway since even if the
          * SORT result is empty a new key is set and maybe the old content
          * replaced. */
@@ -7273,6 +7577,9 @@ static void sortCommand(redisClient *c) {
     }
 
     /* Cleanup */
+    if (sortval->type == REDIS_LIST)
+        for (j = 0; j < vectorlen; j++)
+            decrRefCount(vector[j].obj);
     decrRefCount(sortval);
     listRelease(operations);
     for (j = 0; j < vectorlen; j++) {
@@ -8597,40 +8904,17 @@ int loadAppendOnlyFile(char *filename) {
     exit(1);
 }
 
-/* Write an object into a file in the bulk format $<count>\r\n<payload>\r\n */
-static int fwriteBulkObject(FILE *fp, robj *obj) {
-    char buf[128];
-    int decrrc = 0;
-
-    /* Avoid the incr/decr ref count business if possible to help
-     * copy-on-write (we are often in a child process when this function
-     * is called).
-     * Also makes sure that key objects don't get incrRefCount-ed when VM
-     * is enabled */
-    if (obj->encoding != REDIS_ENCODING_RAW) {
-        obj = getDecodedObject(obj);
-        decrrc = 1;
-    }
-    snprintf(buf,sizeof(buf),"$%ld\r\n",(long)sdslen(obj->ptr));
-    if (fwrite(buf,strlen(buf),1,fp) == 0) goto err;
-    if (sdslen(obj->ptr) && fwrite(obj->ptr,sdslen(obj->ptr),1,fp) == 0)
-        goto err;
-    if (fwrite("\r\n",2,1,fp) == 0) goto err;
-    if (decrrc) decrRefCount(obj);
-    return 1;
-err:
-    if (decrrc) decrRefCount(obj);
-    return 0;
-}
-
 /* Write binary-safe string into a file in the bulkformat
  * $<count>\r\n<payload>\r\n */
 static int fwriteBulkString(FILE *fp, char *s, unsigned long len) {
-    char buf[128];
-
-    snprintf(buf,sizeof(buf),"$%ld\r\n",(unsigned long)len);
-    if (fwrite(buf,strlen(buf),1,fp) == 0) return 0;
-    if (len && fwrite(s,len,1,fp) == 0) return 0;
+    char cbuf[128];
+    int clen;
+    cbuf[0] = '$';
+    clen = 1+ll2string(cbuf+1,sizeof(cbuf)-1,len);
+    cbuf[clen++] = '\r';
+    cbuf[clen++] = '\n';
+    if (fwrite(cbuf,clen,1,fp) == 0) return 0;
+    if (len > 0 && fwrite(s,len,1,fp) == 0) return 0;
     if (fwrite("\r\n",2,1,fp) == 0) return 0;
     return 1;
 }
@@ -8647,16 +8931,28 @@ static int fwriteBulkDouble(FILE *fp, double d) {
 }
 
 /* Write a long value in bulk format $<count>\r\n<payload>\r\n */
-static int fwriteBulkLong(FILE *fp, long l) {
-    char buf[128], lbuf[128];
-
-    snprintf(lbuf,sizeof(lbuf),"%ld\r\n",l);
-    snprintf(buf,sizeof(buf),"$%lu\r\n",(unsigned long)strlen(lbuf)-2);
-    if (fwrite(buf,strlen(buf),1,fp) == 0) return 0;
-    if (fwrite(lbuf,strlen(lbuf),1,fp) == 0) return 0;
+static int fwriteBulkLongLong(FILE *fp, long long l) {
+    char bbuf[128], lbuf[128];
+    unsigned int blen, llen;
+    llen = ll2string(lbuf,32,l);
+    blen = snprintf(bbuf,sizeof(bbuf),"$%u\r\n%s\r\n",llen,lbuf);
+    if (fwrite(bbuf,blen,1,fp) == 0) return 0;
     return 1;
 }
 
+/* Delegate writing an object to writing a bulk string or bulk long long. */
+static int fwriteBulkObject(FILE *fp, robj *obj) {
+    /* Avoid using getDecodedObject to help copy-on-write (we are often
+     * in a child process when this function is called). */
+    if (obj->encoding == REDIS_ENCODING_INT) {
+        return fwriteBulkLongLong(fp,(long)obj->ptr);
+    } else if (obj->encoding == REDIS_ENCODING_RAW) {
+        return fwriteBulkString(fp,obj->ptr,sdslen(obj->ptr));
+    } else {
+        redisPanic("Unknown string encoding");
+    }
+}
+
 /* Write a sequence of commands able to fully rebuild the dataset into
  * "filename". Used both by REWRITEAOF and BGREWRITEAOF. */
 static int rewriteAppendOnlyFile(char *filename) {
@@ -8688,7 +8984,7 @@ static int rewriteAppendOnlyFile(char *filename) {
 
         /* SELECT the new DB */
         if (fwrite(selectcmd,sizeof(selectcmd)-1,1,fp) == 0) goto werr;
-        if (fwriteBulkLong(fp,j) == 0) goto werr;
+        if (fwriteBulkLongLong(fp,j) == 0) goto werr;
 
         /* Iterate this DB writing every entry */
         while((de = dictNext(di)) != NULL) {
@@ -8723,18 +9019,41 @@ static int rewriteAppendOnlyFile(char *filename) {
                 if (fwriteBulkObject(fp,o) == 0) goto werr;
             } else if (o->type == REDIS_LIST) {
                 /* Emit the RPUSHes needed to rebuild the list */
-                list *list = o->ptr;
-                listNode *ln;
-                listIter li;
+                char cmd[]="*3\r\n$5\r\nRPUSH\r\n";
+                if (o->encoding == REDIS_ENCODING_ZIPLIST) {
+                    unsigned char *zl = o->ptr;
+                    unsigned char *p = ziplistIndex(zl,0);
+                    unsigned char *vstr;
+                    unsigned int vlen;
+                    long long vlong;
+
+                    while(ziplistGet(p,&vstr,&vlen,&vlong)) {
+                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
+                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
+                        if (vstr) {
+                            if (fwriteBulkString(fp,(char*)vstr,vlen) == 0)
+                                goto werr;
+                        } else {
+                            if (fwriteBulkLongLong(fp,vlong) == 0)
+                                goto werr;
+                        }
+                        p = ziplistNext(zl,p);
+                    }
+                } else if (o->encoding == REDIS_ENCODING_LIST) {
+                    list *list = o->ptr;
+                    listNode *ln;
+                    listIter li;
 
-                listRewind(list,&li);
-                while((ln = listNext(&li))) {
-                    char cmd[]="*3\r\n$5\r\nRPUSH\r\n";
-                    robj *eleobj = listNodeValue(ln);
+                    listRewind(list,&li);
+                    while((ln = listNext(&li))) {
+                        robj *eleobj = listNodeValue(ln);
 
-                    if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                    if (fwriteBulkObject(fp,&key) == 0) goto werr;
-                    if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
+                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
+                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
+                        if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
+                    }
+                } else {
+                    redisPanic("Unknown list encoding");
                 }
             } else if (o->type == REDIS_SET) {
                 /* Emit the SADDs needed to rebuild the set */
@@ -8810,7 +9129,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                 if (expiretime < now) continue;
                 if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
                 if (fwriteBulkObject(fp,&key) == 0) goto werr;
-                if (fwriteBulkLong(fp,expiretime) == 0) goto werr;
+                if (fwriteBulkLongLong(fp,expiretime) == 0) goto werr;
             }
             if (swapped) decrRefCount(o);
         }
@@ -10759,16 +11078,14 @@ static void computeDatasetDigest(unsigned char *final) {
             if (o->type == REDIS_STRING) {
                 mixObjectDigest(digest,o);
             } else if (o->type == REDIS_LIST) {
-                list *list = o->ptr;
-                listNode *ln;
-                listIter li;
-
-                listRewind(list,&li);
-                while((ln = listNext(&li))) {
-                    robj *eleobj = listNodeValue(ln);
-
+                listTypeIterator *li = listTypeInitIterator(o,0,REDIS_TAIL);
+                listTypeEntry entry;
+                while(listTypeNext(li,&entry)) {
+                    robj *eleobj = listTypeGet(&entry);
                     mixObjectDigest(digest,eleobj);
+                    decrRefCount(eleobj);
                 }
+                listTypeReleaseIterator(li);
             } else if (o->type == REDIS_SET) {
                 dict *set = o->ptr;
                 dictIterator *di = dictGetIterator(set);