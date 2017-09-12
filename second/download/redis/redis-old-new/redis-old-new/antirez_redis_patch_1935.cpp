@@ -1,5 +1,4 @@
 #include "redis.h"
-
 #include <sys/uio.h>
 
 void *dupClientReplyValue(void *o) {
@@ -12,7 +11,12 @@ int listMatchObjects(void *a, void *b) {
 }
 
 redisClient *createClient(int fd) {
-    redisClient *c = zmalloc(sizeof(*c));
+    redisClient *c;
+
+    /* Allocate more space to hold a static write buffer. */
+    c = zmalloc(sizeof(redisClient)+REDIS_REPLY_CHUNK_BYTES);
+    c->buflen = REDIS_REPLY_CHUNK_BYTES;
+    c->bufpos = 0;
 
     anetNonBlock(NULL,fd);
     anetTcpNoDelay(NULL,fd);
@@ -56,70 +60,238 @@ redisClient *createClient(int fd) {
     return c;
 }
 
-void addReply(redisClient *c, robj *obj) {
-    if (listLength(c->reply) == 0 &&
+int _ensureFileEvent(redisClient *c) {
+    if (c->fd <= 0) return REDIS_ERR;
+    if (c->bufpos == 0 && listLength(c->reply) == 0 &&
         (c->replstate == REDIS_REPL_NONE ||
          c->replstate == REDIS_REPL_ONLINE) &&
         aeCreateFileEvent(server.el, c->fd, AE_WRITABLE,
-        sendReplyToClient, c) == AE_ERR) return;
+        sendReplyToClient, c) == AE_ERR) return REDIS_ERR;
+    return REDIS_OK;
+}
 
+/* Create a duplicate of the last object in the reply list when
+ * it is not exclusively owned by the reply list. */
+robj *dupLastObjectIfNeeded(list *reply) {
+    robj *new, *cur;
+    listNode *ln;
+    redisAssert(listLength(reply) > 0);
+    ln = listLast(reply);
+    cur = listNodeValue(ln);
+    if (cur->refcount > 1) {
+        new = dupStringObject(cur);
+        decrRefCount(cur);
+        listNodeValue(ln) = new;
+    }
+    return listNodeValue(ln);
+}
+
+int _addReplyToBuffer(redisClient *c, char *s, size_t len) {
+    size_t available = c->buflen-c->bufpos;
+
+    /* If there already are entries in the reply list, we cannot
+     * add anything more to the static buffer. */
+    if (listLength(c->reply) > 0) return REDIS_ERR;
+
+    /* Check that the buffer has enough space available for this string. */
+    if (len > available) return REDIS_ERR;
+
+    memcpy(c->buf+c->bufpos,s,len);
+    c->bufpos+=len;
+    return REDIS_OK;
+}
+
+void _addReplyObjectToList(redisClient *c, robj *o) {
+    robj *tail;
+    if (listLength(c->reply) == 0) {
+        incrRefCount(o);
+        listAddNodeTail(c->reply,o);
+    } else {
+        tail = listNodeValue(listLast(c->reply));
+
+        /* Append to this object when possible. */
+        if (tail->ptr != NULL &&
+            sdslen(tail->ptr)+sdslen(o->ptr) <= REDIS_REPLY_CHUNK_BYTES)
+        {
+            tail = dupLastObjectIfNeeded(c->reply);
+            tail->ptr = sdscatlen(tail->ptr,o->ptr,sdslen(o->ptr));
+        } else {
+            incrRefCount(o);
+            listAddNodeTail(c->reply,o);
+        }
+    }
+}
+
+/* This method takes responsibility over the sds. When it is no longer
+ * needed it will be free'd, otherwise it ends up in a robj. */
+void _addReplySdsToList(redisClient *c, sds s) {
+    robj *tail;
+    if (listLength(c->reply) == 0) {
+        listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
+    } else {
+        tail = listNodeValue(listLast(c->reply));
+
+        /* Append to this object when possible. */
+        if (tail->ptr != NULL &&
+            sdslen(tail->ptr)+sdslen(s) <= REDIS_REPLY_CHUNK_BYTES)
+        {
+            tail = dupLastObjectIfNeeded(c->reply);
+            tail->ptr = sdscatlen(tail->ptr,s,sdslen(s));
+            sdsfree(s);
+        } else {
+            listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
+        }
+    }
+}
+
+void _addReplyStringToList(redisClient *c, char *s, size_t len) {
+    robj *tail;
+    if (listLength(c->reply) == 0) {
+        listAddNodeTail(c->reply,createStringObject(s,len));
+    } else {
+        tail = listNodeValue(listLast(c->reply));
+
+        /* Append to this object when possible. */
+        if (tail->ptr != NULL &&
+            sdslen(tail->ptr)+len <= REDIS_REPLY_CHUNK_BYTES)
+        {
+            tail = dupLastObjectIfNeeded(c->reply);
+            tail->ptr = sdscatlen(tail->ptr,s,len);
+        } else {
+            listAddNodeTail(c->reply,createStringObject(s,len));
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
     }
-    listAddNodeTail(c->reply,getDecodedObject(obj));
+    if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != REDIS_OK)
+        _addReplyObjectToList(c,obj);
+    decrRefCount(obj);
 }
 
 void addReplySds(redisClient *c, sds s) {
-    robj *o = createObject(REDIS_STRING,s);
-    addReply(c,o);
-    decrRefCount(o);
+    if (_ensureFileEvent(c) != REDIS_OK) {
+        /* The caller expects the sds to be free'd. */
+        sdsfree(s);
+        return;
+    }
+    if (_addReplyToBuffer(c,s,sdslen(s)) == REDIS_OK) {
+        sdsfree(s);
+    } else {
+        /* This method free's the sds when it is no longer needed. */
+        _addReplySdsToList(c,s);
+    }
 }
 
-void addReplyDouble(redisClient *c, double d) {
-    char buf[128];
+void addReplyString(redisClient *c, char *s, size_t len) {
+    if (_ensureFileEvent(c) != REDIS_OK) return;
+    if (_addReplyToBuffer(c,s,len) != REDIS_OK)
+        _addReplyStringToList(c,s,len);
+}
 
-    snprintf(buf,sizeof(buf),"%.17g",d);
-    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n%s\r\n",
-        (unsigned long) strlen(buf),buf));
+void _addReplyError(redisClient *c, char *s, size_t len) {
+    addReplyString(c,"-ERR ",5);
+    addReplyString(c,s,len);
+    addReplyString(c,"\r\n",2);
 }
 
-void addReplyLongLong(redisClient *c, long long ll) {
-    char buf[128];
-    size_t len;
+void addReplyError(redisClient *c, char *err) {
+    _addReplyError(c,err,strlen(err));
+}
 
-    if (ll == 0) {
-        addReply(c,shared.czero);
-        return;
-    } else if (ll == 1) {
-        addReply(c,shared.cone);
-        return;
+void addReplyErrorFormat(redisClient *c, const char *fmt, ...) {
+    va_list ap;
+    va_start(ap,fmt);
+    sds s = sdscatvprintf(sdsempty(),fmt,ap);
+    va_end(ap);
+    _addReplyError(c,s,sdslen(s));
+    sdsfree(s);
+}
+
+void _addReplyStatus(redisClient *c, char *s, size_t len) {
+    addReplyString(c,"+",1);
+    addReplyString(c,s,len);
+    addReplyString(c,"\r\n",2);
+}
+
+void addReplyStatus(redisClient *c, char *status) {
+    _addReplyStatus(c,status,strlen(status));
+}
+
+void addReplyStatusFormat(redisClient *c, const char *fmt, ...) {
+    va_list ap;
+    va_start(ap,fmt);
+    sds s = sdscatvprintf(sdsempty(),fmt,ap);
+    va_end(ap);
+    _addReplyStatus(c,s,sdslen(s));
+    sdsfree(s);
+}
+
+/* Adds an empty object to the reply list that will contain the multi bulk
+ * length, which is not known when this function is called. */
+void *addDeferredMultiBulkLength(redisClient *c) {
+    if (_ensureFileEvent(c) != REDIS_OK) return NULL;
+    listAddNodeTail(c->reply,createObject(REDIS_STRING,NULL));
+    return listLast(c->reply);
+}
+
+/* Populate the length object and try glueing it to the next chunk. */
+void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
+    listNode *ln = (listNode*)node;
+    robj *len, *next;
+
+    /* Abort when *node is NULL (see addDeferredMultiBulkLength). */
+    if (node == NULL) return;
+
+    len = listNodeValue(ln);
+    len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
+    if (ln->next != NULL) {
+        next = listNodeValue(ln->next);
+
+        /* Only glue when the next node is non-NULL (an sds in this case) */
+        if (next->ptr != NULL) {
+            len->ptr = sdscatlen(len->ptr,next->ptr,sdslen(next->ptr));
+            listDelNode(c->reply,ln->next);
+        }
     }
-    buf[0] = ':';
+}
+
+void addReplyDouble(redisClient *c, double d) {
+    char dbuf[128], sbuf[128];
+    int dlen, slen;
+    dlen = snprintf(dbuf,sizeof(dbuf),"%.17g",d);
+    slen = snprintf(sbuf,sizeof(sbuf),"$%d\r\n%s\r\n",dlen,dbuf);
+    addReplyString(c,sbuf,slen);
+}
+
+void _addReplyLongLong(redisClient *c, long long ll, char prefix) {
+    char buf[128];
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
+void addReplyMultiBulkLen(redisClient *c, long length) {
+    _addReplyLongLong(c,length,'*');
 }
 
 void addReplyBulkLen(redisClient *c, robj *obj) {
-    size_t len, intlen;
-    char buf[128];
+    size_t len;
 
     if (obj->encoding == REDIS_ENCODING_RAW) {
         len = sdslen(obj->ptr);
@@ -136,11 +308,7 @@ void addReplyBulkLen(redisClient *c, robj *obj) {
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
@@ -290,34 +458,6 @@ void freeClient(redisClient *c) {
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
@@ -334,31 +474,48 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
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
+
+            /* If the buffer was sent, set bufpos to zero to continue with
+             * the remainder of the reply. */
+            if (c->sentlen == c->bufpos) {
+                c->bufpos = 0;
+                c->sentlen = 0;
+            }
+        } else {
+            o = listNodeValue(listFirst(c->reply));
+            objlen = sdslen(o->ptr);
 
-        o = listNodeValue(listFirst(c->reply));
-        objlen = sdslen(o->ptr);
+            if (objlen == 0) {
+                listDelNode(c->reply,listFirst(c->reply));
+                continue;
+            }
 
-        if (objlen == 0) {
-            listDelNode(c->reply,listFirst(c->reply));
-            continue;
-        }
+            if (c->flags & REDIS_MASTER) {
+                /* Don't reply to a master */
+                nwritten = objlen - c->sentlen;
+            } else {
+                nwritten = write(fd, ((char*)o->ptr)+c->sentlen,objlen-c->sentlen);
+                if (nwritten <= 0) break;
+            }
+            c->sentlen += nwritten;
+            totwritten += nwritten;
 
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
+            /* If we fully sent the object on head go to the next one */
+            if (c->sentlen == objlen) {
+                listDelNode(c->reply,listFirst(c->reply));
+                c->sentlen = 0;
+            }
         }
         /* Note that we avoid to send more thank REDIS_MAX_WRITE_PER_EVENT
          * bytes, in a single threaded server it's a good idea to serve