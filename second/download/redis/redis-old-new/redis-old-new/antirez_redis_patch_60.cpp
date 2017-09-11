@@ -1,6 +1,8 @@
 /*
  * Copyright (c) 2009-2011, Salvatore Sanfilippo <antirez at gmail dot com>
- * Copyright (c) 2010-2011, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2010-2014, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2015, Matt Stancliff <matt at genges dot com>,
+ *                     Jan-Erik Rediger <janerik at fnordig dot com>
  *
  * All rights reserved.
  *
@@ -73,6 +75,9 @@ void freeReplyObject(void *reply) {
     redisReply *r = reply;
     size_t j;
 
+    if (r == NULL)
+        return;
+
     switch(r->type) {
     case REDIS_REPLY_INTEGER:
         break; /* Nothing to free */
@@ -183,504 +188,23 @@ static void *createNilObject(const redisReadTask *task) {
     return r;
 }
 
-static void __redisReaderSetError(redisReader *r, int type, const char *str) {
-    size_t len;
-
-    if (r->reply != NULL && r->fn && r->fn->freeObject) {
-        r->fn->freeObject(r->reply);
-        r->reply = NULL;
-    }
-
-    /* Clear input buffer on errors. */
-    if (r->buf != NULL) {
-        sdsfree(r->buf);
-        r->buf = NULL;
-        r->pos = r->len = 0;
-    }
-
-    /* Reset task stack. */
-    r->ridx = -1;
-
-    /* Set error. */
-    r->err = type;
-    len = strlen(str);
-    len = len < (sizeof(r->errstr)-1) ? len : (sizeof(r->errstr)-1);
-    memcpy(r->errstr,str,len);
-    r->errstr[len] = '\0';
-}
-
-static size_t chrtos(char *buf, size_t size, char byte) {
-    size_t len = 0;
-
-    switch(byte) {
-    case '\\':
-    case '"':
-        len = snprintf(buf,size,"\"\\%c\"",byte);
-        break;
-    case '\n': len = snprintf(buf,size,"\"\\n\""); break;
-    case '\r': len = snprintf(buf,size,"\"\\r\""); break;
-    case '\t': len = snprintf(buf,size,"\"\\t\""); break;
-    case '\a': len = snprintf(buf,size,"\"\\a\""); break;
-    case '\b': len = snprintf(buf,size,"\"\\b\""); break;
-    default:
-        if (isprint(byte))
-            len = snprintf(buf,size,"\"%c\"",byte);
-        else
-            len = snprintf(buf,size,"\"\\x%02x\"",(unsigned char)byte);
-        break;
-    }
-
-    return len;
-}
-
-static void __redisReaderSetErrorProtocolByte(redisReader *r, char byte) {
-    char cbuf[8], sbuf[128];
-
-    chrtos(cbuf,sizeof(cbuf),byte);
-    snprintf(sbuf,sizeof(sbuf),
-        "Protocol error, got %s as reply type byte", cbuf);
-    __redisReaderSetError(r,REDIS_ERR_PROTOCOL,sbuf);
-}
-
-static void __redisReaderSetErrorOOM(redisReader *r) {
-    __redisReaderSetError(r,REDIS_ERR_OOM,"Out of memory");
-}
-
-static char *readBytes(redisReader *r, unsigned int bytes) {
-    char *p;
-    if (r->len-r->pos >= bytes) {
-        p = r->buf+r->pos;
-        r->pos += bytes;
-        return p;
-    }
-    return NULL;
-}
-
-/* Find pointer to \r\n. */
-static char *seekNewline(char *s, size_t len) {
-    int pos = 0;
-    int _len = len-1;
-
-    /* Position should be < len-1 because the character at "pos" should be
-     * followed by a \n. Note that strchr cannot be used because it doesn't
-     * allow to search a limited length and the buffer that is being searched
-     * might not have a trailing NULL character. */
-    while (pos < _len) {
-        while(pos < _len && s[pos] != '\r') pos++;
-        if (s[pos] != '\r') {
-            /* Not found. */
-            return NULL;
-        } else {
-            if (s[pos+1] == '\n') {
-                /* Found. */
-                return s+pos;
-            } else {
-                /* Continue searching. */
-                pos++;
-            }
-        }
-    }
-    return NULL;
-}
-
-/* Read a long long value starting at *s, under the assumption that it will be
- * terminated by \r\n. Ambiguously returns -1 for unexpected input. */
-static long long readLongLong(char *s) {
-    long long v = 0;
-    int dec, mult = 1;
-    char c;
-
-    if (*s == '-') {
-        mult = -1;
-        s++;
-    } else if (*s == '+') {
-        mult = 1;
-        s++;
-    }
-
-    while ((c = *(s++)) != '\r') {
-        dec = c - '0';
-        if (dec >= 0 && dec < 10) {
-            v *= 10;
-            v += dec;
-        } else {
-            /* Should not happen... */
-            return -1;
-        }
-    }
-
-    return mult*v;
-}
-
-static char *readLine(redisReader *r, int *_len) {
-    char *p, *s;
-    int len;
-
-    p = r->buf+r->pos;
-    s = seekNewline(p,(r->len-r->pos));
-    if (s != NULL) {
-        len = s-(r->buf+r->pos);
-        r->pos += len+2; /* skip \r\n */
-        if (_len) *_len = len;
-        return p;
-    }
-    return NULL;
-}
-
-static void moveToNextTask(redisReader *r) {
-    redisReadTask *cur, *prv;
-    while (r->ridx >= 0) {
-        /* Return a.s.a.p. when the stack is now empty. */
-        if (r->ridx == 0) {
-            r->ridx--;
-            return;
-        }
-
-        cur = &(r->rstack[r->ridx]);
-        prv = &(r->rstack[r->ridx-1]);
-        assert(prv->type == REDIS_REPLY_ARRAY);
-        if (cur->idx == prv->elements-1) {
-            r->ridx--;
-        } else {
-            /* Reset the type because the next item can be anything */
-            assert(cur->idx < prv->elements);
-            cur->type = -1;
-            cur->elements = -1;
-            cur->idx++;
-            return;
-        }
-    }
-}
-
-static int processLineItem(redisReader *r) {
-    redisReadTask *cur = &(r->rstack[r->ridx]);
-    void *obj;
-    char *p;
-    int len;
-
-    if ((p = readLine(r,&len)) != NULL) {
-        if (cur->type == REDIS_REPLY_INTEGER) {
-            if (r->fn && r->fn->createInteger)
-                obj = r->fn->createInteger(cur,readLongLong(p));
-            else
-                obj = (void*)REDIS_REPLY_INTEGER;
-        } else {
-            /* Type will be error or status. */
-            if (r->fn && r->fn->createString)
-                obj = r->fn->createString(cur,p,len);
-            else
-                obj = (void*)(size_t)(cur->type);
-        }
-
-        if (obj == NULL) {
-            __redisReaderSetErrorOOM(r);
-            return REDIS_ERR;
-        }
-
-        /* Set reply if this is the root object. */
-        if (r->ridx == 0) r->reply = obj;
-        moveToNextTask(r);
-        return REDIS_OK;
-    }
-
-    return REDIS_ERR;
-}
-
-static int processBulkItem(redisReader *r) {
-    redisReadTask *cur = &(r->rstack[r->ridx]);
-    void *obj = NULL;
-    char *p, *s;
-    long len;
-    unsigned long bytelen;
-    int success = 0;
-
-    p = r->buf+r->pos;
-    s = seekNewline(p,r->len-r->pos);
-    if (s != NULL) {
-        p = r->buf+r->pos;
-        bytelen = s-(r->buf+r->pos)+2; /* include \r\n */
-        len = readLongLong(p);
-
-        if (len < 0) {
-            /* The nil object can always be created. */
-            if (r->fn && r->fn->createNil)
-                obj = r->fn->createNil(cur);
-            else
-                obj = (void*)REDIS_REPLY_NIL;
-            success = 1;
-        } else {
-            /* Only continue when the buffer contains the entire bulk item. */
-            bytelen += len+2; /* include \r\n */
-            if (r->pos+bytelen <= r->len) {
-                if (r->fn && r->fn->createString)
-                    obj = r->fn->createString(cur,s+2,len);
-                else
-                    obj = (void*)REDIS_REPLY_STRING;
-                success = 1;
-            }
-        }
-
-        /* Proceed when obj was created. */
-        if (success) {
-            if (obj == NULL) {
-                __redisReaderSetErrorOOM(r);
-                return REDIS_ERR;
-            }
-
-            r->pos += bytelen;
-
-            /* Set reply if this is the root object. */
-            if (r->ridx == 0) r->reply = obj;
-            moveToNextTask(r);
-            return REDIS_OK;
-        }
-    }
-
-    return REDIS_ERR;
-}
-
-static int processMultiBulkItem(redisReader *r) {
-    redisReadTask *cur = &(r->rstack[r->ridx]);
-    void *obj;
-    char *p;
-    long elements;
-    int root = 0;
-
-    /* Set error for nested multi bulks with depth > 7 */
-    if (r->ridx == 8) {
-        __redisReaderSetError(r,REDIS_ERR_PROTOCOL,
-            "No support for nested multi bulk replies with depth > 7");
-        return REDIS_ERR;
-    }
-
-    if ((p = readLine(r,NULL)) != NULL) {
-        elements = readLongLong(p);
-        root = (r->ridx == 0);
-
-        if (elements == -1) {
-            if (r->fn && r->fn->createNil)
-                obj = r->fn->createNil(cur);
-            else
-                obj = (void*)REDIS_REPLY_NIL;
-
-            if (obj == NULL) {
-                __redisReaderSetErrorOOM(r);
-                return REDIS_ERR;
-            }
-
-            moveToNextTask(r);
-        } else {
-            if (r->fn && r->fn->createArray)
-                obj = r->fn->createArray(cur,elements);
-            else
-                obj = (void*)REDIS_REPLY_ARRAY;
-
-            if (obj == NULL) {
-                __redisReaderSetErrorOOM(r);
-                return REDIS_ERR;
-            }
-
-            /* Modify task stack when there are more than 0 elements. */
-            if (elements > 0) {
-                cur->elements = elements;
-                cur->obj = obj;
-                r->ridx++;
-                r->rstack[r->ridx].type = -1;
-                r->rstack[r->ridx].elements = -1;
-                r->rstack[r->ridx].idx = 0;
-                r->rstack[r->ridx].obj = NULL;
-                r->rstack[r->ridx].parent = cur;
-                r->rstack[r->ridx].privdata = r->privdata;
-            } else {
-                moveToNextTask(r);
-            }
-        }
-
-        /* Set reply if this is the root object. */
-        if (root) r->reply = obj;
-        return REDIS_OK;
-    }
-
-    return REDIS_ERR;
-}
-
-static int processItem(redisReader *r) {
-    redisReadTask *cur = &(r->rstack[r->ridx]);
-    char *p;
-
-    /* check if we need to read type */
-    if (cur->type < 0) {
-        if ((p = readBytes(r,1)) != NULL) {
-            switch (p[0]) {
-            case '-':
-                cur->type = REDIS_REPLY_ERROR;
-                break;
-            case '+':
-                cur->type = REDIS_REPLY_STATUS;
-                break;
-            case ':':
-                cur->type = REDIS_REPLY_INTEGER;
-                break;
-            case '$':
-                cur->type = REDIS_REPLY_STRING;
-                break;
-            case '*':
-                cur->type = REDIS_REPLY_ARRAY;
-                break;
-            default:
-                __redisReaderSetErrorProtocolByte(r,*p);
-                return REDIS_ERR;
-            }
-        } else {
-            /* could not consume 1 byte */
-            return REDIS_ERR;
-        }
-    }
-
-    /* process typed item */
-    switch(cur->type) {
-    case REDIS_REPLY_ERROR:
-    case REDIS_REPLY_STATUS:
-    case REDIS_REPLY_INTEGER:
-        return processLineItem(r);
-    case REDIS_REPLY_STRING:
-        return processBulkItem(r);
-    case REDIS_REPLY_ARRAY:
-        return processMultiBulkItem(r);
-    default:
-        assert(NULL);
-        return REDIS_ERR; /* Avoid warning. */
-    }
-}
-
-redisReader *redisReaderCreate(void) {
-    redisReader *r;
-
-    r = calloc(sizeof(redisReader),1);
-    if (r == NULL)
-        return NULL;
-
-    r->err = 0;
-    r->errstr[0] = '\0';
-    r->fn = &defaultFunctions;
-    r->buf = sdsempty();
-    r->maxbuf = REDIS_READER_MAX_BUF;
-    if (r->buf == NULL) {
-        free(r);
-        return NULL;
-    }
-
-    r->ridx = -1;
-    return r;
-}
-
-void redisReaderFree(redisReader *r) {
-    if (r->reply != NULL && r->fn && r->fn->freeObject)
-        r->fn->freeObject(r->reply);
-    if (r->buf != NULL)
-        sdsfree(r->buf);
-    free(r);
-}
-
-int redisReaderFeed(redisReader *r, const char *buf, size_t len) {
-    sds newbuf;
-
-    /* Return early when this reader is in an erroneous state. */
-    if (r->err)
-        return REDIS_ERR;
-
-    /* Copy the provided buffer. */
-    if (buf != NULL && len >= 1) {
-        /* Destroy internal buffer when it is empty and is quite large. */
-        if (r->len == 0 && r->maxbuf != 0 && sdsavail(r->buf) > r->maxbuf) {
-            sdsfree(r->buf);
-            r->buf = sdsempty();
-            r->pos = 0;
-
-            /* r->buf should not be NULL since we just free'd a larger one. */
-            assert(r->buf != NULL);
-        }
-
-        newbuf = sdscatlen(r->buf,buf,len);
-        if (newbuf == NULL) {
-            __redisReaderSetErrorOOM(r);
-            return REDIS_ERR;
-        }
-
-        r->buf = newbuf;
-        r->len = sdslen(r->buf);
-    }
-
-    return REDIS_OK;
-}
-
-int redisReaderGetReply(redisReader *r, void **reply) {
-    /* Default target pointer to NULL. */
-    if (reply != NULL)
-        *reply = NULL;
-
-    /* Return early when this reader is in an erroneous state. */
-    if (r->err)
-        return REDIS_ERR;
-
-    /* When the buffer is empty, there will never be a reply. */
-    if (r->len == 0)
-        return REDIS_OK;
-
-    /* Set first item to process when the stack is empty. */
-    if (r->ridx == -1) {
-        r->rstack[0].type = -1;
-        r->rstack[0].elements = -1;
-        r->rstack[0].idx = -1;
-        r->rstack[0].obj = NULL;
-        r->rstack[0].parent = NULL;
-        r->rstack[0].privdata = r->privdata;
-        r->ridx = 0;
-    }
-
-    /* Process items in reply. */
-    while (r->ridx >= 0)
-        if (processItem(r) != REDIS_OK)
-            break;
-
-    /* Return ASAP when an error occurred. */
-    if (r->err)
-        return REDIS_ERR;
-
-    /* Discard part of the buffer when we've consumed at least 1k, to avoid
-     * doing unnecessary calls to memmove() in sds.c. */
-    if (r->pos >= 1024) {
-        sdsrange(r->buf,r->pos,-1);
-        r->pos = 0;
-        r->len = sdslen(r->buf);
-    }
-
-    /* Emit a reply when there is one. */
-    if (r->ridx == -1) {
-        if (reply != NULL)
-            *reply = r->reply;
-        r->reply = NULL;
-    }
-    return REDIS_OK;
-}
-
-/* Calculate the number of bytes needed to represent an integer as string. */
-static int intlen(int i) {
-    int len = 0;
-    if (i < 0) {
-        len++;
-        i = -i;
-    }
-    do {
-        len++;
-        i /= 10;
-    } while(i);
-    return len;
+/* Return the number of digits of 'v' when converted to string in radix 10.
+ * Implementation borrowed from link in redis/src/util.c:string2ll(). */
+static uint32_t countDigits(uint64_t v) {
+  uint32_t result = 1;
+  for (;;) {
+    if (v < 10) return result;
+    if (v < 100) return result + 1;
+    if (v < 1000) return result + 2;
+    if (v < 10000) return result + 3;
+    v /= 10000U;
+    result += 4;
+  }
 }
 
 /* Helper that calculates the bulk length given a certain string length. */
 static size_t bulklen(size_t len) {
-    return 1+intlen(len)+2+len+2;
+    return 1+countDigits(len)+2+len+2;
 }
 
 int redisvFormatCommand(char **target, const char *format, va_list ap) {
@@ -692,6 +216,7 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
     char **curargv = NULL, **newargv = NULL;
     int argc = 0;
     int totlen = 0;
+    int error_type = 0; /* 0 = no error; -1 = memory error; -2 = format error */
     int j;
 
     /* Abort if there is not target to set */
@@ -708,19 +233,19 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
             if (*c == ' ') {
                 if (touched) {
                     newargv = realloc(curargv,sizeof(char*)*(argc+1));
-                    if (newargv == NULL) goto err;
+                    if (newargv == NULL) goto memory_err;
                     curargv = newargv;
                     curargv[argc++] = curarg;
                     totlen += bulklen(sdslen(curarg));
 
                     /* curarg is put in argv so it can be overwritten. */
                     curarg = sdsempty();
-                    if (curarg == NULL) goto err;
+                    if (curarg == NULL) goto memory_err;
                     touched = 0;
                 }
             } else {
                 newarg = sdscatlen(curarg,c,1);
-                if (newarg == NULL) goto err;
+                if (newarg == NULL) goto memory_err;
                 curarg = newarg;
                 touched = 1;
             }
@@ -751,17 +276,14 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
                 /* Try to detect printf format */
                 {
                     static const char intfmts[] = "diouxX";
+                    static const char flags[] = "#0-+ ";
                     char _format[16];
                     const char *_p = c+1;
                     size_t _l = 0;
                     va_list _cpy;
 
                     /* Flags */
-                    if (*_p != '\0' && *_p == '#') _p++;
-                    if (*_p != '\0' && *_p == '0') _p++;
-                    if (*_p != '\0' && *_p == '-') _p++;
-                    if (*_p != '\0' && *_p == ' ') _p++;
-                    if (*_p != '\0' && *_p == '+') _p++;
+                    while (*_p != '\0' && strchr(flags,*_p) != NULL) _p++;
 
                     /* Field width */
                     while (*_p != '\0' && isdigit(*_p)) _p++;
@@ -829,7 +351,7 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
 
                 fmt_invalid:
                     va_end(_cpy);
-                    goto err;
+                    goto format_err;
 
                 fmt_valid:
                     _l = (_p+1)-c;
@@ -848,7 +370,7 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
                 }
             }
 
-            if (newarg == NULL) goto err;
+            if (newarg == NULL) goto memory_err;
             curarg = newarg;
 
             touched = 1;
@@ -860,7 +382,7 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
     /* Add the last argument if needed */
     if (touched) {
         newargv = realloc(curargv,sizeof(char*)*(argc+1));
-        if (newargv == NULL) goto err;
+        if (newargv == NULL) goto memory_err;
         curargv = newargv;
         curargv[argc++] = curarg;
         totlen += bulklen(sdslen(curarg));
@@ -872,11 +394,11 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
     curarg = NULL;
 
     /* Add bytes needed to hold multi bulk count */
-    totlen += 1+intlen(argc)+2;
+    totlen += 1+countDigits(argc)+2;
 
     /* Build the command at protocol level */
     cmd = malloc(totlen+1);
-    if (cmd == NULL) goto err;
+    if (cmd == NULL) goto memory_err;
 
     pos = sprintf(cmd,"*%d\r\n",argc);
     for (j = 0; j < argc; j++) {
@@ -894,20 +416,29 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
     *target = cmd;
     return totlen;
 
-err:
-    while(argc--)
-        sdsfree(curargv[argc]);
-    free(curargv);
+format_err:
+    error_type = -2;
+    goto cleanup;
 
-    if (curarg != NULL)
-        sdsfree(curarg);
+memory_err:
+    error_type = -1;
+    goto cleanup;
+
+cleanup:
+    if (curargv) {
+        while(argc--)
+            sdsfree(curargv[argc]);
+        free(curargv);
+    }
+
+    sdsfree(curarg);
 
     /* No need to check cmd since it is the last statement that can fail,
      * but do it anyway to be as defensive as possible. */
     if (cmd != NULL)
         free(cmd);
 
-    return -1;
+    return error_type;
 }
 
 /* Format a command according to the Redis protocol. This function
@@ -928,9 +459,69 @@ int redisFormatCommand(char **target, const char *format, ...) {
     va_start(ap,format);
     len = redisvFormatCommand(target,format,ap);
     va_end(ap);
+
+    /* The API says "-1" means bad result, but we now also return "-2" in some
+     * cases.  Force the return value to always be -1. */
+    if (len < 0)
+        len = -1;
+
     return len;
 }
 
+/* Format a command according to the Redis protocol using an sds string and
+ * sdscatfmt for the processing of arguments. This function takes the
+ * number of arguments, an array with arguments and an array with their
+ * lengths. If the latter is set to NULL, strlen will be used to compute the
+ * argument lengths.
+ */
+int redisFormatSdsCommandArgv(sds *target, int argc, const char **argv,
+                              const size_t *argvlen)
+{
+    sds cmd;
+    unsigned long long totlen;
+    int j;
+    size_t len;
+
+    /* Abort on a NULL target */
+    if (target == NULL)
+        return -1;
+
+    /* Calculate our total size */
+    totlen = 1+countDigits(argc)+2;
+    for (j = 0; j < argc; j++) {
+        len = argvlen ? argvlen[j] : strlen(argv[j]);
+        totlen += bulklen(len);
+    }
+
+    /* Use an SDS string for command construction */
+    cmd = sdsempty();
+    if (cmd == NULL)
+        return -1;
+
+    /* We already know how much storage we need */
+    cmd = sdsMakeRoomFor(cmd, totlen);
+    if (cmd == NULL)
+        return -1;
+
+    /* Construct command */
+    cmd = sdscatfmt(cmd, "*%i\r\n", argc);
+    for (j=0; j < argc; j++) {
+        len = argvlen ? argvlen[j] : strlen(argv[j]);
+        cmd = sdscatfmt(cmd, "$%u\r\n", len);
+        cmd = sdscatlen(cmd, argv[j], len);
+        cmd = sdscatlen(cmd, "\r\n", sizeof("\r\n")-1);
+    }
+
+    assert(sdslen(cmd)==totlen);
+
+    *target = cmd;
+    return totlen;
+}
+
+void redisFreeSdsCommand(sds cmd) {
+    sdsfree(cmd);
+}
+
 /* Format a command according to the Redis protocol. This function takes the
  * number of arguments, an array with arguments and an array with their
  * lengths. If the latter is set to NULL, strlen will be used to compute the
@@ -942,8 +533,12 @@ int redisFormatCommandArgv(char **target, int argc, const char **argv, const siz
     size_t len;
     int totlen, j;
 
+    /* Abort on a NULL target */
+    if (target == NULL)
+        return -1;
+
     /* Calculate number of bytes needed for the command */
-    totlen = 1+intlen(argc)+2;
+    totlen = 1+countDigits(argc)+2;
     for (j = 0; j < argc; j++) {
         len = argvlen ? argvlen[j] : strlen(argv[j]);
         totlen += bulklen(len);
@@ -970,6 +565,10 @@ int redisFormatCommandArgv(char **target, int argc, const char **argv, const siz
     return totlen;
 }
 
+void redisFreeCommand(char *cmd) {
+    free(cmd);
+}
+
 void __redisSetError(redisContext *c, int type, const char *str) {
     size_t len;
 
@@ -982,10 +581,14 @@ void __redisSetError(redisContext *c, int type, const char *str) {
     } else {
         /* Only REDIS_ERR_IO may lack a description! */
         assert(type == REDIS_ERR_IO);
-        strerror_r(errno,c->errstr,sizeof(c->errstr));
+        __redis_strerror_r(errno, c->errstr, sizeof(c->errstr));
     }
 }
 
+redisReader *redisReaderCreate(void) {
+    return redisReaderCreateWithFunctions(&defaultFunctions);
+}
+
 static redisContext *redisContextInit(void) {
     redisContext *c;
 
@@ -997,24 +600,72 @@ static redisContext *redisContextInit(void) {
     c->errstr[0] = '\0';
     c->obuf = sdsempty();
     c->reader = redisReaderCreate();
+    c->tcp.host = NULL;
+    c->tcp.source_addr = NULL;
+    c->unix_sock.path = NULL;
+    c->timeout = NULL;
+
+    if (c->obuf == NULL || c->reader == NULL) {
+        redisFree(c);
+        return NULL;
+    }
+
     return c;
 }
 
 void redisFree(redisContext *c) {
+    if (c == NULL)
+        return;
     if (c->fd > 0)
         close(c->fd);
     if (c->obuf != NULL)
         sdsfree(c->obuf);
     if (c->reader != NULL)
         redisReaderFree(c->reader);
+    if (c->tcp.host)
+        free(c->tcp.host);
+    if (c->tcp.source_addr)
+        free(c->tcp.source_addr);
+    if (c->unix_sock.path)
+        free(c->unix_sock.path);
+    if (c->timeout)
+        free(c->timeout);
     free(c);
 }
 
 int redisFreeKeepFd(redisContext *c) {
-	int fd = c->fd;
-	c->fd = -1;
-	redisFree(c);
-	return fd;
+    int fd = c->fd;
+    c->fd = -1;
+    redisFree(c);
+    return fd;
+}
+
+int redisReconnect(redisContext *c) {
+    c->err = 0;
+    memset(c->errstr, '\0', strlen(c->errstr));
+
+    if (c->fd > 0) {
+        close(c->fd);
+    }
+
+    sdsfree(c->obuf);
+    redisReaderFree(c->reader);
+
+    c->obuf = sdsempty();
+    c->reader = redisReaderCreate();
+
+    if (c->connection_type == REDIS_CONN_TCP) {
+        return redisContextConnectBindTcp(c, c->tcp.host, c->tcp.port,
+                c->timeout, c->tcp.source_addr);
+    } else if (c->connection_type == REDIS_CONN_UNIX) {
+        return redisContextConnectUnix(c, c->unix_sock.path, c->timeout);
+    } else {
+        /* Something bad happened here and shouldn't have. There isn't
+           enough information in the context to reconnect. */
+        __redisSetError(c,REDIS_ERR_OTHER,"Not enough information to reconnect");
+    }
+
+    return REDIS_ERR;
 }
 
 /* Connect to a Redis instance. On error the field error in the returned
@@ -1064,6 +715,15 @@ redisContext *redisConnectBindNonBlock(const char *ip, int port,
     return c;
 }
 
+redisContext *redisConnectBindNonBlockWithReuse(const char *ip, int port,
+                                                const char *source_addr) {
+    redisContext *c = redisContextInit();
+    c->flags &= ~REDIS_BLOCK;
+    c->flags |= REDIS_REUSEADDR;
+    redisContextConnectBindTcp(c,ip,port,NULL,source_addr);
+    return c;
+}
+
 redisContext *redisConnectUnix(const char *path) {
     redisContext *c;
 
@@ -1162,10 +822,10 @@ int redisBufferRead(redisContext *c) {
 /* Write the output buffer to the socket.
  *
  * Returns REDIS_OK when the buffer is empty, or (a part of) the buffer was
- * succesfully written to the socket. When the buffer is empty after the
+ * successfully written to the socket. When the buffer is empty after the
  * write operation, "done" is set to 1 (if given).
  *
- * Returns REDIS_ERR if an error occured trying to write and sets
+ * Returns REDIS_ERR if an error occurred trying to write and sets
  * c->errstr to hold the appropriate error string.
  */
 int redisBufferWrite(redisContext *c, int *done) {
@@ -1274,6 +934,9 @@ int redisvAppendCommand(redisContext *c, const char *format, va_list ap) {
     if (len == -1) {
         __redisSetError(c,REDIS_ERR_OOM,"Out of memory");
         return REDIS_ERR;
+    } else if (len == -2) {
+        __redisSetError(c,REDIS_ERR_OTHER,"Invalid format string");
+        return REDIS_ERR;
     }
 
     if (__redisAppendCommand(c,cmd,len) != REDIS_OK) {
@@ -1296,21 +959,21 @@ int redisAppendCommand(redisContext *c, const char *format, ...) {
 }
 
 int redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen) {
-    char *cmd;
+    sds cmd;
     int len;
 
-    len = redisFormatCommandArgv(&cmd,argc,argv,argvlen);
+    len = redisFormatSdsCommandArgv(&cmd,argc,argv,argvlen);
     if (len == -1) {
         __redisSetError(c,REDIS_ERR_OOM,"Out of memory");
         return REDIS_ERR;
     }
 
     if (__redisAppendCommand(c,cmd,len) != REDIS_OK) {
-        free(cmd);
+        sdsfree(cmd);
         return REDIS_ERR;
     }
 
-    free(cmd);
+    sdsfree(cmd);
     return REDIS_OK;
 }
 
@@ -1321,7 +984,7 @@ int redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const s
  * context is non-blocking, the "reply" pointer will not be used and the
  * command is simply appended to the write buffer.
  *
- * Returns the reply when a reply was succesfully retrieved. Returns NULL
+ * Returns the reply when a reply was successfully retrieved. Returns NULL
  * otherwise. When NULL is returned in a blocking context, the error field
  * in the context will be set.
  */