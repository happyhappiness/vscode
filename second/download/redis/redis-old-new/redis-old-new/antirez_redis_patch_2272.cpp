@@ -56,6 +56,7 @@
 #include <fcntl.h>
 #include <sys/time.h>
 #include <sys/resource.h>
+#include <sys/uio.h>
 #include <limits.h>
 #include <math.h>
 
@@ -89,7 +90,12 @@
 #define REDIS_MAX_SYNC_TIME     60      /* Slave can't take more to sync */
 #define REDIS_EXPIRELOOKUPS_PER_CRON    100 /* try to expire 100 keys/second */
 #define REDIS_MAX_WRITE_PER_EVENT (1024*64)
-#define REDIS_REQUEST_MAX_SIZE  (1024*1024*256) /* max bytes in inline command */
+#define REDIS_REQUEST_MAX_SIZE (1024*1024*256) /* max bytes in inline command */
+
+/* If more then REDIS_WRITEV_THRESHOLD write packets are pending use writev */
+#define REDIS_WRITEV_THRESHOLD      3
+/* Max number of iovecs used for each writev call */
+#define REDIS_WRITEV_IOVEC_COUNT    256
 
 /* Hash table parameters */
 #define REDIS_HT_MINFILL        10      /* Minimal hash table fill 10% */
@@ -394,6 +400,7 @@ static void processInputBuffer(redisClient *c);
 static zskiplist *zslCreate(void);
 static void zslFree(zskiplist *zsl);
 static void zslInsert(zskiplist *zsl, double score, robj *obj);
+static void sendReplyToClientWritev(aeEventLoop *el, int fd, void *privdata, int mask);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -1381,6 +1388,17 @@ static void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask)
 
     if (server.glueoutputbuf && listLength(c->reply) > 1)
         glueReplyBuffersIfNeeded(c);
+
+    /* Use writev() if we have enough buffers to send */
+#if 0
+    if (listLength(c->reply) > REDIS_WRITEV_THRESHOLD && 
+            !(c->flags & REDIS_MASTER))
+    {
+        sendReplyToClientWritev(el, fd, privdata, mask);
+        return;
+    }
+#endif
+
     while(listLength(c->reply)) {
         o = listNodeValue(listFirst(c->reply));
         objlen = sdslen(o->ptr);
@@ -1428,6 +1446,84 @@ static void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask)
     }
 }
 
+static void sendReplyToClientWritev(aeEventLoop *el, int fd, void *privdata, int mask)
+{
+    redisClient *c = privdata;
+    int nwritten = 0, totwritten = 0, objlen, willwrite;
+    robj *o;
+    struct iovec iov[REDIS_WRITEV_IOVEC_COUNT];
+    int offset, ion = 0;
+    REDIS_NOTUSED(el);
+    REDIS_NOTUSED(mask);
+
+    listNode *node;
+    while (listLength(c->reply)) {
+        offset = c->sentlen;
+        ion = 0;
+        willwrite = 0;
+
+        /* fill-in the iov[] array */
+        for(node = listFirst(c->reply); node; node = listNextNode(node)) {
+            o = listNodeValue(node);
+            objlen = sdslen(o->ptr);
+
+            if (totwritten + objlen - offset > REDIS_MAX_WRITE_PER_EVENT) 
+                break;
+
+            if(ion == REDIS_WRITEV_IOVEC_COUNT)
+                break; /* no more iovecs */
+
+            iov[ion].iov_base = ((char*)o->ptr) + offset;
+            iov[ion].iov_len = objlen - offset;
+            willwrite += objlen - offset;
+            offset = 0; /* just for the first item */
+            ion++;
+        }
+
+        if(willwrite == 0)
+            break;
+
+        /* write all collected blocks at once */
+        if((nwritten = writev(fd, iov, ion)) < 0) {
+            if (errno != EAGAIN) {
+                redisLog(REDIS_DEBUG,
+                         "Error writing to client: %s", strerror(errno));
+                freeClient(c);
+                return;
+            }
+            break;
+        }
+
+        totwritten += nwritten;
+        offset = c->sentlen;
+
+        /* remove written robjs from c->reply */
+        while (nwritten && listLength(c->reply)) {
+            o = listNodeValue(listFirst(c->reply));
+            objlen = sdslen(o->ptr);
+
+            if(nwritten >= objlen - offset) {
+                listDelNode(c->reply, listFirst(c->reply));
+                nwritten -= objlen - offset;
+                c->sentlen = 0;
+            } else {
+                /* partial write */
+                c->sentlen += nwritten;
+                break;
+            }
+            offset = 0;
+        }
+    }
+
+    if (totwritten > 0) 
+        c->lastinteraction = time(NULL);
+
+    if (listLength(c->reply) == 0) {
+        c->sentlen = 0;
+        aeDeleteFileEvent(server.el,c->fd,AE_WRITABLE);
+    }
+}
+
 static struct redisCommand *lookupCommand(char *name) {
     int j = 0;
     while(cmdTable[j].name != NULL) {