     *r = rioFileIO;
     r->io.file.fp = fp;
     r->io.file.buffered = 0;
     r->io.file.autosync = 0;
 }
 
-void rioInitWithBuffer(rio *r, sds s) {
-    *r = rioBufferIO;
-    r->io.buffer.ptr = s;
-    r->io.buffer.pos = 0;
+/* ------------------- File descriptors set implementation ------------------- */
+
+/* Returns 1 or 0 for success/failure.
+ * The function returns success as long as we are able to correctly write
+ * to at least one file descriptor.
+ *
+ * When buf is NULL adn len is 0, the function performs a flush operation
+ * if there is some pending buffer, so this function is also used in order
+ * to implement rioFdsetFlush(). */
+static size_t rioFdsetWrite(rio *r, const void *buf, size_t len) {
+    ssize_t retval;
+    int j;
+    unsigned char *p = (unsigned char*) buf;
+    int doflush = (buf == NULL && len == 0);
+
+    /* To start we always append to our buffer. If it gets larger than
+     * a given size, we actually write to the sockets. */
+    if (len) {
+        r->io.fdset.buf = sdscatlen(r->io.fdset.buf,buf,len);
+        len = 0; /* Prevent entering the while belove if we don't flush. */
+        if (sdslen(r->io.fdset.buf) > REDIS_IOBUF_LEN) doflush = 1;
+    }
+
+    if (doflush) {
+        p = (unsigned char*) r->io.fdset.buf;
+        len = sdslen(r->io.fdset.buf);
+    }
+
+    /* Write in little chunchs so that when there are big writes we
+     * parallelize while the kernel is sending data in background to
+     * the TCP socket. */
+    while(len) {
+        size_t count = len < 1024 ? len : 1024;
+        int broken = 0;
+        for (j = 0; j < r->io.fdset.numfds; j++) {
+            if (r->io.fdset.state[j] != 0) {
+                /* Skip FDs alraedy in error. */
+                broken++;
+                continue;
+            }
+
+            /* Make sure to write 'count' bytes to the socket regardless
+             * of short writes. */
+            size_t nwritten = 0;
+            while(nwritten != count) {
+                retval = write(r->io.fdset.fds[j],p+nwritten,count-nwritten);
+                if (retval <= 0) {
+                    /* With blocking sockets, which is the sole user of this
+                     * rio target, EWOULDBLOCK is returned only because of
+                     * the SO_SNDTIMEO socket option, so we translate the error
+                     * into one more recognizable by the user. */
+                    if (retval == -1 && errno == EWOULDBLOCK) errno = ETIMEDOUT;
+                    break;
+                }
+                nwritten += retval;
+            }
+
+            if (nwritten != count) {
+                /* Mark this FD as broken. */
+                r->io.fdset.state[j] = errno;
+                if (r->io.fdset.state[j] == 0) r->io.fdset.state[j] = EIO;
+            }
+        }
+        if (broken == r->io.fdset.numfds) return 0; /* All the FDs in error. */
+        p += count;
+        len -= count;
+        r->io.fdset.pos += count;
+    }
+
+    if (doflush) sdsclear(r->io.fdset.buf);
+    return 1;
+}
+
+/* Returns 1 or 0 for success/failure. */
+static size_t rioFdsetRead(rio *r, void *buf, size_t len) {
+    REDIS_NOTUSED(r);
+    REDIS_NOTUSED(buf);
+    REDIS_NOTUSED(len);
+    return 0; /* Error, this target does not support reading. */
+}
+
+/* Returns read/write position in file. */
+static off_t rioFdsetTell(rio *r) {
+    return r->io.fdset.pos;
 }
 
+/* Flushes any buffer to target device if applicable. Returns 1 on success
+ * and 0 on failures. */
+static int rioFdsetFlush(rio *r) {
+    /* Our flush is implemented by the write method, that recognizes a
+     * buffer set to NULL with a count of zero as a flush request. */
+    return rioFdsetWrite(r,NULL,0);
+}
+
+static const rio rioFdsetIO = {
+    rioFdsetRead,
+    rioFdsetWrite,
+    rioFdsetTell,
+    rioFdsetFlush,
+    NULL,           /* update_checksum */
+    0,              /* current checksum */
+    0,              /* bytes read or written */
+    0,              /* read/write chunk size */
+    { { NULL, 0 } } /* union for io-specific vars */
+};
+
+void rioInitWithFdset(rio *r, int *fds, int numfds) {
+    int j;
+
+    *r = rioFdsetIO;
+    r->io.fdset.fds = zmalloc(sizeof(int)*numfds);
+    r->io.fdset.state = zmalloc(sizeof(int)*numfds);
+    memcpy(r->io.fdset.fds,fds,sizeof(int)*numfds);
+    for (j = 0; j < numfds; j++) r->io.fdset.state[j] = 0;
+    r->io.fdset.numfds = numfds;
+    r->io.fdset.pos = 0;
+    r->io.fdset.buf = sdsempty();
+}
+
+void rioFreeFdset(rio *r) {
+    zfree(r->io.fdset.fds);
+    zfree(r->io.fdset.state);
+    sdsfree(r->io.fdset.buf);
+}
+
+/* ---------------------------- Generic functions ---------------------------- */
+
 /* This function can be installed both in memory and file streams when checksum
  * computation is needed. */
 void rioGenericUpdateChecksum(rio *r, const void *buf, size_t len) {
     r->cksum = crc64(r->cksum,buf,len);
 }
 
