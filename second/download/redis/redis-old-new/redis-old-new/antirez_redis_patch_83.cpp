@@ -30,8 +30,9 @@
 #include "server.h"
 #include <sys/uio.h>
 #include <math.h>
+#include <ctype.h>
 
-static void setProtocolError(client *c, int pos);
+static void setProtocolError(const char *errstr, client *c, int pos);
 
 /* Return the size consumed from the allocator, for the specified SDS string,
  * including internal fragmentation. This function is used in order to compute
@@ -1039,7 +1040,7 @@ int processInlineBuffer(client *c) {
     if (newline == NULL) {
         if (sdslen(c->querybuf) > PROTO_INLINE_MAX_SIZE) {
             addReplyError(c,"Protocol error: too big inline request");
-            setProtocolError(c,0);
+            setProtocolError("too big inline request",c,0);
         }
         return C_ERR;
     }
@@ -1056,7 +1057,7 @@ int processInlineBuffer(client *c) {
     sdsfree(aux);
     if (argv == NULL) {
         addReplyError(c,"Protocol error: unbalanced quotes in request");
-        setProtocolError(c,0);
+        setProtocolError("unbalanced quotes in inline request",c,0);
         return C_ERR;
     }
 
@@ -1099,11 +1100,29 @@ int processInlineBuffer(client *c) {
 
 /* Helper function. Trims query buffer to make the function that processes
  * multi bulk requests idempotent. */
-static void setProtocolError(client *c, int pos) {
+#define PROTO_DUMP_LEN 128
+static void setProtocolError(const char *errstr, client *c, int pos) {
     if (server.verbosity <= LL_VERBOSE) {
         sds client = catClientInfoString(sdsempty(),c);
+
+        /* Sample some protocol to given an idea about what was inside. */
+        char buf[256];
+        if (sdslen(c->querybuf) < PROTO_DUMP_LEN) {
+            snprintf(buf,sizeof(buf),"Query buffer during protocol error: '%s'", c->querybuf);
+        } else {
+            snprintf(buf,sizeof(buf),"Query buffer during protocol error: '%.*s' (... more %zu bytes ...) '%.*s'", PROTO_DUMP_LEN/2, c->querybuf, sdslen(c->querybuf)-PROTO_DUMP_LEN, PROTO_DUMP_LEN/2, c->querybuf+sdslen(c->querybuf)-PROTO_DUMP_LEN/2);
+        }
+
+        /* Remove non printable chars. */
+        char *p = buf;
+        while (*p != '\0') {
+            if (!isprint(*p)) *p = '.';
+            p++;
+        }
+
+        /* Log all the client and protocol info. */
         serverLog(LL_VERBOSE,
-            "Protocol error from client: %s", client);
+            "Protocol error (%s) from client: %s. %s", errstr, client, buf);
         sdsfree(client);
     }
     c->flags |= CLIENT_CLOSE_AFTER_REPLY;
@@ -1124,7 +1143,7 @@ int processMultibulkBuffer(client *c) {
         if (newline == NULL) {
             if (sdslen(c->querybuf) > PROTO_INLINE_MAX_SIZE) {
                 addReplyError(c,"Protocol error: too big mbulk count string");
-                setProtocolError(c,0);
+                setProtocolError("too big mbulk count string",c,0);
             }
             return C_ERR;
         }
@@ -1139,7 +1158,7 @@ int processMultibulkBuffer(client *c) {
         ok = string2ll(c->querybuf+1,newline-(c->querybuf+1),&ll);
         if (!ok || ll > 1024*1024) {
             addReplyError(c,"Protocol error: invalid multibulk length");
-            setProtocolError(c,pos);
+            setProtocolError("invalid mbulk count",c,pos);
             return C_ERR;
         }
 
@@ -1165,7 +1184,7 @@ int processMultibulkBuffer(client *c) {
                 if (sdslen(c->querybuf) > PROTO_INLINE_MAX_SIZE) {
                     addReplyError(c,
                         "Protocol error: too big bulk count string");
-                    setProtocolError(c,0);
+                    setProtocolError("too big bulk count string",c,0);
                     return C_ERR;
                 }
                 break;
@@ -1179,14 +1198,14 @@ int processMultibulkBuffer(client *c) {
                 addReplyErrorFormat(c,
                     "Protocol error: expected '$', got '%c'",
                     c->querybuf[pos]);
-                setProtocolError(c,pos);
+                setProtocolError("expected $ but got something else",c,pos);
                 return C_ERR;
             }
 
             ok = string2ll(c->querybuf+pos+1,newline-(c->querybuf+pos+1),&ll);
             if (!ok || ll < 0 || ll > 512*1024*1024) {
                 addReplyError(c,"Protocol error: invalid bulk length");
-                setProtocolError(c,pos);
+                setProtocolError("invalid bulk length",c,pos);
                 return C_ERR;
             }
 