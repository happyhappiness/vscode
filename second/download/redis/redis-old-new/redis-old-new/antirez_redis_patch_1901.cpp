@@ -1,5 +1,4 @@
 #include "redis.h"
-
 #include <sys/uio.h>
 
 void *dupClientReplyValue(void *o) {
@@ -12,14 +11,24 @@ int listMatchObjects(void *a, void *b) {
 }
 
 redisClient *createClient(int fd) {
-    redisClient *c = zmalloc(sizeof(*c));
+    redisClient *c = zmalloc(sizeof(redisClient));
+    c->bufpos = 0;
 
     anetNonBlock(NULL,fd);
     anetTcpNoDelay(NULL,fd);
     if (!c) return NULL;
+    if (aeCreateFileEvent(server.el,fd,AE_READABLE,
+        readQueryFromClient, c) == AE_ERR)
+    {
+        close(fd);
+        zfree(c);
+        return NULL;
+    }
+
     selectDb(c,0);
     c->fd = fd;
     c->querybuf = sdsempty();
+    c->newline = NULL;
     c->argc = 0;
     c->argv = NULL;
     c->bulklen = -1;
@@ -43,80 +52,254 @@ redisClient *createClient(int fd) {
     c->pubsub_patterns = listCreate();
     listSetFreeMethod(c->pubsub_patterns,decrRefCount);
     listSetMatchMethod(c->pubsub_patterns,listMatchObjects);
-    if (aeCreateFileEvent(server.el, c->fd, AE_READABLE,
-        readQueryFromClient, c) == AE_ERR) {
-        freeClient(c);
-        return NULL;
-    }
     listAddNodeTail(server.clients,c);
     initClientMultiState(c);
     return c;
 }
 
-void addReply(redisClient *c, robj *obj) {
-    if (listLength(c->reply) == 0 &&
+int _installWriteEvent(redisClient *c) {
+    if (c->fd <= 0) return REDIS_ERR;
+    if (c->bufpos == 0 && listLength(c->reply) == 0 &&
         (c->replstate == REDIS_REPL_NONE ||
          c->replstate == REDIS_REPL_ONLINE) &&
         aeCreateFileEvent(server.el, c->fd, AE_WRITABLE,
-        sendReplyToClient, c) == AE_ERR) return;
+        sendReplyToClient, c) == AE_ERR) return REDIS_ERR;
+    return REDIS_OK;
+}
 
-    if (server.vm_enabled && obj->storage != REDIS_VM_MEMORY) {
-        obj = dupStringObject(obj);
-        obj->refcount = 0; /* getDecodedObject() will increment the refcount */
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
     }
-    listAddNodeTail(c->reply,getDecodedObject(obj));
+    return listNodeValue(ln);
 }
 
-void addReplySds(redisClient *c, sds s) {
-    robj *o = createObject(REDIS_STRING,s);
-    addReply(c,o);
-    decrRefCount(o);
+int _addReplyToBuffer(redisClient *c, char *s, size_t len) {
+    size_t available = sizeof(c->buf)-c->bufpos;
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
 }
 
-void addReplyDouble(redisClient *c, double d) {
-    char buf[128];
+void _addReplyObjectToList(redisClient *c, robj *o) {
+    robj *tail;
+    if (listLength(c->reply) == 0) {
+        incrRefCount(o);
+        listAddNodeTail(c->reply,o);
+    } else {
+        tail = listNodeValue(listLast(c->reply));
 
-    snprintf(buf,sizeof(buf),"%.17g",d);
-    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n%s\r\n",
-        (unsigned long) strlen(buf),buf));
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
 }
 
-void addReplyLongLong(redisClient *c, long long ll) {
-    char buf[128];
-    size_t len;
+/* This method takes responsibility over the sds. When it is no longer
+ * needed it will be free'd, otherwise it ends up in a robj. */
+void _addReplySdsToList(redisClient *c, sds s) {
+    robj *tail;
+    if (listLength(c->reply) == 0) {
+        listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
+    } else {
+        tail = listNodeValue(listLast(c->reply));
 
-    if (ll == 0) {
-        addReply(c,shared.czero);
-        return;
-    } else if (ll == 1) {
-        addReply(c,shared.cone);
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
+    if (_installWriteEvent(c) != REDIS_OK) return;
+    redisAssert(!server.vm_enabled || obj->storage == REDIS_VM_MEMORY);
+
+    /* This is an important place where we can avoid copy-on-write
+     * when there is a saving child running, avoiding touching the
+     * refcount field of the object if it's not needed.
+     *
+     * If the encoding is RAW and there is room in the static buffer
+     * we'll be able to send the object to the client without
+     * messing with its page. */
+    if (obj->encoding == REDIS_ENCODING_RAW) {
+        if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != REDIS_OK)
+            _addReplyObjectToList(c,obj);
+    } else {
+        obj = getDecodedObject(obj);
+        if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != REDIS_OK)
+            _addReplyObjectToList(c,obj);
+        decrRefCount(obj);
+    }
+}
+
+void addReplySds(redisClient *c, sds s) {
+    if (_installWriteEvent(c) != REDIS_OK) {
+        /* The caller expects the sds to be free'd. */
+        sdsfree(s);
         return;
     }
-    buf[0] = ':';
+    if (_addReplyToBuffer(c,s,sdslen(s)) == REDIS_OK) {
+        sdsfree(s);
+    } else {
+        /* This method free's the sds when it is no longer needed. */
+        _addReplySdsToList(c,s);
+    }
+}
+
+void addReplyString(redisClient *c, char *s, size_t len) {
+    if (_installWriteEvent(c) != REDIS_OK) return;
+    if (_addReplyToBuffer(c,s,len) != REDIS_OK)
+        _addReplyStringToList(c,s,len);
+}
+
+void _addReplyError(redisClient *c, char *s, size_t len) {
+    addReplyString(c,"-ERR ",5);
+    addReplyString(c,s,len);
+    addReplyString(c,"\r\n",2);
+}
+
+void addReplyError(redisClient *c, char *err) {
+    _addReplyError(c,err,strlen(err));
+}
+
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
+    /* Note that we install the write event here even if the object is not
+     * ready to be sent, since we are sure that before returning to the
+     * event loop setDeferredMultiBulkLength() will be called. */
+    if (_installWriteEvent(c) != REDIS_OK) return NULL;
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
+    }
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
@@ -133,11 +316,7 @@ void addReplyBulkLen(redisClient *c, robj *obj) {
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
@@ -275,7 +454,8 @@ void freeClient(redisClient *c) {
         server.vm_blocked_clients--;
     }
     listRelease(c->io_keys);
-    /* Master/slave cleanup */
+    /* Master/slave cleanup.
+     * Case 1: we lost the connection with a slave. */
     if (c->flags & REDIS_SLAVE) {
         if (c->replstate == REDIS_REPL_SEND_BULK && c->repldbfd != -1)
             close(c->repldbfd);
@@ -284,9 +464,20 @@ void freeClient(redisClient *c) {
         redisAssert(ln != NULL);
         listDelNode(l,ln);
     }
+
+    /* Case 2: we lost the connection with the master. */
     if (c->flags & REDIS_MASTER) {
         server.master = NULL;
         server.replstate = REDIS_REPL_CONNECT;
+        /* Since we lost the connection with the master, we should also
+         * close the connection with all our slaves if we have any, so
+         * when we'll resync with the master the other slaves will sync again
+         * with us as well. Note that also when the slave is not connected
+         * to the master it will keep refusing connections by other slaves. */
+        while (listLength(server.slaves)) {
+            ln = listFirst(server.slaves);
+            freeClient((redisClient*)ln->value);
+        }
     }
     /* Release memory */
     zfree(c->argv);
@@ -295,34 +486,6 @@ void freeClient(redisClient *c) {
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
@@ -339,31 +502,48 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
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
@@ -472,6 +652,7 @@ void resetClient(redisClient *c) {
     freeClientArgv(c);
     c->bulklen = -1;
     c->multibulk = 0;
+    c->newline = NULL;
 }
 
 void closeTimedoutClients(void) {
@@ -486,6 +667,7 @@ void closeTimedoutClients(void) {
         if (server.maxidletime &&
             !(c->flags & REDIS_SLAVE) &&    /* no timeout for slaves */
             !(c->flags & REDIS_MASTER) &&   /* no timeout for masters */
+            !(c->flags & REDIS_BLOCKED) &&  /* no timeout for BLPOP */
             dictSize(c->pubsub_channels) == 0 && /* no timeout for pubsub */
             listLength(c->pubsub_patterns) == 0 &&
             (now - c->lastinteraction > server.maxidletime))
@@ -502,6 +684,8 @@ void closeTimedoutClients(void) {
 }
 
 void processInputBuffer(redisClient *c) {
+    int seeknewline = 0;
+
 again:
     /* Before to process the input buffer, make sure the client is not
      * waitig for a blocking operation such as BLPOP. Note that the first
@@ -510,15 +694,19 @@ void processInputBuffer(redisClient *c) {
      * in the input buffer the client may be blocked, and the "goto again"
      * will try to reiterate. The following line will make it return asap. */
     if (c->flags & REDIS_BLOCKED || c->flags & REDIS_IO_WAIT) return;
+
+    if (seeknewline && c->bulklen == -1) c->newline = strchr(c->querybuf,'\n');
+    seeknewline = 1;
     if (c->bulklen == -1) {
         /* Read the first line of the query */
-        char *p = strchr(c->querybuf,'\n');
         size_t querylen;
 
-        if (p) {
+        if (c->newline) {
+            char *p = c->newline;
             sds query, *argv;
             int argc, j;
 
+            c->newline = NULL;
             query = c->querybuf;
             c->querybuf = sdsempty();
             querylen = 1+(p-(query));
@@ -605,8 +793,14 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         return;
     }
     if (nread) {
+        size_t oldlen = sdslen(c->querybuf);
         c->querybuf = sdscatlen(c->querybuf, buf, nread);
         c->lastinteraction = time(NULL);
+        /* Scan this new piece of the query for the newline. We do this
+         * here in order to make sure we perform this scan just one time
+         * per piece of buffer, leading to an O(N) scan instead of O(N*N) */
+        if (c->bulklen == -1 && c->newline == NULL)
+            c->newline = strchr(c->querybuf+oldlen,'\n');
     } else {
         return;
     }