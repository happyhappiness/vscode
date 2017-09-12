@@ -1981,7 +1981,7 @@ static void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask)
 
     /* Use writev() if we have enough buffers to send */
     if (!server.glueoutputbuf &&
-        listLength(c->reply) > REDIS_WRITEV_THRESHOLD && 
+        listLength(c->reply) > REDIS_WRITEV_THRESHOLD &&
         !(c->flags & REDIS_MASTER))
     {
         sendReplyToClientWritev(el, fd, privdata, mask);
@@ -2059,7 +2059,7 @@ static void sendReplyToClientWritev(aeEventLoop *el, int fd, void *privdata, int
             o = listNodeValue(node);
             objlen = sdslen(o->ptr);
 
-            if (totwritten + objlen - offset > REDIS_MAX_WRITE_PER_EVENT) 
+            if (totwritten + objlen - offset > REDIS_MAX_WRITE_PER_EVENT)
                 break;
 
             if(ion == REDIS_WRITEV_IOVEC_COUNT)
@@ -2107,7 +2107,7 @@ static void sendReplyToClientWritev(aeEventLoop *el, int fd, void *privdata, int
         }
     }
 
-    if (totwritten > 0) 
+    if (totwritten > 0)
         c->lastinteraction = time(NULL);
 
     if (listLength(c->reply) == 0) {
@@ -2417,7 +2417,7 @@ static void processInputBuffer(redisClient *c) {
         if (p) {
             sds query, *argv;
             int argc, j;
-            
+
             query = c->querybuf;
             c->querybuf = sdsempty();
             querylen = 1+(p-(query));
@@ -2959,7 +2959,7 @@ static int isStringRepresentableAsLong(sds s, long *longval) {
     char buf[32], *endptr;
     long value;
     int slen;
-    
+
     value = strtol(s, &endptr, 10);
     if (endptr[0] != '\0') return REDIS_ERR;
     slen = snprintf(buf,32,"%ld",value);
@@ -3007,7 +3007,7 @@ static robj *tryObjectEncoding(robj *o) {
  * If the object is already raw-encoded just increment the ref count. */
 static robj *getDecodedObject(robj *o) {
     robj *dec;
-    
+
     if (o->encoding == REDIS_ENCODING_RAW) {
         incrRefCount(o);
         return o;
@@ -3337,7 +3337,7 @@ static off_t rdbSavedObjectLen(robj *o, FILE *fp) {
 /* Return the number of pages required to save this object in the swap file */
 static off_t rdbSavedObjectPages(robj *o, FILE *fp) {
     off_t bytes = rdbSavedObjectLen(o,fp);
-    
+
     return (bytes+(server.vm_page_size-1))/server.vm_page_size;
 }
 
@@ -3420,7 +3420,7 @@ static int rdbSave(char *filename) {
     fflush(fp);
     fsync(fileno(fp));
     fclose(fp);
-    
+
     /* Use RENAME to make sure the DB file is changed atomically only
      * if the generate DB file is ok. */
     if (rename(tmpfile,filename) == -1) {
@@ -3850,7 +3850,7 @@ static void setnxCommand(redisClient *c) {
 
 static int getGenericCommand(redisClient *c) {
     robj *o;
-    
+
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL)
         return REDIS_OK;
 
@@ -3881,7 +3881,7 @@ static void getsetCommand(redisClient *c) {
 
 static void mgetCommand(redisClient *c) {
     int j;
-  
+
     addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-1));
     for (j = 1; j < c->argc; j++) {
         robj *o = lookupKeyRead(c->db,c->argv[j]);
@@ -3948,7 +3948,7 @@ static void incrDecrCommand(redisClient *c, long long incr) {
     long long value;
     int retval;
     robj *o;
-    
+
     o = lookupKeyWrite(c->db,c->argv[1]);
     if (o == NULL) {
         value = 0;
@@ -4015,7 +4015,7 @@ static void appendCommand(redisClient *c) {
         totlen = stringObjectLen(c->argv[2]);
     } else {
         dictEntry *de;
-       
+
         de = dictFind(c->db->dict,c->argv[1]);
         assert(de != NULL);
 
@@ -4104,7 +4104,7 @@ static void existsCommand(redisClient *c) {
 
 static void selectCommand(redisClient *c) {
     int id = atoi(c->argv[1]->ptr);
-    
+
     if (selectDb(c,id) == REDIS_ERR) {
         addReplySds(c,sdsnew("-ERR invalid DB index\r\n"));
     } else {
@@ -4114,7 +4114,7 @@ static void selectCommand(redisClient *c) {
 
 static void randomkeyCommand(redisClient *c) {
     dictEntry *de;
-   
+
     while(1) {
         de = dictGetRandomKey(c->db->dict);
         if (!de || expireIfNeeded(c->db,dictGetEntryKey(de)) == 0) break;
@@ -4242,7 +4242,7 @@ static void shutdownCommand(redisClient *c) {
              * in the next cron() Redis will be notified that the background
              * saving aborted, handling special stuff like slaves pending for
              * synchronization... */
-            redisLog(REDIS_WARNING,"Error trying to save the DB, can't exit"); 
+            redisLog(REDIS_WARNING,"Error trying to save the DB, can't exit");
             addReplySds(c,
                 sdsnew("-ERR can't quit, problems saving the DB\r\n"));
         }
@@ -4386,7 +4386,7 @@ static void llenCommand(redisClient *c) {
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_LIST)) return;
-    
+
     l = o->ptr;
     addReplyUlong(c,listLength(l));
 }
@@ -4742,7 +4742,7 @@ static void scardCommand(redisClient *c) {
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_SET)) return;
-    
+
     s = o->ptr;
     addReplyUlong(c,dictSize(s));
 }
@@ -5033,7 +5033,7 @@ static zskiplistNode *zslCreateNode(int level, double score, robj *obj) {
 static zskiplist *zslCreate(void) {
     int j;
     zskiplist *zsl;
-    
+
     zsl = zmalloc(sizeof(*zsl));
     zsl->level = 1;
     zsl->length = 0;
@@ -5366,7 +5366,7 @@ static void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double scor
     } else {
         dictEntry *de;
         double *oldscore;
-        
+
         /* case 2: Score update operation */
         de = dictFind(zs->dict,ele);
         redisAssert(de != NULL);
@@ -7190,7 +7190,7 @@ static void blockingPopGenericCommand(redisClient *c, int where) {
                      * non-blocking POP operation */
                     robj *argv[2], **orig_argv;
                     int orig_argc;
-                   
+
                     /* We need to alter the command arguments before to call
                      * popGenericCommand() as the command takes a single key. */
                     orig_argv = c->argv;
@@ -7427,7 +7427,7 @@ static void updateSlavesWaitingBgsave(int bgsaveerr) {
             slave->replstate = REDIS_REPL_WAIT_BGSAVE_END;
         } else if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
             struct redis_stat buf;
-           
+
             if (bgsaveerr != REDIS_OK) {
                 freeClient(slave);
                 redisLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
@@ -8084,7 +8084,7 @@ static int rewriteAppendOnlyFile(char *filename) {
     fflush(fp);
     fsync(fileno(fp));
     fclose(fp);
-    
+
     /* Use RENAME to make sure the DB file is changed atomically only
      * if the generate DB file is ok. */
     if (rename(tmpfile,filename) == -1) {
@@ -8202,7 +8202,7 @@ static void aofRemoveTempFile(pid_t childpid) {
 static void expandVmSwapFilename(void) {
     char *p = strstr(server.vm_swap_file,"%p");
     sds new;
-    
+
     if (!p) return;
     new = sdsempty();
     *p = '\0';
@@ -8327,7 +8327,7 @@ static int vmFreePage(off_t page) {
 }
 
 /* Find N contiguous free pages storing the first page of the cluster in *first.
- * Returns REDIS_OK if it was able to find N contiguous pages, otherwise 
+ * Returns REDIS_OK if it was able to find N contiguous pages, otherwise
  * REDIS_ERR is returned.
  *
  * This function uses a simple algorithm: we try to allocate
@@ -8338,7 +8338,7 @@ static int vmFreePage(off_t page) {
  * we try to find less populated places doing a forward jump of
  * REDIS_VM_MAX_RANDOM_JUMP, then we start scanning again a few pages
  * without hurry, and then we jump again and so forth...
- * 
+ *
  * This function can be improved using a free list to avoid to guess
  * too much, since we could collect data about freed pages.
  *
@@ -8992,7 +8992,7 @@ static void *IOThreadEntryPoint(void *arg) {
         listDelNode(server.io_processing,ln);
         listAddNodeTail(server.io_processed,j);
         unlockThreadedIO();
-        
+
         /* Signal the main thread there is new stuff to process */
         assert(write(server.io_ready_pipe_write,"x",1) == 1);
     }
@@ -9070,7 +9070,7 @@ static void queueIOJob(iojob *j) {
 
 static int vmSwapObjectThreaded(robj *key, robj *val, redisDb *db) {
     iojob *j;
-    
+
     assert(key->storage == REDIS_VM_MEMORY);
     assert(key->refcount == 1);
 
@@ -9114,7 +9114,7 @@ static int waitForSwappedKey(redisClient *c, robj *key) {
         vmCancelThreadedIOJob(o);
         return 0;
     }
-    
+
     /* OK: the key is either swapped, or being loaded just now. */
 
     /* Add the key to the list of keys this client is waiting for.
@@ -9827,7 +9827,7 @@ static void *getMcontextEip(ucontext_t *uc) {
     return (void*) uc->uc_mcontext->__ss.__rip;
   #else
     return (void*) uc->uc_mcontext->__ss.__eip;
-  #endif 
+  #endif
 #elif defined(__i386__) || defined(__X86_64__) || defined(__x86_64__)
     return (void*) uc->uc_mcontext.gregs[REG_EIP]; /* Linux 32/64 bit */
 #elif defined(__ia64__) /* Linux IA64 */
@@ -9852,7 +9852,7 @@ static void segvHandler(int sig, siginfo_t *info, void *secret) {
     redisLog(REDIS_WARNING, "%s",infostring);
     /* It's not safe to sdsfree() the returned string under memory
      * corruption conditions. Let it leak as we are going to abort */
-    
+
     trace_size = backtrace(trace, 100);
     /* overwrite sigaction with caller's address */
     if (getMcontextEip(uc) != NULL) {