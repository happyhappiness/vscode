@@ -172,7 +172,7 @@
 #define REDIS_MONITOR 8      /* This client is a slave monitor, see MONITOR */
 #define REDIS_MULTI 16      /* This client is in a MULTI context */
 #define REDIS_BLOCKED 32    /* The client is waiting in a blocking operation */
-#define REDIS_IO_WAIT 64    /* The client is waiting for Virutal Memory I/O */
+#define REDIS_IO_WAIT 64    /* The client is waiting for Virtual Memory I/O */
 
 /* Slave replication state - slave side */
 #define REDIS_REPL_NONE 0   /* No active replication */
@@ -387,15 +387,22 @@ struct redisServer {
     unsigned char *vm_bitmap; /* Bitmap of free/used pages */
     time_t unixtime;    /* Unix time sampled every second. */
     /* Virtual memory I/O threads stuff */
-    pthread_t io_threads[REDIS_VM_MAX_THREADS];
     /* An I/O thread process an element taken from the io_jobs queue and
-     * put the result of the operation in the io_done list. */
-    list *io_jobs; /* List of VM I/O jobs */
-    list *io_done; /* List of VM processed jobs */
+     * put the result of the operation in the io_done list. While the
+     * job is being processed, it's put on io_processing queue. */
+    list *io_newjobs; /* List of VM I/O jobs yet to be processed */
+    list *io_processing; /* List of VM I/O jobs being processed */
+    list *io_processed; /* List of VM I/O jobs already processed */
     list *io_clients; /* All the clients waiting for SWAP I/O operations */
-    pthread_mutex_t io_mutex; /* lock to access io_jobs and io_done */
+    pthread_mutex_t io_mutex; /* lock to access io_jobs/io_done/io_thread_job */
     int io_active_threads; /* Number of running I/O threads */
     int vm_max_threads; /* Max number of I/O threads running at the same time */
+    /* Our main thread is blocked on the event loop, locking for sockets ready
+     * to be read or written, so when a threaded I/O operation is ready to be
+     * processed by the main thread, the I/O thread will use a unix pipe to
+     * awake the main thread. The followings are the two pipe FDs. */
+    int io_ready_pipe_read;
+    int io_ready_pipe_write;
     /* Virtual memory stats */
     unsigned long long vm_stats_used_pages;
     unsigned long long vm_stats_swapped_objects;
@@ -467,16 +474,18 @@ struct sharedObjectsStruct {
 static double R_Zero, R_PosInf, R_NegInf, R_Nan;
 
 /* VM threaded I/O request message */
-#define REDIS_IOREQ_LOAD 0
-#define REDIS_IOREQ_SWAP 1
-typedef struct ioreq {
-    int type;   /* Request type, REDIS_IOREQ_* */
+#define REDIS_IOJOB_LOAD 0
+#define REDIS_IOJOB_SWAP 1
+typedef struct iojon {
+    int type;   /* Request type, REDIS_IOJOB_* */
     int dbid;   /* Redis database ID */
     robj *key;  /* This I/O request is about swapping this key */
     robj *val;  /* the value to swap for REDIS_IOREQ_SWAP, otherwise this
                  * field is populated by the I/O thread for REDIS_IOREQ_LOAD. */
     off_t page; /* Swap page where to read/write the object */
-} ioreq;
+    int canceled; /* True if this command was canceled by blocking side of VM */
+    pthread_t thread; /* ID of the thread processing this entry */
+} iojob;
 
 /*================================ Prototypes =============================== */
 
@@ -530,6 +539,9 @@ static robj *vmPreviewObject(robj *key);
 static int vmSwapOneObject(void);
 static int vmCanSwapOut(void);
 static void freeOneObjectFromFreelist(void);
+static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask);
+static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata, int mask);
+static void vmCancelThreadedIOJob(robj *o);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -1379,6 +1391,14 @@ static void initServer() {
     server.stat_starttime = time(NULL);
     server.unixtime = time(NULL);
     aeCreateTimeEvent(server.el, 1, serverCron, NULL, NULL);
+    if (aeCreateFileEvent(server.el, server.fd, AE_READABLE,
+        acceptHandler, NULL) == AE_ERR) oom("creating file event");
+    if (server.vm_enabled) {
+        /* Listen for events in the threaded I/O pipe */
+        if (aeCreateFileEvent(server.el, server.io_ready_pipe_read, AE_READABLE,
+            vmThreadedIOCompletedJob, NULL) == AE_ERR)
+            oom("creating file event");
+    }
 
     if (server.appendonly) {
         server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
@@ -2418,9 +2438,14 @@ static void incrRefCount(robj *o) {
 static void decrRefCount(void *obj) {
     robj *o = obj;
 
-    /* REDIS_VM_SWAPPED */
-    if (server.vm_enabled && o->storage == REDIS_VM_SWAPPED) {
-        redisAssert(o->refcount == 1);
+    /* Object is swapped out, or in the process of being loaded. */
+    if (server.vm_enabled &&
+        (o->storage == REDIS_VM_SWAPPED || o->storage == REDIS_VM_LOADING))
+    {
+        if (o->storage == REDIS_VM_SWAPPED || o->storage == REDIS_VM_LOADING) {
+            redisAssert(o->refcount == 1);
+        }
+        if (o->storage == REDIS_VM_LOADING) vmCancelThreadedIOJob(obj);
         redisAssert(o->type == REDIS_STRING);
         freeStringObject(o);
         vmMarkPagesFree(o->vm.page,o->vm.usedpages);
@@ -2430,8 +2455,10 @@ static void decrRefCount(void *obj) {
         server.vm_stats_swapped_objects--;
         return;
     }
-    /* REDIS_VM_MEMORY */
+    /* Object is in memory, or in the process of being swapped out. */
     if (--(o->refcount) == 0) {
+        if (server.vm_enabled && o->storage == REDIS_VM_SWAPPING)
+            vmCancelThreadedIOJob(obj);
         switch(o->type) {
         case REDIS_STRING: freeStringObject(o); break;
         case REDIS_LIST: freeListObject(o); break;
@@ -2453,7 +2480,13 @@ static robj *lookupKey(redisDb *db, robj *key) {
         robj *val = dictGetEntryVal(de);
 
         if (server.vm_enabled) {
-            if (key->storage == REDIS_VM_MEMORY) {
+            if (key->storage == REDIS_VM_MEMORY ||
+                key->storage == REDIS_VM_SWAPPING)
+            {
+                /* If we were swapping the object out, stop it, this key
+                 * was requested. */
+                if (key->storage == REDIS_VM_SWAPPING)
+                    vmCancelThreadedIOJob(key);
                 /* Update the access time of the key for the aging algorithm. */
                 key->vm.atime = server.unixtime;
             } else {
@@ -2789,9 +2822,23 @@ static int rdbSaveStringObjectRaw(FILE *fp, robj *obj) {
 static int rdbSaveStringObject(FILE *fp, robj *obj) {
     int retval;
 
-    obj = getDecodedObject(obj);
-    retval = rdbSaveStringObjectRaw(fp,obj);
-    decrRefCount(obj);
+    if (obj->storage == REDIS_VM_MEMORY &&
+       obj->encoding != REDIS_ENCODING_RAW)
+    {
+        obj = getDecodedObject(obj);
+        retval = rdbSaveStringObjectRaw(fp,obj);
+        decrRefCount(obj);
+    } else {
+        /* This is a fast path when we are sure the object is not encoded.
+         * Note that's any *faster* actually as we needed to add the conditional
+         * but because this may happen in a background process we don't want
+         * to touch the object fields with incr/decrRefCount in order to
+         * preveny copy on write of pages.
+         *
+         * Also incrRefCount() will have a failing assert() if we try to call
+         * it against an object with storage != REDIS_VM_MEMORY. */
+        retval = rdbSaveStringObjectRaw(fp,obj);
+    }
     return retval;
 }
 
@@ -2940,12 +2987,14 @@ static int rdbSave(char *filename) {
             }
             /* Save the key and associated value. This requires special
              * handling if the value is swapped out. */
-            if (!server.vm_enabled || key->storage == REDIS_VM_MEMORY) {
+            if (!server.vm_enabled || key->storage == REDIS_VM_MEMORY ||
+                                      key->storage == REDIS_VM_SWAPPING) {
                 /* Save type, key, value */
                 if (rdbSaveType(fp,o->type) == -1) goto werr;
                 if (rdbSaveStringObject(fp,key) == -1) goto werr;
                 if (rdbSaveObject(fp,o) == -1) goto werr;
             } else {
+                /* REDIS_VM_SWAPPED or REDIS_VM_LOADING */
                 robj *po, *newkey;
                 /* Get a preview of the object in memory */
                 po = vmPreviewObject(key);
@@ -6654,7 +6703,8 @@ static int rewriteAppendOnlyFile(char *filename) {
             int swapped;
 
             key = dictGetEntryKey(de);
-            if (!server.vm_enabled || key->storage == REDIS_VM_MEMORY) {
+            if (!server.vm_enabled || key->storage == REDIS_VM_MEMORY ||
+                key->storage == REDIS_VM_SWAPPING) {
                 o = dictGetEntryVal(de);
                 swapped = 0;
             } else {
@@ -6831,9 +6881,31 @@ static void aofRemoveTempFile(pid_t childpid) {
     unlink(tmpfile);
 }
 
-/* =============================== Virtual Memory =========================== */
+/* Virtual Memory is composed mainly of two subsystems:
+ * - Blocking Virutal Memory
+ * - Threaded Virtual Memory I/O
+ * The two parts are not fully decoupled, but functions are split among two
+ * different sections of the source code (delimited by comments) in order to
+ * make more clear what functionality is about the blocking VM and what about
+ * the threaded (not blocking) VM.
+ *
+ * Redis VM design:
+ *
+ * Redis VM is a blocking VM (one that blocks reading swapped values from
+ * disk into memory when a value swapped out is needed in memory) that is made
+ * unblocking by trying to examine the command argument vector in order to
+ * load in background values that will likely be needed in order to exec
+ * the command. The command is executed only once all the relevant keys
+ * are loaded into memory.
+ *
+ * This basically is almost as simple of a blocking VM, but almost as parallel
+ * as a fully non-blocking VM.
+ */
+
+/* =================== Virtual Memory - Blocking Side  ====================== */
 static void vmInit(void) {
     off_t totsize;
+    int pipefds[2];
 
     server.vm_fp = fopen("/tmp/redisvm","w+b");
     if (server.vm_fp == NULL) {
@@ -6864,12 +6936,21 @@ static void vmInit(void) {
      * file system when Redis exists. */
     unlink("/tmp/redisvm");
 
-    /* Initialize threaded I/O */
-    server.io_jobs = listCreate();
-    server.io_done = listCreate();
+    /* Initialize threaded I/O (used by Virtual Memory) */
+    server.io_newjobs = listCreate();
+    server.io_processing = listCreate();
+    server.io_processed = listCreate();
     server.io_clients = listCreate();
     pthread_mutex_init(&server.io_mutex,NULL);
     server.io_active_threads = 0;
+    if (pipe(pipefds) == -1) {
+        redisLog(REDIS_WARNING,"Unable to intialized VM: pipe(2): %s. Exiting."
+            ,strerror(errno));
+        exit(1);
+    }
+    server.io_ready_pipe_read = pipefds[0];
+    server.io_ready_pipe_write = pipefds[1];
+    redisAssert(anetNonBlock(NULL,server.io_ready_pipe_read) != ANET_ERR);
 }
 
 /* Mark the page as used */
@@ -7056,6 +7137,10 @@ static robj *vmGenericLoadObject(robj *key, int preview) {
 
 /* Plain object loading, from swap to memory */
 static robj *vmLoadObject(robj *key) {
+    /* If we are loading the object in background, stop it, we
+     * need to load this object synchronously ASAP. */
+    if (key->storage == REDIS_VM_LOADING)
+        vmCancelThreadedIOJob(key);
     return vmGenericLoadObject(key,0);
 }
 
@@ -7212,6 +7297,86 @@ static int deleteIfSwapped(redisDb *db, robj *key) {
     return 1;
 }
 
+/* =================== Virtual Memory - Threaded I/O  ======================= */
+
+/* Every time a thread finished a Job, it writes a byte into the write side
+ * of an unix pipe in order to "awake" the main thread, and this function
+ * is called. */
+static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
+            int mask)
+{
+    char buf[1];
+    int retval;
+    REDIS_NOTUSED(el);
+    REDIS_NOTUSED(mask);
+    REDIS_NOTUSED(privdata);
+
+    /* For every byte we read in the read side of the pipe, there is one
+     * I/O job completed to process. */
+    while((retval = read(fd,buf,1)) == 1) {
+        redisLog(REDIS_DEBUG,"Processing I/O completed job");
+    }
+    if (retval < 0 && errno != EAGAIN) {
+        redisLog(REDIS_WARNING,
+            "WARNING: read(2) error in vmThreadedIOCompletedJob() %s",
+            strerror(errno));
+    }
+}
+
+static void lockThreadedIO(void) {
+    pthread_mutex_lock(&server.io_mutex);
+}
+
+static void unlockThreadedIO(void) {
+    pthread_mutex_unlock(&server.io_mutex);
+}
+
+/* Remove the specified object from the threaded I/O queue if still not
+ * processed, otherwise make sure to flag it as canceled. */
+static void vmCancelThreadedIOJob(robj *o) {
+    list *lists[3] = {
+        server.io_newjobs, server.io_processing, server.io_processed
+    };
+    int i;
+
+    assert(o->storage == REDIS_VM_LOADING || o->storage == REDIS_VM_SWAPPING);
+    lockThreadedIO();
+    /* Search for a matching key in one of the queues */
+    for (i = 0; i < 3; i++) {
+        listNode *ln;
+
+        listRewind(lists[i]);
+        while ((ln = listYield(lists[i])) != NULL) {
+            iojob *job = ln->value;
+
+            if (compareStringObjects(job->key,o) == 0) {
+                switch(i) {
+                case 0: /* io_newjobs */
+                    /* If the job was not yet processed the best thing to do
+                     * is to remove it from the queue at all */
+                    decrRefCount(job->key);
+                    if (job->type == REDIS_IOJOB_SWAP)
+                        decrRefCount(job->val);
+                    listDelNode(lists[i],ln);
+                    break;
+                case 1: /* io_processing */
+                case 2: /* io_processed */
+                    job->canceled = 1;
+                    break;
+                }
+                if (o->storage == REDIS_VM_LOADING)
+                    o->storage = REDIS_VM_SWAPPED;
+                else if (o->storage == REDIS_VM_SWAPPING)
+                    o->storage = REDIS_VM_MEMORY;
+                unlockThreadedIO();
+                return;
+            }
+        }
+    }
+    unlockThreadedIO();
+    assert(1 != 1); /* We should never reach this */
+}
+
 /* ================================= Debugging ============================== */
 
 static void debugCommand(redisClient *c) {
@@ -7377,8 +7542,6 @@ int main(int argc, char **argv) {
         if (rdbLoad(server.dbfilename) == REDIS_OK)
             redisLog(REDIS_NOTICE,"DB loaded from disk");
     }
-    if (aeCreateFileEvent(server.el, server.fd, AE_READABLE,
-        acceptHandler, NULL) == AE_ERR) oom("creating file event");
     redisLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
     aeMain(server.el);
     aeDeleteEventLoop(server.el);