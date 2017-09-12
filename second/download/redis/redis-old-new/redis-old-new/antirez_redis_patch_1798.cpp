@@ -47,17 +47,59 @@ static void test_format_commands() {
         len == 4+4+(3+2)+4+(3+2)+4+(3+2));
     free(cmd);
 
+    test("Format command with %%s and an empty string: ");
+    len = redisFormatCommand(&cmd,"SET %s %s","foo","");
+    test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$3\r\nfoo\r\n$0\r\n\r\n",len) == 0 &&
+        len == 4+4+(3+2)+4+(3+2)+4+(0+2));
+    free(cmd);
+
     test("Format command with %%b string interpolation: ");
     len = redisFormatCommand(&cmd,"SET %b %b","foo",3,"b\0r",3);
     test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$3\r\nfoo\r\n$3\r\nb\0r\r\n",len) == 0 &&
         len == 4+4+(3+2)+4+(3+2)+4+(3+2));
     free(cmd);
 
+    test("Format command with %%b and an empty string: ");
+    len = redisFormatCommand(&cmd,"SET %b %b","foo",3,"",0);
+    test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$3\r\nfoo\r\n$0\r\n\r\n",len) == 0 &&
+        len == 4+4+(3+2)+4+(3+2)+4+(0+2));
+    free(cmd);
+
+    test("Format command with literal %%: ");
+    len = redisFormatCommand(&cmd,"SET %% %%");
+    test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$1\r\n%\r\n$1\r\n%\r\n",len) == 0 &&
+        len == 4+4+(3+2)+4+(1+2)+4+(1+2));
+    free(cmd);
+
+    test("Format command with printf-delegation (long long): ");
+    len = redisFormatCommand(&cmd,"key:%08lld",1234ll);
+    test_cond(strncmp(cmd,"*1\r\n$12\r\nkey:00001234\r\n",len) == 0 &&
+        len == 4+5+(12+2));
+    free(cmd);
+
+    test("Format command with printf-delegation (float): ");
+    len = redisFormatCommand(&cmd,"v:%06.1f",12.34f);
+    test_cond(strncmp(cmd,"*1\r\n$8\r\nv:0012.3\r\n",len) == 0 &&
+        len == 4+4+(8+2));
+    free(cmd);
+
+    test("Format command with printf-delegation and extra interpolation: ");
+    len = redisFormatCommand(&cmd,"key:%d %b",1234,"foo",3);
+    test_cond(strncmp(cmd,"*2\r\n$8\r\nkey:1234\r\n$3\r\nfoo\r\n",len) == 0 &&
+        len == 4+4+(8+2)+4+(3+2));
+    free(cmd);
+
+    test("Format command with wrong printf format and extra interpolation: ");
+    len = redisFormatCommand(&cmd,"key:%08p %b",1234,"foo",3);
+    test_cond(strncmp(cmd,"*2\r\n$6\r\nkey:8p\r\n$3\r\nfoo\r\n",len) == 0 &&
+        len == 4+4+(6+2)+4+(3+2));
+    free(cmd);
+
     const char *argv[3];
     argv[0] = "SET";
-    argv[1] = "foo";
+    argv[1] = "foo\0xxx";
     argv[2] = "bar";
-    size_t lens[3] = { 3, 3, 3 };
+    size_t lens[3] = { 3, 7, 3 };
     int argc = 3;
 
     test("Format command by passing argc/argv without lengths: ");
@@ -68,38 +110,29 @@ static void test_format_commands() {
 
     test("Format command by passing argc/argv with lengths: ");
     len = redisFormatCommandArgv(&cmd,argc,argv,lens);
-    test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$3\r\nfoo\r\n$3\r\nbar\r\n",len) == 0 &&
-        len == 4+4+(3+2)+4+(3+2)+4+(3+2));
+    test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$7\r\nfoo\0xxx\r\n$3\r\nbar\r\n",len) == 0 &&
+        len == 4+4+(3+2)+4+(7+2)+4+(3+2));
     free(cmd);
 }
 
 static void test_blocking_connection() {
     redisContext *c;
     redisReply *reply;
+    int major, minor;
 
-    __connect(&c);
-    test("Returns I/O error when the connection is lost: ");
-    reply = redisCommand(c,"QUIT");
-    test_cond(strcasecmp(reply->str,"OK") == 0 && redisCommand(c,"PING") == NULL);
-
-    /* Two conditions may happen, depending on the type of connection.
-     * When connected via TCP, the socket will not yet be aware of the closed
-     * connection and the write(2) call will succeed, but the read(2) will
-     * result in an EOF. When connected via Unix sockets, the socket will be
-     * immediately aware that it was closed and fail on the write(2) call. */
-    if (use_unix) {
-        fprintf(stderr,"Error: %s\n", c->errstr);
-        assert(c->err == REDIS_ERR_IO &&
-            strcmp(c->errstr,"Broken pipe") == 0);
-    } else {
-        fprintf(stderr,"Error: %s\n", c->errstr);
-        assert(c->err == REDIS_ERR_EOF &&
-            strcmp(c->errstr,"Server closed the connection") == 0);
-    }
-    freeReplyObject(reply);
+    test("Returns error when host cannot be resolved: ");
+    c = redisConnect((char*)"idontexist.local", 6379);
+    test_cond(c->err == REDIS_ERR_OTHER &&
+        strcmp(c->errstr,"Can't resolve: idontexist.local") == 0);
     redisFree(c);
 
-    __connect(&c); /* reconnect */
+    test("Returns error when the port is not open: ");
+    c = redisConnect((char*)"localhost", 56380);
+    test_cond(c->err == REDIS_ERR_IO &&
+        strcmp(c->errstr,"Connection refused") == 0);
+    redisFree(c);
+
+    __connect(&c);
     test("Is able to deliver commands: ");
     reply = redisCommand(c,"PING");
     test_cond(reply->type == REDIS_REPLY_STATUS &&
@@ -112,12 +145,9 @@ static void test_blocking_connection() {
 
     /* Make sure the DB is emtpy */
     reply = redisCommand(c,"DBSIZE");
-    if (reply->type != REDIS_REPLY_INTEGER ||
-        reply->integer != 0) {
-        printf("Sorry DB 9 is not empty, test can not continue\n");
+    if (reply->type != REDIS_REPLY_INTEGER || reply->integer != 0) {
+        printf("Database #9 is not empty, test can not continue\n");
         exit(1);
-    } else {
-        printf("DB 9 is empty... test can continue\n");
     }
     freeReplyObject(reply);
 
@@ -183,6 +213,43 @@ static void test_blocking_connection() {
               reply->element[1]->type == REDIS_REPLY_STATUS &&
               strcasecmp(reply->element[1]->str,"pong") == 0);
     freeReplyObject(reply);
+
+    {
+        /* Find out Redis version to determine the path for the next test */
+        const char *field = "redis_version:";
+        char *p, *eptr;
+
+        reply = redisCommand(c,"INFO");
+        p = strstr(reply->str,field);
+        major = strtol(p+strlen(field),&eptr,10);
+        p = eptr+1; /* char next to the first "." */
+        minor = strtol(p,&eptr,10);
+        freeReplyObject(reply);
+    }
+
+    test("Returns I/O error when the connection is lost: ");
+    reply = redisCommand(c,"QUIT");
+    if (major >= 2 && minor > 0) {
+        /* > 2.0 returns OK on QUIT and read() should be issued once more
+         * to know the descriptor is at EOF. */
+        test_cond(strcasecmp(reply->str,"OK") == 0 &&
+            redisGetReply(c,(void**)&reply) == REDIS_ERR);
+        freeReplyObject(reply);
+    } else {
+        test_cond(reply == NULL);
+    }
+
+    /* On 2.0, QUIT will cause the connection to be closed immediately and
+     * the read(2) for the reply on QUIT will set the error to EOF.
+     * On >2.0, QUIT will return with OK and another read(2) needed to be
+     * issued to find out the socket was closed by the server. In both
+     * conditions, the error will be set to EOF. */
+    assert(c->err == REDIS_ERR_EOF &&
+        strcmp(c->errstr,"Server closed the connection") == 0);
+
+    /* Clean up context and reconnect again */
+    redisFree(c);
+    __connect(&c);
 }
 
 static void test_reply_reader() {
@@ -197,7 +264,7 @@ static void test_reply_reader() {
     ret = redisReplyReaderGetReply(reader,NULL);
     err = redisReplyReaderGetError(reader);
     test_cond(ret == REDIS_ERR &&
-              strcasecmp(err,"protocol error, got \"@\" as reply type byte") == 0);
+              strcasecmp(err,"Protocol error, got \"@\" as reply type byte") == 0);
     redisReplyReaderFree(reader);
 
     /* when the reply already contains multiple items, they must be free'd
@@ -210,7 +277,18 @@ static void test_reply_reader() {
     ret = redisReplyReaderGetReply(reader,NULL);
     err = redisReplyReaderGetError(reader);
     test_cond(ret == REDIS_ERR &&
-              strcasecmp(err,"protocol error, got \"@\" as reply type byte") == 0);
+              strcasecmp(err,"Protocol error, got \"@\" as reply type byte") == 0);
+    redisReplyReaderFree(reader);
+
+    test("Set error on nested multi bulks with depth > 1: ");
+    reader = redisReplyReaderCreate();
+    redisReplyReaderFeed(reader,(char*)"*1\r\n",4);
+    redisReplyReaderFeed(reader,(char*)"*1\r\n",4);
+    redisReplyReaderFeed(reader,(char*)"*1\r\n",4);
+    ret = redisReplyReaderGetReply(reader,NULL);
+    err = redisReplyReaderGetError(reader);
+    test_cond(ret == REDIS_ERR &&
+              strncasecmp(err,"No support for",14) == 0);
     redisReplyReaderFree(reader);
 
     test("Works with NULL functions for reply: ");