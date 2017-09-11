@@ -1,6 +1,6 @@
 /*
- * Copyright (c) 2009-2010, Salvatore Sanfilippo <antirez at gmail dot com>
- * Copyright (c) 2010, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2009-2011, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2010-2011, Pieter Noordhuis <pcnoordhuis at gmail dot com>
  *
  * All rights reserved.
  *
@@ -29,6 +29,7 @@
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
+#include "fmacros.h"
 #include <string.h>
 #include <stdlib.h>
 #include <unistd.h>
@@ -39,30 +40,15 @@
 #include "hiredis.h"
 #include "net.h"
 #include "sds.h"
-#include "util.h"
-
-typedef struct redisReader {
-    struct redisReplyObjectFunctions *fn;
-    sds error; /* holds optional error */
-    void *reply; /* holds temporary reply */
-
-    sds buf; /* read buffer */
-    size_t pos; /* buffer cursor */
-    size_t len; /* buffer length */
-
-    redisReadTask rstack[9]; /* stack of read tasks */
-    int ridx; /* index of stack */
-    void *privdata; /* user-settable arbitrary field */
-} redisReader;
 
 static redisReply *createReplyObject(int type);
 static void *createStringObject(const redisReadTask *task, char *str, size_t len);
 static void *createArrayObject(const redisReadTask *task, int elements);
 static void *createIntegerObject(const redisReadTask *task, long long value);
 static void *createNilObject(const redisReadTask *task);
-static void redisSetReplyReaderError(redisReader *r, sds err);
 
-/* Default set of functions to build the reply. */
+/* Default set of functions to build the reply. Keep in mind that such a
+ * function returning NULL is interpreted as OOM. */
 static redisReplyObjectFunctions defaultFunctions = {
     createStringObject,
     createArrayObject,
@@ -73,9 +59,11 @@ static redisReplyObjectFunctions defaultFunctions = {
 
 /* Create a reply object */
 static redisReply *createReplyObject(int type) {
-    redisReply *r = malloc(sizeof(*r));
+    redisReply *r = calloc(1,sizeof(*r));
+
+    if (r == NULL)
+        return NULL;
 
-    if (!r) redisOOM();
     r->type = type;
     return r;
 }
@@ -89,75 +77,175 @@ void freeReplyObject(void *reply) {
     case REDIS_REPLY_INTEGER:
         break; /* Nothing to free */
     case REDIS_REPLY_ARRAY:
-        for (j = 0; j < r->elements; j++)
-            if (r->element[j]) freeReplyObject(r->element[j]);
-        free(r->element);
+        if (r->element != NULL) {
+            for (j = 0; j < r->elements; j++)
+                if (r->element[j] != NULL)
+                    freeReplyObject(r->element[j]);
+            free(r->element);
+        }
         break;
     case REDIS_REPLY_ERROR:
     case REDIS_REPLY_STATUS:
     case REDIS_REPLY_STRING:
-        free(r->str);
+        if (r->str != NULL)
+            free(r->str);
         break;
     }
     free(r);
 }
 
 static void *createStringObject(const redisReadTask *task, char *str, size_t len) {
-    redisReply *r = createReplyObject(task->type);
-    char *value = malloc(len+1);
-    if (!value) redisOOM();
-    assert(task->type == REDIS_REPLY_ERROR ||
+    redisReply *r, *parent;
+    char *buf;
+
+    r = createReplyObject(task->type);
+    if (r == NULL)
+        return NULL;
+
+    buf = malloc(len+1);
+    if (buf == NULL) {
+        freeReplyObject(r);
+        return NULL;
+    }
+
+    assert(task->type == REDIS_REPLY_ERROR  ||
            task->type == REDIS_REPLY_STATUS ||
            task->type == REDIS_REPLY_STRING);
 
     /* Copy string value */
-    memcpy(value,str,len);
-    value[len] = '\0';
-    r->str = value;
+    memcpy(buf,str,len);
+    buf[len] = '\0';
+    r->str = buf;
     r->len = len;
 
     if (task->parent) {
-        redisReply *parent = task->parent->obj;
+        parent = task->parent->obj;
         assert(parent->type == REDIS_REPLY_ARRAY);
         parent->element[task->idx] = r;
     }
     return r;
 }
 
 static void *createArrayObject(const redisReadTask *task, int elements) {
-    redisReply *r = createReplyObject(REDIS_REPLY_ARRAY);
+    redisReply *r, *parent;
+
+    r = createReplyObject(REDIS_REPLY_ARRAY);
+    if (r == NULL)
+        return NULL;
+
+    if (elements > 0) {
+        r->element = calloc(elements,sizeof(redisReply*));
+        if (r->element == NULL) {
+            freeReplyObject(r);
+            return NULL;
+        }
+    }
+
     r->elements = elements;
-    if ((r->element = calloc(sizeof(redisReply*),elements)) == NULL)
-        redisOOM();
+
     if (task->parent) {
-        redisReply *parent = task->parent->obj;
+        parent = task->parent->obj;
         assert(parent->type == REDIS_REPLY_ARRAY);
         parent->element[task->idx] = r;
     }
     return r;
 }
 
 static void *createIntegerObject(const redisReadTask *task, long long value) {
-    redisReply *r = createReplyObject(REDIS_REPLY_INTEGER);
+    redisReply *r, *parent;
+
+    r = createReplyObject(REDIS_REPLY_INTEGER);
+    if (r == NULL)
+        return NULL;
+
     r->integer = value;
+
     if (task->parent) {
-        redisReply *parent = task->parent->obj;
+        parent = task->parent->obj;
         assert(parent->type == REDIS_REPLY_ARRAY);
         parent->element[task->idx] = r;
     }
     return r;
 }
 
 static void *createNilObject(const redisReadTask *task) {
-    redisReply *r = createReplyObject(REDIS_REPLY_NIL);
+    redisReply *r, *parent;
+
+    r = createReplyObject(REDIS_REPLY_NIL);
+    if (r == NULL)
+        return NULL;
+
     if (task->parent) {
-        redisReply *parent = task->parent->obj;
+        parent = task->parent->obj;
         assert(parent->type == REDIS_REPLY_ARRAY);
         parent->element[task->idx] = r;
     }
     return r;
 }
 
+static void __redisReaderSetError(redisReader *r, int type, const char *str) {
+    size_t len;
+
+    if (r->reply != NULL && r->fn && r->fn->freeObject) {
+        r->fn->freeObject(r->reply);
+        r->reply = NULL;
+    }
+
+    /* Clear input buffer on errors. */
+    if (r->buf != NULL) {
+        sdsfree(r->buf);
+        r->buf = NULL;
+        r->pos = r->len = 0;
+    }
+
+    /* Reset task stack. */
+    r->ridx = -1;
+
+    /* Set error. */
+    r->err = type;
+    len = strlen(str);
+    len = len < (sizeof(r->errstr)-1) ? len : (sizeof(r->errstr)-1);
+    memcpy(r->errstr,str,len);
+    r->errstr[len] = '\0';
+}
+
+static size_t chrtos(char *buf, size_t size, char byte) {
+    size_t len = 0;
+
+    switch(byte) {
+    case '\\':
+    case '"':
+        len = snprintf(buf,size,"\"\\%c\"",byte);
+        break;
+    case '\n': len = snprintf(buf,size,"\"\\n\""); break;
+    case '\r': len = snprintf(buf,size,"\"\\r\""); break;
+    case '\t': len = snprintf(buf,size,"\"\\t\""); break;
+    case '\a': len = snprintf(buf,size,"\"\\a\""); break;
+    case '\b': len = snprintf(buf,size,"\"\\b\""); break;
+    default:
+        if (isprint(byte))
+            len = snprintf(buf,size,"\"%c\"",byte);
+        else
+            len = snprintf(buf,size,"\"\\x%02x\"",(unsigned char)byte);
+        break;
+    }
+
+    return len;
+}
+
+static void __redisReaderSetErrorProtocolByte(redisReader *r, char byte) {
+    char cbuf[8], sbuf[128];
+
+    chrtos(cbuf,sizeof(cbuf),byte);
+    snprintf(sbuf,sizeof(sbuf),
+        "Protocol error, got %s as reply type byte", cbuf);
+    __redisReaderSetError(r,REDIS_ERR_PROTOCOL,sbuf);
+}
+
+static void __redisReaderSetErrorOOM(redisReader *r) {
+    __redisReaderSetError(r,REDIS_ERR_OOM,"Out of memory");
+}
+
 static char *readBytes(redisReader *r, unsigned int bytes) {
     char *p;
     if (r->len-r->pos >= bytes) {
@@ -284,12 +372,18 @@ static int processLineItem(redisReader *r) {
                 obj = (void*)(size_t)(cur->type);
         }
 
+        if (obj == NULL) {
+            __redisReaderSetErrorOOM(r);
+            return REDIS_ERR;
+        }
+
         /* Set reply if this is the root object. */
         if (r->ridx == 0) r->reply = obj;
         moveToNextTask(r);
-        return 0;
+        return REDIS_OK;
     }
-    return -1;
+
+    return REDIS_ERR;
 }
 
 static int processBulkItem(redisReader *r) {
@@ -328,15 +422,21 @@ static int processBulkItem(redisReader *r) {
 
         /* Proceed when obj was created. */
         if (success) {
+            if (obj == NULL) {
+                __redisReaderSetErrorOOM(r);
+                return REDIS_ERR;
+            }
+
             r->pos += bytelen;
 
             /* Set reply if this is the root object. */
             if (r->ridx == 0) r->reply = obj;
             moveToNextTask(r);
-            return 0;
+            return REDIS_OK;
         }
     }
-    return -1;
+
+    return REDIS_ERR;
 }
 
 static int processMultiBulkItem(redisReader *r) {
@@ -346,11 +446,11 @@ static int processMultiBulkItem(redisReader *r) {
     long elements;
     int root = 0;
 
-    /* Set error for nested multi bulks with depth > 1 */
-    if (r->ridx == 8) {
-        redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
-            "No support for nested multi bulk replies with depth > 7"));
-        return -1;
+    /* Set error for nested multi bulks with depth > 2 */
+    if (r->ridx == 3) {
+        __redisReaderSetError(r,REDIS_ERR_PROTOCOL,
+            "No support for nested multi bulk replies with depth > 2");
+        return REDIS_ERR;
     }
 
     if ((p = readLine(r,NULL)) != NULL) {
@@ -362,13 +462,24 @@ static int processMultiBulkItem(redisReader *r) {
                 obj = r->fn->createNil(cur);
             else
                 obj = (void*)REDIS_REPLY_NIL;
+
+            if (obj == NULL) {
+                __redisReaderSetErrorOOM(r);
+                return REDIS_ERR;
+            }
+
             moveToNextTask(r);
         } else {
             if (r->fn && r->fn->createArray)
                 obj = r->fn->createArray(cur,elements);
             else
                 obj = (void*)REDIS_REPLY_ARRAY;
 
+            if (obj == NULL) {
+                __redisReaderSetErrorOOM(r);
+                return REDIS_ERR;
+            }
+
             /* Modify task stack when there are more than 0 elements. */
             if (elements > 0) {
                 cur->elements = elements;
@@ -387,15 +498,15 @@ static int processMultiBulkItem(redisReader *r) {
 
         /* Set reply if this is the root object. */
         if (root) r->reply = obj;
-        return 0;
+        return REDIS_OK;
     }
-    return -1;
+
+    return REDIS_ERR;
 }
 
 static int processItem(redisReader *r) {
     redisReadTask *cur = &(r->rstack[r->ridx]);
     char *p;
-    sds byte;
 
     /* check if we need to read type */
     if (cur->type < 0) {
@@ -417,15 +528,12 @@ static int processItem(redisReader *r) {
                 cur->type = REDIS_REPLY_ARRAY;
                 break;
             default:
-                byte = sdscatrepr(sdsempty(),p,1);
-                redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
-                    "Protocol error, got %s as reply type byte", byte));
-                sdsfree(byte);
-                return -1;
+                __redisReaderSetErrorProtocolByte(r,*p);
+                return REDIS_ERR;
             }
         } else {
             /* could not consume 1 byte */
-            return -1;
+            return REDIS_ERR;
         }
     }
 
@@ -441,101 +549,78 @@ static int processItem(redisReader *r) {
         return processMultiBulkItem(r);
     default:
         assert(NULL);
-        return -1;
+        return REDIS_ERR; /* Avoid warning. */
     }
 }
 
-void *redisReplyReaderCreate(void) {
-    redisReader *r = calloc(sizeof(redisReader),1);
-    r->error = NULL;
-    r->fn = &defaultFunctions;
-    r->buf = sdsempty();
-    r->ridx = -1;
-    return r;
-}
+redisReader *redisReaderCreate(void) {
+    redisReader *r;
 
-/* Set the function set to build the reply. Returns REDIS_OK when there
- * is no temporary object and it can be set, REDIS_ERR otherwise. */
-int redisReplyReaderSetReplyObjectFunctions(void *reader, redisReplyObjectFunctions *fn) {
-    redisReader *r = reader;
-    if (r->reply == NULL) {
-        r->fn = fn;
-        return REDIS_OK;
-    }
-    return REDIS_ERR;
-}
+    r = calloc(sizeof(redisReader),1);
+    if (r == NULL)
+        return NULL;
 
-/* Set the private data field that is used in the read tasks. This argument can
- * be used to curry arbitrary data to the custom reply object functions. */
-int redisReplyReaderSetPrivdata(void *reader, void *privdata) {
-    redisReader *r = reader;
-    if (r->reply == NULL) {
-        r->privdata = privdata;
-        return REDIS_OK;
+    r->err = 0;
+    r->errstr[0] = '\0';
+    r->fn = &defaultFunctions;
+    r->buf = sdsempty();
+    if (r->buf == NULL) {
+        free(r);
+        return NULL;
     }
-    return REDIS_ERR;
-}
 
-/* External libraries wrapping hiredis might need access to the temporary
- * variable while the reply is built up. When the reader contains an
- * object in between receiving some bytes to parse, this object might
- * otherwise be free'd by garbage collection. */
-void *redisReplyReaderGetObject(void *reader) {
-    redisReader *r = reader;
-    return r->reply;
+    r->ridx = -1;
+    return r;
 }
 
-void redisReplyReaderFree(void *reader) {
-    redisReader *r = reader;
-    if (r->error != NULL)
-        sdsfree(r->error);
-    if (r->reply != NULL && r->fn)
+void redisReaderFree(redisReader *r) {
+    if (r->reply != NULL && r->fn && r->fn->freeObject)
         r->fn->freeObject(r->reply);
     if (r->buf != NULL)
         sdsfree(r->buf);
     free(r);
 }
 
-static void redisSetReplyReaderError(redisReader *r, sds err) {
-    if (r->reply != NULL)
-        r->fn->freeObject(r->reply);
-
-    /* Clear remaining buffer when we see a protocol error. */
-    if (r->buf != NULL) {
-        sdsfree(r->buf);
-        r->buf = sdsempty();
-        r->pos = r->len = 0;
-    }
-    r->ridx = -1;
-    r->error = err;
-}
-
-char *redisReplyReaderGetError(void *reader) {
-    redisReader *r = reader;
-    return r->error;
-}
+int redisReaderFeed(redisReader *r, const char *buf, size_t len) {
+    sds newbuf;
 
-void redisReplyReaderFeed(void *reader, const char *buf, size_t len) {
-    redisReader *r = reader;
+    /* Return early when this reader is in an erroneous state. */
+    if (r->err)
+        return REDIS_ERR;
 
     /* Copy the provided buffer. */
     if (buf != NULL && len >= 1) {
-#if 0
         /* Destroy internal buffer when it is empty and is quite large. */
         if (r->len == 0 && sdsavail(r->buf) > 16*1024) {
             sdsfree(r->buf);
             r->buf = sdsempty();
             r->pos = 0;
+
+            /* r->buf should not be NULL since we just free'd a larger one. */
+            assert(r->buf != NULL);
+        }
+
+        newbuf = sdscatlen(r->buf,buf,len);
+        if (newbuf == NULL) {
+            __redisReaderSetErrorOOM(r);
+            return REDIS_ERR;
         }
-#endif
-        r->buf = sdscatlen(r->buf,buf,len);
+
+        r->buf = newbuf;
         r->len = sdslen(r->buf);
     }
+
+    return REDIS_OK;
 }
 
-int redisReplyReaderGetReply(void *reader, void **reply) {
-    redisReader *r = reader;
-    if (reply != NULL) *reply = NULL;
+int redisReaderGetReply(redisReader *r, void **reply) {
+    /* Default target pointer to NULL. */
+    if (reply != NULL)
+        *reply = NULL;
+
+    /* Return early when this reader is in an erroneous state. */
+    if (r->err)
+        return REDIS_ERR;
 
     /* When the buffer is empty, there will never be a reply. */
     if (r->len == 0)
@@ -554,9 +639,13 @@ int redisReplyReaderGetReply(void *reader, void **reply) {
 
     /* Process items in reply. */
     while (r->ridx >= 0)
-        if (processItem(r) < 0)
+        if (processItem(r) != REDIS_OK)
             break;
 
+    /* Return ASAP when an error occurred. */
+    if (r->err)
+        return REDIS_ERR;
+
     /* Discard part of the buffer when we've consumed at least 1k, to avoid
      * doing unnecessary calls to memmove() in sds.c. */
     if (r->pos >= 1024) {
@@ -567,15 +656,9 @@ int redisReplyReaderGetReply(void *reader, void **reply) {
 
     /* Emit a reply when there is one. */
     if (r->ridx == -1) {
-        void *aux = r->reply;
+        if (reply != NULL)
+            *reply = r->reply;
         r->reply = NULL;
-
-        /* Check if there actually *is* a reply. */
-        if (r->error != NULL) {
-            return REDIS_ERR;
-        } else {
-            if (reply != NULL) *reply = aux;
-        }
     }
     return REDIS_OK;
 }
@@ -594,63 +677,79 @@ static int intlen(int i) {
     return len;
 }
 
-/* Helper function for redisvFormatCommand(). */
-static void addArgument(sds a, char ***argv, int *argc, int *totlen) {
-    (*argc)++;
-    if ((*argv = realloc(*argv, sizeof(char*)*(*argc))) == NULL) redisOOM();
-    if (totlen) *totlen = *totlen+1+intlen(sdslen(a))+2+sdslen(a)+2;
-    (*argv)[(*argc)-1] = a;
+/* Helper that calculates the bulk length given a certain string length. */
+static size_t bulklen(size_t len) {
+    return 1+intlen(len)+2+len+2;
 }
 
 int redisvFormatCommand(char **target, const char *format, va_list ap) {
-    size_t size;
-    const char *arg, *c = format;
+    const char *c = format;
     char *cmd = NULL; /* final command */
     int pos; /* position in final command */
-    sds current; /* current argument */
+    sds curarg, newarg; /* current argument */
     int touched = 0; /* was the current argument touched? */
-    char **argv = NULL;
-    int argc = 0, j;
+    char **curargv = NULL, **newargv = NULL;
+    int argc = 0;
     int totlen = 0;
+    int j;
 
     /* Abort if there is not target to set */
     if (target == NULL)
         return -1;
 
     /* Build the command string accordingly to protocol */
-    current = sdsempty();
+    curarg = sdsempty();
+    if (curarg == NULL)
+        return -1;
+
     while(*c != '\0') {
         if (*c != '%' || c[1] == '\0') {
             if (*c == ' ') {
                 if (touched) {
-                    addArgument(current, &argv, &argc, &totlen);
-                    current = sdsempty();
+                    newargv = realloc(curargv,sizeof(char*)*(argc+1));
+                    if (newargv == NULL) goto err;
+                    curargv = newargv;
+                    curargv[argc++] = curarg;
+                    totlen += bulklen(sdslen(curarg));
+
+                    /* curarg is put in argv so it can be overwritten. */
+                    curarg = sdsempty();
+                    if (curarg == NULL) goto err;
                     touched = 0;
                 }
             } else {
-                current = sdscatlen(current,c,1);
+                newarg = sdscatlen(curarg,c,1);
+                if (newarg == NULL) goto err;
+                curarg = newarg;
                 touched = 1;
             }
         } else {
+            char *arg;
+            size_t size;
+
+            /* Set newarg so it can be checked even if it is not touched. */
+            newarg = curarg;
+
             switch(c[1]) {
             case 's':
                 arg = va_arg(ap,char*);
                 size = strlen(arg);
                 if (size > 0)
-                    current = sdscatlen(current,arg,size);
+                    newarg = sdscatlen(curarg,arg,size);
                 break;
             case 'b':
                 arg = va_arg(ap,char*);
                 size = va_arg(ap,size_t);
                 if (size > 0)
-                    current = sdscatlen(current,arg,size);
+                    newarg = sdscatlen(curarg,arg,size);
                 break;
             case '%':
-                current = sdscat(current,"%");
+                newarg = sdscat(curarg,"%");
                 break;
             default:
                 /* Try to detect printf format */
                 {
+                    static const char intfmts[] = "diouxX";
                     char _format[16];
                     const char *_p = c+1;
                     size_t _l = 0;
@@ -672,35 +771,85 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
                         while (*_p != '\0' && isdigit(*_p)) _p++;
                     }
 
-                    /* Modifiers */
-                    if (*_p != '\0') {
-                        if (*_p == 'h' || *_p == 'l') {
-                            /* Allow a single repetition for these modifiers */
-                            if (_p[0] == _p[1]) _p++;
-                            _p++;
+                    /* Copy va_list before consuming with va_arg */
+                    va_copy(_cpy,ap);
+
+                    /* Integer conversion (without modifiers) */
+                    if (strchr(intfmts,*_p) != NULL) {
+                        va_arg(ap,int);
+                        goto fmt_valid;
+                    }
+
+                    /* Double conversion (without modifiers) */
+                    if (strchr("eEfFgGaA",*_p) != NULL) {
+                        va_arg(ap,double);
+                        goto fmt_valid;
+                    }
+
+                    /* Size: char */
+                    if (_p[0] == 'h' && _p[1] == 'h') {
+                        _p += 2;
+                        if (*_p != '\0' && strchr(intfmts,*_p) != NULL) {
+                            va_arg(ap,int); /* char gets promoted to int */
+                            goto fmt_valid;
                         }
+                        goto fmt_invalid;
                     }
 
-                    /* Conversion specifier */
-                    if (*_p != '\0' && strchr("diouxXeEfFgGaA",*_p) != NULL) {
-                        _l = (_p+1)-c;
-                        if (_l < sizeof(_format)-2) {
-                            memcpy(_format,c,_l);
-                            _format[_l] = '\0';
-                            va_copy(_cpy,ap);
-                            current = sdscatvprintf(current,_format,_cpy);
-                            va_end(_cpy);
-
-                            /* Update current position (note: outer blocks
-                             * increment c twice so compensate here) */
-                            c = _p-1;
+                    /* Size: short */
+                    if (_p[0] == 'h') {
+                        _p += 1;
+                        if (*_p != '\0' && strchr(intfmts,*_p) != NULL) {
+                            va_arg(ap,int); /* short gets promoted to int */
+                            goto fmt_valid;
                         }
+                        goto fmt_invalid;
                     }
 
-                    /* Consume and discard vararg */
-                    va_arg(ap,void);
+                    /* Size: long long */
+                    if (_p[0] == 'l' && _p[1] == 'l') {
+                        _p += 2;
+                        if (*_p != '\0' && strchr(intfmts,*_p) != NULL) {
+                            va_arg(ap,long long);
+                            goto fmt_valid;
+                        }
+                        goto fmt_invalid;
+                    }
+
+                    /* Size: long */
+                    if (_p[0] == 'l') {
+                        _p += 1;
+                        if (*_p != '\0' && strchr(intfmts,*_p) != NULL) {
+                            va_arg(ap,long);
+                            goto fmt_valid;
+                        }
+                        goto fmt_invalid;
+                    }
+
+                fmt_invalid:
+                    va_end(_cpy);
+                    goto err;
+
+                fmt_valid:
+                    _l = (_p+1)-c;
+                    if (_l < sizeof(_format)-2) {
+                        memcpy(_format,c,_l);
+                        _format[_l] = '\0';
+                        newarg = sdscatvprintf(curarg,_format,_cpy);
+
+                        /* Update current position (note: outer blocks
+                         * increment c twice so compensate here) */
+                        c = _p-1;
+                    }
+
+                    va_end(_cpy);
+                    break;
                 }
             }
+
+            if (newarg == NULL) goto err;
+            curarg = newarg;
+
             touched = 1;
             c++;
         }
@@ -709,31 +858,55 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
 
     /* Add the last argument if needed */
     if (touched) {
-        addArgument(current, &argv, &argc, &totlen);
+        newargv = realloc(curargv,sizeof(char*)*(argc+1));
+        if (newargv == NULL) goto err;
+        curargv = newargv;
+        curargv[argc++] = curarg;
+        totlen += bulklen(sdslen(curarg));
     } else {
-        sdsfree(current);
+        sdsfree(curarg);
     }
 
+    /* Clear curarg because it was put in curargv or was free'd. */
+    curarg = NULL;
+
     /* Add bytes needed to hold multi bulk count */
     totlen += 1+intlen(argc)+2;
 
     /* Build the command at protocol level */
     cmd = malloc(totlen+1);
-    if (!cmd) redisOOM();
+    if (cmd == NULL) goto err;
+
     pos = sprintf(cmd,"*%d\r\n",argc);
     for (j = 0; j < argc; j++) {
-        pos += sprintf(cmd+pos,"$%zu\r\n",sdslen(argv[j]));
-        memcpy(cmd+pos,argv[j],sdslen(argv[j]));
-        pos += sdslen(argv[j]);
-        sdsfree(argv[j]);
+        pos += sprintf(cmd+pos,"$%zu\r\n",sdslen(curargv[j]));
+        memcpy(cmd+pos,curargv[j],sdslen(curargv[j]));
+        pos += sdslen(curargv[j]);
+        sdsfree(curargv[j]);
         cmd[pos++] = '\r';
         cmd[pos++] = '\n';
     }
     assert(pos == totlen);
-    free(argv);
-    cmd[totlen] = '\0';
+    cmd[pos] = '\0';
+
+    free(curargv);
     *target = cmd;
     return totlen;
+
+err:
+    while(argc--)
+        sdsfree(curargv[argc]);
+    free(curargv);
+
+    if (curarg != NULL)
+        sdsfree(curarg);
+
+    /* No need to check cmd since it is the last statement that can fail,
+     * but do it anyway to be as defensive as possible. */
+    if (cmd != NULL)
+        free(cmd);
+
+    return -1;
 }
 
 /* Format a command according to the Redis protocol. This function
@@ -772,12 +945,14 @@ int redisFormatCommandArgv(char **target, int argc, const char **argv, const siz
     totlen = 1+intlen(argc)+2;
     for (j = 0; j < argc; j++) {
         len = argvlen ? argvlen[j] : strlen(argv[j]);
-        totlen += 1+intlen(len)+2+len+2;
+        totlen += bulklen(len);
     }
 
     /* Build the command at protocol level */
     cmd = malloc(totlen+1);
-    if (!cmd) redisOOM();
+    if (cmd == NULL)
+        return -1;
+
     pos = sprintf(cmd,"*%d\r\n",argc);
     for (j = 0; j < argc; j++) {
         len = argvlen ? argvlen[j] : strlen(argv[j]);
@@ -788,41 +963,49 @@ int redisFormatCommandArgv(char **target, int argc, const char **argv, const siz
         cmd[pos++] = '\n';
     }
     assert(pos == totlen);
-    cmd[totlen] = '\0';
+    cmd[pos] = '\0';
+
     *target = cmd;
     return totlen;
 }
 
-void __redisSetError(redisContext *c, int type, const sds errstr) {
+void __redisSetError(redisContext *c, int type, const char *str) {
+    size_t len;
+
     c->err = type;
-    if (errstr != NULL) {
-        c->errstr = errstr;
+    if (str != NULL) {
+        len = strlen(str);
+        len = len < (sizeof(c->errstr)-1) ? len : (sizeof(c->errstr)-1);
+        memcpy(c->errstr,str,len);
+        c->errstr[len] = '\0';
     } else {
         /* Only REDIS_ERR_IO may lack a description! */
         assert(type == REDIS_ERR_IO);
-        c->errstr = sdsnew(strerror(errno));
+        strerror_r(errno,c->errstr,sizeof(c->errstr));
     }
 }
 
 static redisContext *redisContextInit(void) {
-    redisContext *c = calloc(sizeof(redisContext),1);
+    redisContext *c;
+
+    c = calloc(1,sizeof(redisContext));
+    if (c == NULL)
+        return NULL;
+
     c->err = 0;
-    c->errstr = NULL;
+    c->errstr[0] = '\0';
     c->obuf = sdsempty();
-    c->fn = &defaultFunctions;
-    c->reader = NULL;
+    c->reader = redisReaderCreate();
     return c;
 }
 
 void redisFree(redisContext *c) {
     if (c->fd > 0)
         close(c->fd);
-    if (c->errstr != NULL)
-        sdsfree(c->errstr);
     if (c->obuf != NULL)
         sdsfree(c->obuf);
     if (c->reader != NULL)
-        redisReplyReaderFree(c->reader);
+        redisReaderFree(c->reader);
     free(c);
 }
 
@@ -878,32 +1061,20 @@ int redisSetTimeout(redisContext *c, struct timeval tv) {
     return REDIS_ERR;
 }
 
-/* Set the replyObjectFunctions to use. Returns REDIS_ERR when the reader
- * was already initialized and the function set could not be re-set.
- * Return REDIS_OK when they could be set. */
-int redisSetReplyObjectFunctions(redisContext *c, redisReplyObjectFunctions *fn) {
-    if (c->reader != NULL)
-        return REDIS_ERR;
-    c->fn = fn;
-    return REDIS_OK;
-}
-
-/* Helper function to lazily create a reply reader. */
-static void __redisCreateReplyReader(redisContext *c) {
-    if (c->reader == NULL) {
-        c->reader = redisReplyReaderCreate();
-        assert(redisReplyReaderSetReplyObjectFunctions(c->reader,c->fn) == REDIS_OK);
-    }
-}
-
 /* Use this function to handle a read event on the descriptor. It will try
  * and read some bytes from the socket and feed them to the reply parser.
  *
  * After this function is called, you may use redisContextReadReply to
  * see if there is a reply available. */
 int redisBufferRead(redisContext *c) {
-    char buf[1024*16];
-    int nread = read(c->fd,buf,sizeof(buf));
+    char buf[2048];
+    int nread;
+
+    /* Return early when the context has seen an error. */
+    if (c->err)
+        return REDIS_ERR;
+
+    nread = read(c->fd,buf,sizeof(buf));
     if (nread == -1) {
         if (errno == EAGAIN && !(c->flags & REDIS_BLOCK)) {
             /* Try again later */
@@ -912,12 +1083,13 @@ int redisBufferRead(redisContext *c) {
             return REDIS_ERR;
         }
     } else if (nread == 0) {
-        __redisSetError(c,REDIS_ERR_EOF,
-            sdsnew("Server closed the connection"));
+        __redisSetError(c,REDIS_ERR_EOF,"Server closed the connection");
         return REDIS_ERR;
     } else {
-        __redisCreateReplyReader(c);
-        redisReplyReaderFeed(c->reader,buf,nread);
+        if (redisReaderFeed(c->reader,buf,nread) != REDIS_OK) {
+            __redisSetError(c,c->reader->err,c->reader->errstr);
+            return REDIS_ERR;
+        }
     }
     return REDIS_OK;
 }
@@ -926,13 +1098,18 @@ int redisBufferRead(redisContext *c) {
  *
  * Returns REDIS_OK when the buffer is empty, or (a part of) the buffer was
  * succesfully written to the socket. When the buffer is empty after the
- * write operation, "wdone" is set to 1 (if given).
+ * write operation, "done" is set to 1 (if given).
  *
  * Returns REDIS_ERR if an error occured trying to write and sets
- * c->error to hold the appropriate error string.
+ * c->errstr to hold the appropriate error string.
  */
 int redisBufferWrite(redisContext *c, int *done) {
     int nwritten;
+
+    /* Return early when the context has seen an error. */
+    if (c->err)
+        return REDIS_ERR;
+
     if (sdslen(c->obuf) > 0) {
         nwritten = write(c->fd,c->obuf,sdslen(c->obuf));
         if (nwritten == -1) {
@@ -958,10 +1135,8 @@ int redisBufferWrite(redisContext *c, int *done) {
 /* Internal helper function to try and get a reply from the reader,
  * or set an error in the context otherwise. */
 int redisGetReplyFromReader(redisContext *c, void **reply) {
-    __redisCreateReplyReader(c);
-    if (redisReplyReaderGetReply(c->reader,reply) == REDIS_ERR) {
-        __redisSetError(c,REDIS_ERR_PROTOCOL,
-            sdsnew(((redisReader*)c->reader)->error));
+    if (redisReaderGetReply(c->reader,reply) == REDIS_ERR) {
+        __redisSetError(c,c->reader->err,c->reader->errstr);
         return REDIS_ERR;
     }
     return REDIS_OK;
@@ -1004,31 +1179,65 @@ int redisGetReply(redisContext *c, void **reply) {
  * is used, you need to call redisGetReply yourself to retrieve
  * the reply (or replies in pub/sub).
  */
-void __redisAppendCommand(redisContext *c, char *cmd, size_t len) {
-    c->obuf = sdscatlen(c->obuf,cmd,len);
+int __redisAppendCommand(redisContext *c, char *cmd, size_t len) {
+    sds newbuf;
+
+    newbuf = sdscatlen(c->obuf,cmd,len);
+    if (newbuf == NULL) {
+        __redisSetError(c,REDIS_ERR_OOM,"Out of memory");
+        return REDIS_ERR;
+    }
+
+    c->obuf = newbuf;
+    return REDIS_OK;
 }
 
-void redisvAppendCommand(redisContext *c, const char *format, va_list ap) {
+int redisvAppendCommand(redisContext *c, const char *format, va_list ap) {
     char *cmd;
     int len;
+
     len = redisvFormatCommand(&cmd,format,ap);
-    __redisAppendCommand(c,cmd,len);
+    if (len == -1) {
+        __redisSetError(c,REDIS_ERR_OOM,"Out of memory");
+        return REDIS_ERR;
+    }
+
+    if (__redisAppendCommand(c,cmd,len) != REDIS_OK) {
+        free(cmd);
+        return REDIS_ERR;
+    }
+
     free(cmd);
+    return REDIS_OK;
 }
 
-void redisAppendCommand(redisContext *c, const char *format, ...) {
+int redisAppendCommand(redisContext *c, const char *format, ...) {
     va_list ap;
+    int ret;
+
     va_start(ap,format);
-    redisvAppendCommand(c,format,ap);
+    ret = redisvAppendCommand(c,format,ap);
     va_end(ap);
+    return ret;
 }
 
-void redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen) {
+int redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen) {
     char *cmd;
     int len;
+
     len = redisFormatCommandArgv(&cmd,argc,argv,argvlen);
-    __redisAppendCommand(c,cmd,len);
+    if (len == -1) {
+        __redisSetError(c,REDIS_ERR_OOM,"Out of memory");
+        return REDIS_ERR;
+    }
+
+    if (__redisAppendCommand(c,cmd,len) != REDIS_OK) {
+        free(cmd);
+        return REDIS_ERR;
+    }
+
     free(cmd);
+    return REDIS_OK;
 }
 
 /* Helper function for the redisCommand* family of functions.
@@ -1042,26 +1251,21 @@ void redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const
  * otherwise. When NULL is returned in a blocking context, the error field
  * in the context will be set.
  */
-static void *__redisCommand(redisContext *c, char *cmd, size_t len) {
-    void *aux = NULL;
-    __redisAppendCommand(c,cmd,len);
+static void *__redisBlockForReply(redisContext *c) {
+    void *reply;
 
     if (c->flags & REDIS_BLOCK) {
-        if (redisGetReply(c,&aux) == REDIS_OK)
-            return aux;
-        return NULL;
+        if (redisGetReply(c,&reply) != REDIS_OK)
+            return NULL;
+        return reply;
     }
     return NULL;
 }
 
 void *redisvCommand(redisContext *c, const char *format, va_list ap) {
-    char *cmd;
-    int len;
-    void *reply = NULL;
-    len = redisvFormatCommand(&cmd,format,ap);
-    reply = __redisCommand(c,cmd,len);
-    free(cmd);
-    return reply;
+    if (redisvAppendCommand(c,format,ap) != REDIS_OK)
+        return NULL;
+    return __redisBlockForReply(c);
 }
 
 void *redisCommand(redisContext *c, const char *format, ...) {
@@ -1074,11 +1278,7 @@ void *redisCommand(redisContext *c, const char *format, ...) {
 }
 
 void *redisCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen) {
-    char *cmd;
-    int len;
-    void *reply = NULL;
-    len = redisFormatCommandArgv(&cmd,argc,argv,argvlen);
-    reply = __redisCommand(c,cmd,len);
-    free(cmd);
-    return reply;
+    if (redisAppendCommandArgv(c,argc,argv,argvlen) != REDIS_OK)
+        return NULL;
+    return __redisBlockForReply(c);
 }