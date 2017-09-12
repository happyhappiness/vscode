@@ -1,5 +1,4 @@
 #include "redis.h"
-
 #include <sys/uio.h>
 
 void *dupClientReplyValue(void *o) {
@@ -12,7 +11,16 @@ int listMatchObjects(void *a, void *b) {
 }
 
 redisClient *createClient(int fd) {
-    redisClient *c = zmalloc(sizeof(*c));
+    redisClient *c;
+
+    /* Make sure to allocate a multiple of the page size to prevent wasting
+     * memory. A page size of 4096 is assumed here. We need to compensate
+     * for the zmalloc overhead of sizeof(size_t) bytes. */
+    size_t size = 8192-sizeof(size_t);
+    redisAssert(size > sizeof(redisClient));
+    c = zmalloc(size);
+    c->buflen = size-sizeof(redisClient);
+    c->bufpos = 0;
 
     anetNonBlock(NULL,fd);
     anetTcpNoDelay(NULL,fd);
@@ -53,70 +61,118 @@ redisClient *createClient(int fd) {
     return c;
 }
 
-void addReply(redisClient *c, robj *obj) {
-    if (listLength(c->reply) == 0 &&
+int _ensureFileEvent(redisClient *c) {
+    if (c->bufpos == 0 && listLength(c->reply) == 0 &&
         (c->replstate == REDIS_REPL_NONE ||
          c->replstate == REDIS_REPL_ONLINE) &&
         aeCreateFileEvent(server.el, c->fd, AE_WRITABLE,
-        sendReplyToClient, c) == AE_ERR) return;
+        sendReplyToClient, c) == AE_ERR) return REDIS_ERR;
+    return REDIS_OK;
+}
 
+void _addReplyObjectToList(redisClient *c, robj *obj) {
+    redisAssert(obj->type == REDIS_STRING &&
+                obj->encoding == REDIS_ENCODING_RAW);
+    listAddNodeTail(c->reply,obj);
+}
+
+void _ensureBufferInReplyList(redisClient *c) {
+    sds buffer = sdsnewlen(NULL,REDIS_REPLY_CHUNK_SIZE);
+    sdsupdatelen(buffer); /* sdsnewlen expects non-empty string */
+    listAddNodeTail(c->reply,createObject(REDIS_REPLY_NODE,buffer));
+}
+
+void _addReplyStringToBuffer(redisClient *c, char *s, size_t len) {
+    size_t available = 0;
+    redisAssert(len < REDIS_REPLY_CHUNK_THRESHOLD);
+    if (listLength(c->reply) > 0) {
+        robj *o = listNodeValue(listLast(c->reply));
+
+        /* Make sure to append to a reply node with enough bytes available. */
+        if (o->type == REDIS_REPLY_NODE) available = sdsavail(o->ptr);
+        if (o->type != REDIS_REPLY_NODE || len > available) {
+            _ensureBufferInReplyList(c);
+            _addReplyStringToBuffer(c,s,len);
+        } else {
+            o->ptr = sdscatlen(o->ptr,s,len);
+        }
+    } else {
+        available = c->buflen-c->bufpos;
+        if (len > available) {
+            _ensureBufferInReplyList(c);
+            _addReplyStringToBuffer(c,s,len);
+        } else {
+            memcpy(c->buf+c->bufpos,s,len);
+            c->bufpos += len;
+        }
+    }
+}
+
+void addReply(redisClient *c, robj *obj) {
+    if (_ensureFileEvent(c) != REDIS_OK) return;
     if (server.vm_enabled && obj->storage != REDIS_VM_MEMORY) {
+        /* Returns a new object with refcount 1 */
         obj = dupStringObject(obj);
-        obj->refcount = 0; /* getDecodedObject() will increment the refcount */
+    } else {
+        /* This increments the refcount. */
+        obj = getDecodedObject(obj);
+    }
+
+    if (sdslen(obj->ptr) < REDIS_REPLY_CHUNK_THRESHOLD) {
+        _addReplyStringToBuffer(c,obj->ptr,sdslen(obj->ptr));
+        decrRefCount(obj);
+    } else {
+        _addReplyObjectToList(c,obj);
     }
-    listAddNodeTail(c->reply,getDecodedObject(obj));
 }
 
 void addReplySds(redisClient *c, sds s) {
-    robj *o = createObject(REDIS_STRING,s);
-    addReply(c,o);
-    decrRefCount(o);
+    if (_ensureFileEvent(c) != REDIS_OK) return;
+    if (sdslen(s) < REDIS_REPLY_CHUNK_THRESHOLD) {
+        _addReplyStringToBuffer(c,s,sdslen(s));
+        sdsfree(s);
+    } else {
+        _addReplyObjectToList(c,createObject(REDIS_STRING,s));
+    }
 }
 
-void addReplyDouble(redisClient *c, double d) {
-    char buf[128];
+void addReplyString(redisClient *c, char *s, size_t len) {
+    if (_ensureFileEvent(c) != REDIS_OK) return;
+    if (len < REDIS_REPLY_CHUNK_THRESHOLD) {
+        _addReplyStringToBuffer(c,s,len);
+    } else {
+        _addReplyObjectToList(c,createStringObject(s,len));
+    }
+}
 
-    snprintf(buf,sizeof(buf),"%.17g",d);
-    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n%s\r\n",
-        (unsigned long) strlen(buf),buf));
+void addReplyDouble(redisClient *c, double d) {
+    char dbuf[128], sbuf[128];
+    int dlen, slen;
+    dlen = snprintf(dbuf,sizeof(dbuf),"%.17g",d);
+    slen = snprintf(sbuf,sizeof(sbuf),"$%d\r\n%s\r\n",dlen,dbuf);
+    addReplyString(c,sbuf,slen);
 }
 
-void addReplyLongLong(redisClient *c, long long ll) {
+void _addReplyLongLong(redisClient *c, long long ll, char prefix) {
     char buf[128];
-    size_t len;
-
-    if (ll == 0) {
-        addReply(c,shared.czero);
-        return;
-    } else if (ll == 1) {
-        addReply(c,shared.cone);
-        return;
-    }
-    buf[0] = ':';
+    int len;
+    buf[0] = prefix;
     len = ll2string(buf+1,sizeof(buf)-1,ll);
     buf[len+1] = '\r';
     buf[len+2] = '\n';
-    addReplySds(c,sdsnewlen(buf,len+3));
+    addReplyString(c,buf,len+3);
 }
 
-void addReplyUlong(redisClient *c, unsigned long ul) {
-    char buf[128];
-    size_t len;
+void addReplyLongLong(redisClient *c, long long ll) {
+    _addReplyLongLong(c,ll,':');
+}
 
-    if (ul == 0) {
-        addReply(c,shared.czero);
-        return;
-    } else if (ul == 1) {
-        addReply(c,shared.cone);
-        return;
-    }
-    len = snprintf(buf,sizeof(buf),":%lu\r\n",ul);
-    addReplySds(c,sdsnewlen(buf,len));
+void addReplyUlong(redisClient *c, unsigned long ul) {
+    _addReplyLongLong(c,(long long)ul,':');
 }
 
 void addReplyBulkLen(redisClient *c, robj *obj) {
-    size_t len, intlen;
-    char buf[128];
+    size_t len;
 
     if (obj->encoding == REDIS_ENCODING_RAW) {
         len = sdslen(obj->ptr);
@@ -133,11 +189,7 @@ void addReplyBulkLen(redisClient *c, robj *obj) {
             len++;
         }
     }
-    buf[0] = '$';
-    intlen = ll2string(buf+1,sizeof(buf)-1,(long long)len);
-    buf[intlen+1] = '\r';
-    buf[intlen+2] = '\n';
-    addReplySds(c,sdsnewlen(buf,intlen+3));
+    _addReplyLongLong(c,len,'$');
 }
 
 void addReplyBulk(redisClient *c, robj *obj) {
@@ -287,34 +339,6 @@ void freeClient(redisClient *c) {
     zfree(c);
 }
 
-#define GLUEREPLY_UP_TO (1024)
-static void glueReplyBuffersIfNeeded(redisClient *c) {
-    int copylen = 0;
-    char buf[GLUEREPLY_UP_TO];
-    listNode *ln;
-    listIter li;
-    robj *o;
-
-    listRewind(c->reply,&li);
-    while((ln = listNext(&li))) {
-        int objlen;
-
-        o = ln->value;
-        objlen = sdslen(o->ptr);
-        if (copylen + objlen <= GLUEREPLY_UP_TO) {
-            memcpy(buf+copylen,o->ptr,objlen);
-            copylen += objlen;
-            listDelNode(c->reply,ln);
-        } else {
-            if (copylen == 0) return;
-            break;
-        }
-    }
-    /* Now the output buffer is empty, add the new single element */
-    o = createObject(REDIS_STRING,sdsnewlen(buf,copylen));
-    listAddNodeHead(c->reply,o);
-}
-
 void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     redisClient *c = privdata;
     int nwritten = 0, totwritten = 0, objlen;
@@ -331,31 +355,48 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         return;
     }
 
-    while(listLength(c->reply)) {
-        if (server.glueoutputbuf && listLength(c->reply) > 1)
-            glueReplyBuffersIfNeeded(c);
+    while(c->bufpos > 0 || listLength(c->reply)) {
+        if (c->bufpos > 0) {
+            if (c->flags & REDIS_MASTER) {
+                /* Don't reply to a master */
+                nwritten = c->bufpos - c->sentlen;
+            } else {
+                nwritten = write(fd,c->buf+c->sentlen,c->bufpos-c->sentlen);
+                if (nwritten <= 0) break;
+            }
+            c->sentlen += nwritten;
+            totwritten += nwritten;
 
-        o = listNodeValue(listFirst(c->reply));
-        objlen = sdslen(o->ptr);
+            /* If the buffer was sent, set bufpos to zero to continue with
+             * the remainder of the reply. */
+            if (c->sentlen == c->bufpos) {
+                c->bufpos = 0;
+                c->sentlen = 0;
+            }
+        } else {
+            o = listNodeValue(listFirst(c->reply));
+            objlen = sdslen(o->ptr);
 
-        if (objlen == 0) {
-            listDelNode(c->reply,listFirst(c->reply));
-            continue;
-        }
+            if (objlen == 0) {
+                listDelNode(c->reply,listFirst(c->reply));
+                continue;
+            }
 
-        if (c->flags & REDIS_MASTER) {
-            /* Don't reply to a master */
-            nwritten = objlen - c->sentlen;
-        } else {
-            nwritten = write(fd, ((char*)o->ptr)+c->sentlen, objlen - c->sentlen);
-            if (nwritten <= 0) break;
-        }
-        c->sentlen += nwritten;
-        totwritten += nwritten;
-        /* If we fully sent the object on head go to the next one */
-        if (c->sentlen == objlen) {
-            listDelNode(c->reply,listFirst(c->reply));
-            c->sentlen = 0;
+            if (c->flags & REDIS_MASTER) {
+                /* Don't reply to a master */
+                nwritten = objlen - c->sentlen;
+            } else {
+                nwritten = write(fd, ((char*)o->ptr)+c->sentlen,objlen-c->sentlen);
+                if (nwritten <= 0) break;
+            }
+            c->sentlen += nwritten;
+            totwritten += nwritten;
+
+            /* If we fully sent the object on head go to the next one */
+            if (c->sentlen == objlen) {
+                listDelNode(c->reply,listFirst(c->reply));
+                c->sentlen = 0;
+            }
         }
         /* Note that we avoid to send more thank REDIS_MAX_WRITE_PER_EVENT
          * bytes, in a single threaded server it's a good idea to serve