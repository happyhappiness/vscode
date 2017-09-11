@@ -29,6 +29,7 @@
 
 #include "redis.h"
 #include <sys/uio.h>
+#include <math.h>
 
 static void setProtocolError(redisClient *c, int pos);
 
@@ -415,9 +416,15 @@ void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
 void addReplyDouble(redisClient *c, double d) {
     char dbuf[128], sbuf[128];
     int dlen, slen;
-    dlen = snprintf(dbuf,sizeof(dbuf),"%.17g",d);
-    slen = snprintf(sbuf,sizeof(sbuf),"$%d\r\n%s\r\n",dlen,dbuf);
-    addReplyString(c,sbuf,slen);
+    if (isinf(d)) {
+        /* Libc in odd systems (Hi Solaris!) will format infinite in a
+         * different way, so better to handle it in an explicit way. */
+        addReplyBulkCString(c, d > 0 ? "inf" : "-inf");
+    } else {
+        dlen = snprintf(dbuf,sizeof(dbuf),"%.17g",d);
+        slen = snprintf(sbuf,sizeof(sbuf),"$%d\r\n%s\r\n",dlen,dbuf);
+        addReplyString(c,sbuf,slen);
+    }
 }
 
 /* Add a long long as integer reply or bulk len / multi bulk count.