@@ -1,5 +1,7 @@
 /*
  * Copyright (c) 2009-2010, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2010, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ *
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -32,6 +34,7 @@
 #include <unistd.h>
 #include <assert.h>
 #include <errno.h>
+#include <ctype.h>
 
 #include "hiredis.h"
 #include "net.h"
@@ -44,10 +47,12 @@ typedef struct redisReader {
     void *reply; /* holds temporary reply */
 
     sds buf; /* read buffer */
-    unsigned int pos; /* buffer cursor */
+    size_t pos; /* buffer cursor */
+    size_t len; /* buffer length */
 
     redisReadTask rstack[3]; /* stack of read tasks */
     int ridx; /* index of stack */
+    void *privdata; /* user-settable arbitrary field */
 } redisReader;
 
 static redisReply *createReplyObject(int type);
@@ -68,7 +73,7 @@ static redisReplyObjectFunctions defaultFunctions = {
 
 /* Create a reply object */
 static redisReply *createReplyObject(int type) {
-    redisReply *r = calloc(sizeof(*r),1);
+    redisReply *r = malloc(sizeof(*r));
 
     if (!r) redisOOM();
     r->type = type;
@@ -88,9 +93,10 @@ void freeReplyObject(void *reply) {
             if (r->element[j]) freeReplyObject(r->element[j]);
         free(r->element);
         break;
-    default:
-        if (r->str != NULL)
-            free(r->str);
+    case REDIS_REPLY_ERROR:
+    case REDIS_REPLY_STATUS:
+    case REDIS_REPLY_STRING:
+        free(r->str);
         break;
     }
     free(r);
@@ -111,7 +117,7 @@ static void *createStringObject(const redisReadTask *task, char *str, size_t len
     r->len = len;
 
     if (task->parent) {
-        redisReply *parent = task->parent;
+        redisReply *parent = task->parent->obj;
         assert(parent->type == REDIS_REPLY_ARRAY);
         parent->element[task->idx] = r;
     }
@@ -124,7 +130,7 @@ static void *createArrayObject(const redisReadTask *task, int elements) {
     if ((r->element = calloc(sizeof(redisReply*),elements)) == NULL)
         redisOOM();
     if (task->parent) {
-        redisReply *parent = task->parent;
+        redisReply *parent = task->parent->obj;
         assert(parent->type == REDIS_REPLY_ARRAY);
         parent->element[task->idx] = r;
     }
@@ -135,7 +141,7 @@ static void *createIntegerObject(const redisReadTask *task, long long value) {
     redisReply *r = createReplyObject(REDIS_REPLY_INTEGER);
     r->integer = value;
     if (task->parent) {
-        redisReply *parent = task->parent;
+        redisReply *parent = task->parent->obj;
         assert(parent->type == REDIS_REPLY_ARRAY);
         parent->element[task->idx] = r;
     }
@@ -145,7 +151,7 @@ static void *createIntegerObject(const redisReadTask *task, long long value) {
 static void *createNilObject(const redisReadTask *task) {
     redisReply *r = createReplyObject(REDIS_REPLY_NIL);
     if (task->parent) {
-        redisReply *parent = task->parent;
+        redisReply *parent = task->parent->obj;
         assert(parent->type == REDIS_REPLY_ARRAY);
         parent->element[task->idx] = r;
     }
@@ -154,36 +160,76 @@ static void *createNilObject(const redisReadTask *task) {
 
 static char *readBytes(redisReader *r, unsigned int bytes) {
     char *p;
-    if (sdslen(r->buf)-r->pos >= bytes) {
+    if (r->len-r->pos >= bytes) {
         p = r->buf+r->pos;
         r->pos += bytes;
         return p;
     }
     return NULL;
 }
 
-static char *seekNewline(char *s) {
-    /* Find pointer to \r\n without strstr */
-    while (s != NULL) {
-        s = strchr(s,'\r');
-        if (s != NULL) {
-            if (s[1] == '\n')
-                break;
-            else
-                s++;
+/* Find pointer to \r\n. */
+static char *seekNewline(char *s, size_t len) {
+    int pos = 0;
+    int _len = len-1;
+
+    /* Position should be < len-1 because the character at "pos" should be
+     * followed by a \n. Note that strchr cannot be used because it doesn't
+     * allow to search a limited length and the buffer that is being searched
+     * might not have a trailing NULL character. */
+    while (pos < _len) {
+        while(pos < _len && s[pos] != '\r') pos++;
+        if (s[pos] != '\r') {
+            /* Not found. */
+            return NULL;
         } else {
-            break;
+            if (s[pos+1] == '\n') {
+                /* Found. */
+                return s+pos;
+            } else {
+                /* Continue searching. */
+                pos++;
+            }
         }
     }
-    return s;
+    return NULL;
+}
+
+/* Read a long long value starting at *s, under the assumption that it will be
+ * terminated by \r\n. Ambiguously returns -1 for unexpected input. */
+static long long readLongLong(char *s) {
+    long long v = 0;
+    int dec, mult = 1;
+    char c;
+
+    if (*s == '-') {
+        mult = -1;
+        s++;
+    } else if (*s == '+') {
+        mult = 1;
+        s++;
+    }
+
+    while ((c = *(s++)) != '\r') {
+        dec = c - '0';
+        if (dec >= 0 && dec < 10) {
+            v *= 10;
+            v += dec;
+        } else {
+            /* Should not happen... */
+            return -1;
+        }
+    }
+
+    return mult*v;
 }
 
 static char *readLine(redisReader *r, int *_len) {
     char *p, *s;
     int len;
 
     p = r->buf+r->pos;
-    s = seekNewline(p);
+    s = seekNewline(p,(r->len-r->pos));
     if (s != NULL) {
         len = s-(r->buf+r->pos);
         r->pos += len+2; /* skip \r\n */
@@ -227,17 +273,16 @@ static int processLineItem(redisReader *r) {
     if ((p = readLine(r,&len)) != NULL) {
         if (r->fn) {
             if (cur->type == REDIS_REPLY_INTEGER) {
-                obj = r->fn->createInteger(cur,strtoll(p,NULL,10));
+                obj = r->fn->createInteger(cur,readLongLong(p));
             } else {
                 obj = r->fn->createString(cur,p,len);
             }
         } else {
             obj = (void*)(size_t)(cur->type);
         }
 
-        /* If there is no root yet, register this object as root. */
-        if (r->reply == NULL)
-            r->reply = obj;
+        /* Set reply if this is the root object. */
+        if (r->ridx == 0) r->reply = obj;
         moveToNextTask(r);
         return 0;
     }
@@ -250,32 +295,36 @@ static int processBulkItem(redisReader *r) {
     char *p, *s;
     long len;
     unsigned long bytelen;
+    int success = 0;
 
     p = r->buf+r->pos;
-    s = seekNewline(p);
+    s = seekNewline(p,r->len-r->pos);
     if (s != NULL) {
         p = r->buf+r->pos;
         bytelen = s-(r->buf+r->pos)+2; /* include \r\n */
-        len = strtol(p,NULL,10);
+        len = readLongLong(p);
 
         if (len < 0) {
             /* The nil object can always be created. */
             obj = r->fn ? r->fn->createNil(cur) :
                 (void*)REDIS_REPLY_NIL;
+            success = 1;
         } else {
             /* Only continue when the buffer contains the entire bulk item. */
             bytelen += len+2; /* include \r\n */
-            if (r->pos+bytelen <= sdslen(r->buf)) {
+            if (r->pos+bytelen <= r->len) {
                 obj = r->fn ? r->fn->createString(cur,s+2,len) :
                     (void*)REDIS_REPLY_STRING;
+                success = 1;
             }
         }
 
         /* Proceed when obj was created. */
-        if (obj != NULL) {
+        if (success) {
             r->pos += bytelen;
-            if (r->reply == NULL)
-                r->reply = obj;
+
+            /* Set reply if this is the root object. */
+            if (r->ridx == 0) r->reply = obj;
             moveToNextTask(r);
             return 0;
         }
@@ -288,9 +337,19 @@ static int processMultiBulkItem(redisReader *r) {
     void *obj;
     char *p;
     long elements;
+    int root = 0;
+
+    /* Set error for nested multi bulks with depth > 1 */
+    if (r->ridx == 2) {
+        redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
+            "No support for nested multi bulk replies with depth > 1"));
+        return -1;
+    }
 
     if ((p = readLine(r,NULL)) != NULL) {
-        elements = strtol(p,NULL,10);
+        elements = readLongLong(p);
+        root = (r->ridx == 0);
+
         if (elements == -1) {
             obj = r->fn ? r->fn->createNil(cur) :
                 (void*)REDIS_REPLY_NIL;
@@ -302,19 +361,21 @@ static int processMultiBulkItem(redisReader *r) {
             /* Modify task stack when there are more than 0 elements. */
             if (elements > 0) {
                 cur->elements = elements;
+                cur->obj = obj;
                 r->ridx++;
                 r->rstack[r->ridx].type = -1;
                 r->rstack[r->ridx].elements = -1;
-                r->rstack[r->ridx].parent = obj;
                 r->rstack[r->ridx].idx = 0;
+                r->rstack[r->ridx].obj = NULL;
+                r->rstack[r->ridx].parent = cur;
+                r->rstack[r->ridx].privdata = r->privdata;
             } else {
                 moveToNextTask(r);
             }
         }
 
-        /* Object was created, so we can always continue. */
-        if (r->reply == NULL)
-            r->reply = obj;
+        /* Set reply if this is the root object. */
+        if (root) r->reply = obj;
         return 0;
     }
     return -1;
@@ -347,7 +408,7 @@ static int processItem(redisReader *r) {
             default:
                 byte = sdscatrepr(sdsempty(),p,1);
                 redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
-                    "protocol error, got %s as reply type byte", byte));
+                    "Protocol error, got %s as reply type byte", byte));
                 sdsfree(byte);
                 return -1;
             }
@@ -368,8 +429,7 @@ static int processItem(redisReader *r) {
     case REDIS_REPLY_ARRAY:
         return processMultiBulkItem(r);
     default:
-        redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
-            "unknown item type '%d'", cur->type));
+        assert(NULL);
         return -1;
     }
 }
@@ -394,6 +454,17 @@ int redisReplyReaderSetReplyObjectFunctions(void *reader, redisReplyObjectFuncti
     return REDIS_ERR;
 }
 
+/* Set the private data field that is used in the read tasks. This argument can
+ * be used to curry arbitrary data to the custom reply object functions. */
+int redisReplyReaderSetPrivdata(void *reader, void *privdata) {
+    redisReader *r = reader;
+    if (r->reply == NULL) {
+        r->privdata = privdata;
+        return REDIS_OK;
+    }
+    return REDIS_ERR;
+}
+
 /* External libraries wrapping hiredis might need access to the temporary
  * variable while the reply is built up. When the reader contains an
  * object in between receiving some bytes to parse, this object might
@@ -437,24 +508,28 @@ void redisReplyReaderFeed(void *reader, char *buf, size_t len) {
     redisReader *r = reader;
 
     /* Copy the provided buffer. */
-    if (buf != NULL && len >= 1)
+    if (buf != NULL && len >= 1) {
         r->buf = sdscatlen(r->buf,buf,len);
+        r->len = sdslen(r->buf);
+    }
 }
 
 int redisReplyReaderGetReply(void *reader, void **reply) {
     redisReader *r = reader;
     if (reply != NULL) *reply = NULL;
 
     /* When the buffer is empty, there will never be a reply. */
-    if (sdslen(r->buf) == 0)
+    if (r->len == 0)
         return REDIS_OK;
 
     /* Set first item to process when the stack is empty. */
     if (r->ridx == -1) {
         r->rstack[0].type = -1;
         r->rstack[0].elements = -1;
-        r->rstack[0].parent = NULL;
         r->rstack[0].idx = -1;
+        r->rstack[0].obj = NULL;
+        r->rstack[0].parent = NULL;
+        r->rstack[0].privdata = r->privdata;
         r->ridx = 0;
     }
 
@@ -465,14 +540,15 @@ int redisReplyReaderGetReply(void *reader, void **reply) {
 
     /* Discard the consumed part of the buffer. */
     if (r->pos > 0) {
-        if (r->pos == sdslen(r->buf)) {
+        if (r->pos == r->len) {
             /* sdsrange has a quirck on this edge case. */
             sdsfree(r->buf);
             r->buf = sdsempty();
         } else {
-            r->buf = sdsrange(r->buf,r->pos,sdslen(r->buf));
+            r->buf = sdsrange(r->buf,r->pos,r->len);
         }
         r->pos = 0;
+        r->len = sdslen(r->buf);
     }
 
     /* Emit a reply when there is one. */
@@ -481,7 +557,7 @@ int redisReplyReaderGetReply(void *reader, void **reply) {
         r->reply = NULL;
 
         /* Destroy the buffer when it is empty and is quite large. */
-        if (sdslen(r->buf) == 0 && sdsavail(r->buf) > 16*1024) {
+        if (r->len == 0 && sdsavail(r->buf) > 16*1024) {
             sdsfree(r->buf);
             r->buf = sdsempty();
             r->pos = 0;
@@ -525,6 +601,7 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
     char *cmd = NULL; /* final command */
     int pos; /* position in final command */
     sds current; /* current argument */
+    int interpolated = 0; /* did we do interpolation on an argument? */
     char **argv = NULL;
     int argc = 0, j;
     int totlen = 0;
@@ -541,6 +618,7 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
                 if (sdslen(current) != 0) {
                     addArgument(current, &argv, &argc, &totlen);
                     current = sdsempty();
+                    interpolated = 0;
                 }
             } else {
                 current = sdscatlen(current,c,1);
@@ -549,24 +627,82 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
             switch(c[1]) {
             case 's':
                 arg = va_arg(ap,char*);
-                current = sdscat(current,arg);
+                size = strlen(arg);
+                if (size > 0)
+                    current = sdscatlen(current,arg,size);
+                interpolated = 1;
                 break;
             case 'b':
                 arg = va_arg(ap,char*);
                 size = va_arg(ap,size_t);
-                current = sdscatlen(current,arg,size);
+                if (size > 0)
+                    current = sdscatlen(current,arg,size);
+                interpolated = 1;
                 break;
             case '%':
-                cmd = sdscat(cmd,"%");
+                current = sdscat(current,"%");
                 break;
+            default:
+                /* Try to detect printf format */
+                {
+                    char _format[16];
+                    const char *_p = c+1;
+                    size_t _l = 0;
+                    va_list _cpy;
+
+                    /* Flags */
+                    if (*_p != '\0' && *_p == '#') _p++;
+                    if (*_p != '\0' && *_p == '0') _p++;
+                    if (*_p != '\0' && *_p == '-') _p++;
+                    if (*_p != '\0' && *_p == ' ') _p++;
+                    if (*_p != '\0' && *_p == '+') _p++;
+
+                    /* Field width */
+                    while (*_p != '\0' && isdigit(*_p)) _p++;
+
+                    /* Precision */
+                    if (*_p == '.') {
+                        _p++;
+                        while (*_p != '\0' && isdigit(*_p)) _p++;
+                    }
+
+                    /* Modifiers */
+                    if (*_p != '\0') {
+                        if (*_p == 'h' || *_p == 'l') {
+                            /* Allow a single repetition for these modifiers */
+                            if (_p[0] == _p[1]) _p++;
+                            _p++;
+                        }
+                    }
+
+                    /* Conversion specifier */
+                    if (*_p != '\0' && strchr("diouxXeEfFgGaA",*_p) != NULL) {
+                        _l = (_p+1)-c;
+                        if (_l < sizeof(_format)-2) {
+                            memcpy(_format,c,_l);
+                            _format[_l] = '\0';
+                            va_copy(_cpy,ap);
+                            current = sdscatvprintf(current,_format,_cpy);
+                            interpolated = 1;
+                            va_end(_cpy);
+
+                            /* Update current position (note: outer blocks
+                             * increment c twice so compensate here) */
+                            c = _p-1;
+                        }
+                    }
+
+                    /* Consume and discard vararg */
+                    va_arg(ap,void);
+                }
             }
             c++;
         }
         c++;
     }
 
     /* Add the last argument if needed */
-    if (sdslen(current) != 0) {
+    if (interpolated || sdslen(current) != 0) {
         addArgument(current, &argv, &argc, &totlen);
     } else {
         sdsfree(current);
@@ -664,7 +800,6 @@ void __redisSetError(redisContext *c, int type, const sds errstr) {
 
 static redisContext *redisContextInit() {
     redisContext *c = calloc(sizeof(redisContext),1);
-    c->fd = -1; /* quick fix for a bug that should be addressed differently */
     c->err = 0;
     c->errstr = NULL;
     c->obuf = sdsempty();
@@ -692,31 +827,27 @@ void redisFree(redisContext *c) {
 redisContext *redisConnect(const char *ip, int port) {
     redisContext *c = redisContextInit();
     c->flags |= REDIS_BLOCK;
-    c->flags |= REDIS_CONNECTED;
     redisContextConnectTcp(c,ip,port);
     return c;
 }
 
 redisContext *redisConnectNonBlock(const char *ip, int port) {
     redisContext *c = redisContextInit();
     c->flags &= ~REDIS_BLOCK;
-    c->flags |= REDIS_CONNECTED;
     redisContextConnectTcp(c,ip,port);
     return c;
 }
 
 redisContext *redisConnectUnix(const char *path) {
     redisContext *c = redisContextInit();
     c->flags |= REDIS_BLOCK;
-    c->flags |= REDIS_CONNECTED;
     redisContextConnectUnix(c,path);
     return c;
 }
 
 redisContext *redisConnectUnixNonBlock(const char *path) {
     redisContext *c = redisContextInit();
     c->flags &= ~REDIS_BLOCK;
-    c->flags |= REDIS_CONNECTED;
     redisContextConnectUnix(c,path);
     return c;
 }