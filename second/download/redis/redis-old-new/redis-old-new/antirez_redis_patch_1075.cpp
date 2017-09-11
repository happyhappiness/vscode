@@ -138,15 +138,11 @@ void feedReplicationBacklogWithObject(robj *o) {
     feedReplicationBacklog(p,len);
 }
 
-#define FEEDSLAVE_BUF_SIZE (1024*64)
 void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
-    int j, i, len;
-    char buf[FEEDSLAVE_BUF_SIZE], *b = buf;
+    int j, len;
     char llstr[REDIS_LONGSTR_SIZE];
-    int buf_left = FEEDSLAVE_BUF_SIZE;
-    robj *o;
 
     /* If there aren't slaves, and there is no backlog buffer to populate,
      * we can return ASAP. */
@@ -155,117 +151,66 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     /* We can't have slaves attached and no backlog. */
     redisAssert(!(listLength(slaves) != 0 && server.repl_backlog == NULL));
 
-    /* What we do here is to try to write as much data as possible in a static
-     * buffer "buf" that is used to create an object that is later sent to all
-     * the slaves. This way we do the decoding only one time for most commands
-     * not containing big payloads. */
-
-    /* Create the SELECT command into the static buffer if needed. */
+    /* Send SELECT command to every slave if needed. */
     if (server.slaveseldb != dictid) {
-        char *selectcmd;
-        size_t sclen;
+        robj *selectcmd;
 
+        /* For a few DBs we have pre-computed SELECT command. */
         if (dictid >= 0 && dictid < REDIS_SHARED_SELECT_CMDS) {
-            selectcmd = shared.select[dictid]->ptr;
-            sclen = sdslen(selectcmd);
-            memcpy(b,selectcmd,sclen);
-            b += sclen;
-            buf_left -= sclen;
+            selectcmd = shared.select[dictid];
         } else {
             int dictid_len;
 
             dictid_len = ll2string(llstr,sizeof(llstr),dictid);
-            sclen = snprintf(b,buf_left,"*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
-                dictid_len, llstr);
-            b += sclen;
-            buf_left -= sclen;
+            selectcmd = createObject(REDIS_STRING,
+                sdscatprintf(sdsempty(),
+                "*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
+                dictid_len, llstr));
         }
+
+        /* Add the SELECT command into the backlog. */
+        if (server.repl_backlog) feedReplicationBacklogWithObject(selectcmd);
+
+        /* Send it to slaves. */
+        listRewind(slaves,&li);
+        while((ln = listNext(&li))) {
+            redisClient *slave = ln->value;
+            addReply(slave,selectcmd);
+        }
+
+        if (dictid < 0 || dictid >= REDIS_SHARED_SELECT_CMDS)
+            decrRefCount(selectcmd);
     }
     server.slaveseldb = dictid;
-   
-    /* Add the multi bulk reply size to the static buffer, that is, the number
-     * of arguments of the command to send to every slave. */
-    b[0] = '*';
-    len = ll2string(b+1,REDIS_LONGSTR_SIZE,argc);
-    b += len+1;
-    buf_left -= len+1;
-    b[0] = '\r';
-    b[1] = '\n';
-    b += 2;
-    buf_left -= 2;
-
-    /* Try to use the static buffer for as much arguments is possible. */
-    for (j = 0; j < argc; j++) {
-        int objlen;
-        char *objptr;
 
-        if (argv[j]->encoding != REDIS_ENCODING_RAW &&
-            argv[j]->encoding != REDIS_ENCODING_INT &&
-            argv[j]->encoding != REDIS_ENCODING_EMBSTR) {
-            redisPanic("Unexpected encoding");
-        }
-        if (sdsEncodedObject(argv[j])) {
-            objlen = sdslen(argv[j]->ptr);
-            objptr = argv[j]->ptr;
-        } else {
-            objlen = ll2string(llstr,REDIS_LONGSTR_SIZE,(long)argv[j]->ptr);
-            objptr = llstr;
-        }
-        /* We need enough space for bulk reply encoding, newlines, and
-         * the data itself. */
-        if (buf_left < objlen+REDIS_LONGSTR_SIZE+32) break;
-
-        /* Write $...CRLF */
-        b[0] = '$';
-        len = ll2string(b+1,REDIS_LONGSTR_SIZE,objlen);
-        b += len+1;
-        buf_left -= len+1;
-        b[0] = '\r';
-        b[1] = '\n';
-        b += 2;
-        buf_left -= 2;
-
-        /* And data plus CRLF */
-        memcpy(b,objptr,objlen);
-        b += objlen;
-        buf_left -= objlen;
-        b[0] = '\r';
-        b[1] = '\n';
-        b += 2;
-        buf_left -= 2;
-    }
-
-    /* Create an object with the static buffer content. */
-    redisAssert(buf_left < FEEDSLAVE_BUF_SIZE);
-    o = createStringObject(buf,b-buf);
-
-    /* If we have a backlog, populate it with data and increment
-     * the global replication offset. */
+    /* Write the command to the replication backlog if any. */
     if (server.repl_backlog) {
-        feedReplicationBacklogWithObject(o);
-        for (i = j; i < argc; i++) {
-            char aux[REDIS_LONGSTR_SIZE+3];
-            long objlen = stringObjectLen(argv[i]);
+        char aux[REDIS_LONGSTR_SIZE+3];
+
+        /* Add the multi bulk reply length. */
+        aux[0] = '*';
+        len = ll2string(aux+1,sizeof(aux-1),argc);
+        aux[len+1] = '\r';
+        aux[len+2] = '\n';
+        feedReplicationBacklog(aux,len+3);
+
+        for (j = 0; j < argc; j++) {
+            long objlen = stringObjectLen(argv[j]);
 
             /* We need to feed the buffer with the object as a bulk reply
              * not just as a plain string, so create the $..CRLF payload len 
              * ad add the final CRLF */
             aux[0] = '$';
-            len = ll2string(aux+1,objlen,sizeof(aux)-1);
+            len = ll2string(aux+1,sizeof(aux)-1,objlen);
             aux[len+1] = '\r';
             aux[len+2] = '\n';
             feedReplicationBacklog(aux,len+3);
-            feedReplicationBacklogWithObject(argv[i]);
-            feedReplicationBacklogWithObject(shared.crlf);
+            feedReplicationBacklogWithObject(argv[j]);
+            feedReplicationBacklogWithObject(aux+len+1,2);
         }
     }
 
-    /* Write data to slaves. Here we do two things:
-     * 1) We write the "o" object that was created using the accumulated
-     *    static buffer.
-     * 2) We write any additional argument of the command to replicate that
-     *    was not written inside the static buffer for lack of space.
-     */
+    /* Write the command to every slave. */
     listRewind(slaves,&li);
     while((ln = listNext(&li))) {
         redisClient *slave = ln->value;
@@ -277,15 +222,14 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
          * are queued in the output buffer until the initial SYNC completes),
          * or are already in sync with the master. */
 
-        /* First, trasmit the object created from the static buffer. */
-        addReply(slave,o);
+        /* Add the multi bulk length. */
+        addReplyMultiBulkLen(slave,argc);
 
         /* Finally any additional argument that was not stored inside the
          * static buffer if any (from j to argc). */
-        for (i = j; i < argc; i++)
-            addReplyBulk(slave,argv[i]);
+        for (j = 0; j < argc; j++)
+            addReplyBulk(slave,argv[j]);
     }
-    decrRefCount(o);
 }
 
 void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **argv, int argc) {