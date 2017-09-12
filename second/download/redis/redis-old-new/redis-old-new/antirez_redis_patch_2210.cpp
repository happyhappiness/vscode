@@ -172,13 +172,12 @@
 #define REDIS_MAX_COMPLETED_JOBS_PROCESSED 1
 
 /* Client flags */
-#define REDIS_CLOSE 1       /* This client connection should be closed ASAP */
-#define REDIS_SLAVE 2       /* This client is a slave server */
-#define REDIS_MASTER 4      /* This client is a master server */
-#define REDIS_MONITOR 8      /* This client is a slave monitor, see MONITOR */
-#define REDIS_MULTI 16      /* This client is in a MULTI context */
-#define REDIS_BLOCKED 32    /* The client is waiting in a blocking operation */
-#define REDIS_IO_WAIT 64    /* The client is waiting for Virtual Memory I/O */
+#define REDIS_SLAVE 1       /* This client is a slave server */
+#define REDIS_MASTER 2      /* This client is a master server */
+#define REDIS_MONITOR 4     /* This client is a slave monitor, see MONITOR */
+#define REDIS_MULTI 8       /* This client is in a MULTI context */
+#define REDIS_BLOCKED 16    /* The client is waiting in a blocking operation */
+#define REDIS_IO_WAIT 32    /* The client is waiting for Virtual Memory I/O */
 
 /* Slave replication state - slave side */
 #define REDIS_REPL_NONE 0   /* No active replication */
@@ -269,6 +268,7 @@ typedef struct redisDb {
     dict *dict;                 /* The keyspace for this DB */
     dict *expires;              /* Timeout of keys with a timeout set */
     dict *blockingkeys;         /* Keys with clients waiting for data (BLPOP) */
+    dict *io_keys;              /* Keys with clients waiting for VM I/O */
     int id;
 } redisDb;
 
@@ -298,16 +298,15 @@ typedef struct redisClient {
     list *reply;
     int sentlen;
     time_t lastinteraction; /* time of the last interaction, used for timeout */
-    int flags;              /* REDIS_CLOSE | REDIS_SLAVE | REDIS_MONITOR */
-                            /* REDIS_MULTI */
+    int flags;              /* REDIS_SLAVE | REDIS_MONITOR | REDIS_MULTI ... */
     int slaveseldb;         /* slave selected db, if this client is a slave */
     int authenticated;      /* when requirepass is non-NULL */
     int replstate;          /* replication state if this is a slave */
     int repldbfd;           /* replication DB file descriptor */
     long repldboff;         /* replication DB file offset */
     off_t repldbsize;       /* replication DB file size */
     multiState mstate;      /* MULTI/EXEC state */
-    robj **blockingkeys;    /* The key we waiting to terminate a blocking
+    robj **blockingkeys;    /* The key we are waiting to terminate a blocking
                              * operation such as BLPOP. Otherwise NULL. */
     int blockingkeysnum;    /* Number of blocking keys */
     time_t blockingto;      /* Blocking operation timeout. If UNIX current time
@@ -373,7 +372,8 @@ struct redisServer {
     int replstate;
     unsigned int maxclients;
     unsigned long long maxmemory;
-    unsigned int blockedclients;
+    unsigned int blpop_blocked_clients;
+    unsigned int vm_blocked_clients;
     /* Sort parameters - qsort_r() is only available under BSD so we
      * have to take this state global, in order to pass it to sortCompare() */
     int sort_desc;
@@ -399,7 +399,7 @@ struct redisServer {
     list *io_newjobs; /* List of VM I/O jobs yet to be processed */
     list *io_processing; /* List of VM I/O jobs being processed */
     list *io_processed; /* List of VM I/O jobs already processed */
-    list *io_clients; /* All the clients waiting for SWAP I/O operations */
+    list *io_ready_clients; /* Clients ready to be unblocked. All keys loaded */
     pthread_mutex_t io_mutex; /* lock to access io_jobs/io_done/io_thread_job */
     pthread_mutex_t obj_freelist_mutex; /* safe redis objects creation/free */
     pthread_mutex_t io_swapfile_mutex; /* So we can lseek + write */
@@ -487,7 +487,7 @@ static double R_Zero, R_PosInf, R_NegInf, R_Nan;
 #define REDIS_IOJOB_LOAD 0          /* Load from disk to memory */
 #define REDIS_IOJOB_PREPARE_SWAP 1  /* Compute needed pages */
 #define REDIS_IOJOB_DO_SWAP 2       /* Swap from memory to disk */
-typedef struct iojon {
+typedef struct iojob {
     int type;   /* Request type, REDIS_IOJOB_* */
     redisDb *db;/* Redis database */
     robj *key;  /* This I/O request is about swapping this key */
@@ -565,6 +565,13 @@ static robj *vmReadObjectFromSwap(off_t page, int type);
 static void waitEmptyIOJobsQueue(void);
 static void vmReopenSwapFile(void);
 static int vmFreePage(off_t page);
+static int blockClientOnSwappedKeys(struct redisCommand *cmd, redisClient *c);
+static int dontWaitForSwappedKey(redisClient *c, robj *key);
+static void handleClientsBlockedOnSwappedKey(redisDb *db, robj *key);
+static void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask);
+static struct redisCommand *lookupCommand(char *name);
+static void call(redisClient *c, struct redisCommand *cmd);
+static void resetClient(redisClient *c);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -994,7 +1001,8 @@ static dictType keyptrDictType = {
 };
 
 /* Keylist hash table type has unencoded redis objects as keys and
- * lists as values. It's used for blocking operations (BLPOP) */
+ * lists as values. It's used for blocking operations (BLPOP) and to
+ * map swapped keys to a list of clients waiting for this keys to be loaded. */
 static dictType keylistDictType = {
     dictObjHash,                /* hash function */
     NULL,                       /* key dup */
@@ -1195,7 +1203,7 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
     }
 
     /* Close connections of timedout clients */
-    if ((server.maxidletime && !(loops % 10)) || server.blockedclients)
+    if ((server.maxidletime && !(loops % 10)) || server.blpop_blocked_clients)
         closeTimedoutClients();
 
     /* Check if a background saving or AOF rewrite in progress terminated */
@@ -1294,6 +1302,38 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
     return 1000;
 }
 
+/* This function gets called every time Redis is entering the
+ * main loop of the event driven library, that is, before to sleep
+ * for ready file descriptors. */
+static void beforeSleep(struct aeEventLoop *eventLoop) {
+    REDIS_NOTUSED(eventLoop);
+
+    if (server.vm_enabled && listLength(server.io_ready_clients)) {
+        listIter li;
+        listNode *ln;
+
+        listRewind(server.io_ready_clients,&li);
+        while((ln = listNext(&li))) {
+            redisClient *c = ln->value;
+            struct redisCommand *cmd;
+
+            /* Resume the client. */
+            listDelNode(server.io_ready_clients,ln);
+            c->flags &= (~REDIS_IO_WAIT);
+            server.vm_blocked_clients--;
+            aeCreateFileEvent(server.el, c->fd, AE_READABLE,
+                readQueryFromClient, c);
+            cmd = lookupCommand(c->argv[0]->ptr);
+            assert(cmd != NULL);
+            call(c,cmd);
+            resetClient(c);
+            /* There may be more data to process in the input buffer. */
+            if (c->querybuf && sdslen(c->querybuf) > 0)
+                processInputBuffer(c);
+        }
+    }
+}
+
 static void createSharedObjects(void) {
     shared.crlf = createObject(REDIS_STRING,sdsnew("\r\n"));
     shared.ok = createObject(REDIS_STRING,sdsnew("+OK\r\n"));
@@ -1367,14 +1407,15 @@ static void initServerConfig() {
     server.rdbcompression = 1;
     server.sharingpoolsize = 1024;
     server.maxclients = 0;
-    server.blockedclients = 0;
+    server.blpop_blocked_clients = 0;
     server.maxmemory = 0;
     server.vm_enabled = 0;
     server.vm_swap_file = zstrdup("/tmp/redis-%p.vm");
     server.vm_page_size = 256;          /* 256 bytes per page */
     server.vm_pages = 1024*1024*100;    /* 104 millions of pages */
     server.vm_max_memory = 1024LL*1024*1024*1; /* 1 GB of RAM */
     server.vm_max_threads = 4;
+    server.vm_blocked_clients = 0;
 
     resetServerSaveParams();
 
@@ -1425,6 +1466,8 @@ static void initServer() {
         server.db[j].dict = dictCreate(&hashDictType,NULL);
         server.db[j].expires = dictCreate(&keyptrDictType,NULL);
         server.db[j].blockingkeys = dictCreate(&keylistDictType,NULL);
+        if (server.vm_enabled)
+            server.db[j].io_keys = dictCreate(&keylistDictType,NULL);
         server.db[j].id = j;
     }
     server.cronloops = 0;
@@ -1685,11 +1728,17 @@ static void freeClient(redisClient *c) {
     ln = listSearchKey(server.clients,c);
     redisAssert(ln != NULL);
     listDelNode(server.clients,ln);
-    /* Remove from the list of clients waiting for VM operations */
-    if (server.vm_enabled && listLength(c->io_keys)) {
-        ln = listSearchKey(server.io_clients,c);
-        if (ln) listDelNode(server.io_clients,ln);
-        listRelease(c->io_keys);
+    /* Remove from the list of clients waiting for swapped keys */
+    if (c->flags & REDIS_IO_WAIT && listLength(c->io_keys) == 0) {
+        ln = listSearchKey(server.io_ready_clients,c);
+        if (ln) {
+            listDelNode(server.io_ready_clients,ln);
+            server.vm_blocked_clients--;
+        }
+    }
+    while (server.vm_enabled && listLength(c->io_keys)) {
+        ln = listFirst(c->io_keys);
+        dontWaitForSwappedKey(c,ln->value);
     }
     listRelease(c->io_keys);
     /* Other cleanup */
@@ -2002,6 +2051,9 @@ static int processCommand(redisClient *c) {
         freeClient(c);
         return 0;
     }
+
+    /* Now lookup the command and check ASAP about trivial error conditions
+     * such wrong arity, bad command name and so forth. */
     cmd = lookupCommand(c->argv[0]->ptr);
     if (!cmd) {
         addReplySds(c,
@@ -2022,6 +2074,7 @@ static int processCommand(redisClient *c) {
         resetClient(c);
         return 1;
     } else if (cmd->flags & REDIS_CMD_BULK && c->bulklen == -1) {
+        /* This is a bulk command, we have to read the last argument yet. */
         int bulklen = atoi(c->argv[c->argc-1]->ptr);
 
         decrRefCount(c->argv[c->argc-1]);
@@ -2043,6 +2096,8 @@ static int processCommand(redisClient *c) {
             c->argc++;
             c->querybuf = sdsrange(c->querybuf,c->bulklen,-1);
         } else {
+            /* Otherwise return... there is to read the last argument
+             * from the socket. */
             return 1;
         }
     }
@@ -2068,14 +2123,12 @@ static int processCommand(redisClient *c) {
         queueMultiCommand(c,cmd);
         addReply(c,shared.queued);
     } else {
+        if (server.vm_enabled && server.vm_max_threads > 0 &&
+            blockClientOnSwappedKeys(cmd,c)) return 1;
         call(c,cmd);
     }
 
     /* Prepare the client for the next command */
-    if (c->flags & REDIS_CLOSE) {
-        freeClient(c);
-        return 0;
-    }
     resetClient(c);
     return 1;
 }
@@ -2550,10 +2603,16 @@ static robj *lookupKey(redisDb *db, robj *key) {
                 /* Update the access time of the key for the aging algorithm. */
                 key->vm.atime = server.unixtime;
             } else {
+                int notify = (key->storage == REDIS_VM_LOADING);
+
                 /* Our value was swapped on disk. Bring it at home. */
                 redisAssert(val == NULL);
                 val = vmLoadObject(key);
                 dictGetEntryVal(de) = val;
+
+                /* Clients blocked by the VM subsystem may be waiting for
+                 * this key... */
+                if (notify) handleClientsBlockedOnSwappedKey(db,key);
             }
         }
         return val;
@@ -5618,7 +5677,7 @@ static sds genRedisInfoString(void) {
         uptime/(3600*24),
         listLength(server.clients)-listLength(server.slaves),
         listLength(server.slaves),
-        server.blockedclients,
+        server.blpop_blocked_clients,
         zmalloc_used_memory(),
         hmem,
         server.dirty,
@@ -5656,8 +5715,8 @@ static sds genRedisInfoString(void) {
             "vm_stats_io_newjobs_len:%lu\r\n"
             "vm_stats_io_processing_len:%lu\r\n"
             "vm_stats_io_processed_len:%lu\r\n"
-            "vm_stats_io_waiting_clients:%lu\r\n"
             "vm_stats_io_active_threads:%lu\r\n"
+            "vm_stats_blocked_clients:%lu\r\n"
             ,(unsigned long long) server.vm_max_memory,
             (unsigned long long) server.vm_page_size,
             (unsigned long long) server.vm_pages,
@@ -5668,8 +5727,8 @@ static sds genRedisInfoString(void) {
             (unsigned long) listLength(server.io_newjobs),
             (unsigned long) listLength(server.io_processing),
             (unsigned long) listLength(server.io_processed),
-            (unsigned long) listLength(server.io_clients),
-            (unsigned long) server.io_active_threads
+            (unsigned long) server.io_active_threads,
+            (unsigned long) server.vm_blocked_clients
         );
         unlockThreadedIO();
     }
@@ -5942,7 +6001,7 @@ static void blockForKeys(redisClient *c, robj **keys, int numkeys, time_t timeou
     /* Mark the client as a blocked client */
     c->flags |= REDIS_BLOCKED;
     aeDeleteFileEvent(server.el,c->fd,AE_READABLE);
-    server.blockedclients++;
+    server.blpop_blocked_clients++;
 }
 
 /* Unblock a client that's waiting in a blocking operation such as BLPOP */
@@ -5968,7 +6027,7 @@ static void unblockClientWaitingData(redisClient *c) {
     zfree(c->blockingkeys);
     c->blockingkeys = NULL;
     c->flags &= (~REDIS_BLOCKED);
-    server.blockedclients--;
+    server.blpop_blocked_clients--;
     /* Ok now we are ready to get read events from socket, note that we
      * can't trap errors here as it's possible that unblockClientWaitingDatas() is
      * called from freeClient() itself, and the only thing we can do
@@ -7061,7 +7120,7 @@ static void vmInit(void) {
     server.io_newjobs = listCreate();
     server.io_processing = listCreate();
     server.io_processed = listCreate();
-    server.io_clients = listCreate();
+    server.io_ready_clients = listCreate();
     pthread_mutex_init(&server.io_mutex,NULL);
     pthread_mutex_init(&server.obj_freelist_mutex,NULL);
     pthread_mutex_init(&server.io_swapfile_mutex,NULL);
@@ -7254,13 +7313,13 @@ static robj *vmReadObjectFromSwap(off_t page, int type) {
     if (server.vm_enabled) pthread_mutex_lock(&server.io_swapfile_mutex);
     if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
         redisLog(REDIS_WARNING,
-            "Unrecoverable VM problem in vmLoadObject(): can't seek: %s",
+            "Unrecoverable VM problem in vmReadObjectFromSwap(): can't seek: %s",
             strerror(errno));
         exit(1);
     }
     o = rdbLoadObject(type,server.vm_fp);
     if (o == NULL) {
-        redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmLoadObject(): can't load object from swap file: %s", strerror(errno));
+        redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmReadObjectFromSwap(): can't load object from swap file: %s", strerror(errno));
         exit(1);
     }
     if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
@@ -7275,7 +7334,7 @@ static robj *vmReadObjectFromSwap(off_t page, int type) {
 static robj *vmGenericLoadObject(robj *key, int preview) {
     robj *val;
 
-    redisAssert(key->storage == REDIS_VM_SWAPPED);
+    redisAssert(key->storage == REDIS_VM_SWAPPED || key->storage == REDIS_VM_LOADING);
     val = vmReadObjectFromSwap(key->vm.page,key->vtype);
     if (!preview) {
         key->storage = REDIS_VM_MEMORY;
@@ -7485,8 +7544,9 @@ static int deleteIfSwapped(redisDb *db, robj *key) {
 /* =================== Virtual Memory - Threaded I/O  ======================= */
 
 static void freeIOJob(iojob *j) {
-    if (j->type == REDIS_IOJOB_PREPARE_SWAP ||
-        j->type == REDIS_IOJOB_DO_SWAP)
+    if ((j->type == REDIS_IOJOB_PREPARE_SWAP ||
+        j->type == REDIS_IOJOB_DO_SWAP ||
+        j->type == REDIS_IOJOB_LOAD) && j->val != NULL)
         decrRefCount(j->val);
     decrRefCount(j->key);
     zfree(j);
@@ -7537,6 +7597,8 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
         assert(de != NULL);
         key = dictGetEntryKey(de);
         if (j->type == REDIS_IOJOB_LOAD) {
+            redisDb *db;
+
             /* Key loaded, bring it at home */
             key->storage = REDIS_VM_MEMORY;
             key->vm.atime = server.unixtime;
@@ -7545,7 +7607,12 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
                 (unsigned char*) key->ptr);
             server.vm_stats_swapped_objects--;
             server.vm_stats_swapins++;
+            dictGetEntryVal(de) = j->val;
+            incrRefCount(j->val);
+            db = j->db;
             freeIOJob(j);
+            /* Handle clients waiting for this key to be loaded. */
+            handleClientsBlockedOnSwappedKey(db,key);
         } else if (j->type == REDIS_IOJOB_PREPARE_SWAP) {
             /* Now we know the amount of pages required to swap this object.
              * Let's find some space for it, and queue this task again
@@ -7671,23 +7738,25 @@ static void vmCancelThreadedIOJob(robj *o) {
                     listDelNode(lists[i],ln);
                     break;
                 case 1: /* io_processing */
-                    /* Oh Shi- the thread is messing with the Job, and
-                     * probably with the object if this is a
-                     * PREPARE_SWAP or DO_SWAP job. Better to wait for the
-                     * job to move into the next queue... */
-                    if (job->type != REDIS_IOJOB_LOAD) {
-                        /* Yes, we try again and again until the job
-                         * is completed. */
-                        unlockThreadedIO();
-                        /* But let's wait some time for the I/O thread
-                         * to finish with this job. After all this condition
-                         * should be very rare. */
-                        usleep(1);
-                        goto again;
-                    } else {
-                        job->canceled = 1;
-                        break;
-                    }
+                    /* Oh Shi- the thread is messing with the Job:
+                     *
+                     * Probably it's accessing the object if this is a
+                     * PREPARE_SWAP or DO_SWAP job.
+                     * If it's a LOAD job it may be reading from disk and
+                     * if we don't wait for the job to terminate before to
+                     * cancel it, maybe in a few microseconds data can be
+                     * corrupted in this pages. So the short story is:
+                     *
+                     * Better to wait for the job to move into the
+                     * next queue (processed)... */
+
+                    /* We try again and again until the job is completed. */
+                    unlockThreadedIO();
+                    /* But let's wait some time for the I/O thread
+                     * to finish with this job. After all this condition
+                     * should be very rare. */
+                    usleep(1);
+                    goto again;
                 case 2: /* io_processed */
                     /* The job was already processed, that's easy...
                      * just mark it as canceled so that we'll ignore it
@@ -7740,6 +7809,7 @@ static void *IOThreadEntryPoint(void *arg) {
 
         /* Process the Job */
         if (j->type == REDIS_IOJOB_LOAD) {
+            j->val = vmReadObjectFromSwap(j->page,j->key->vtype);
         } else if (j->type == REDIS_IOJOB_PREPARE_SWAP) {
             FILE *fp = fopen("/dev/null","w+");
             j->pages = rdbSavedObjectPages(j->val,fp);
@@ -7843,16 +7913,154 @@ static int vmSwapObjectThreaded(robj *key, robj *val, redisDb *db) {
 
 /* ============ Virtual Memory - Blocking clients on missing keys =========== */
 
+/* This function makes the clinet 'c' waiting for the key 'key' to be loaded.
+ * If there is not already a job loading the key, it is craeted.
+ * The key is added to the io_keys list in the client structure, and also
+ * in the hash table mapping swapped keys to waiting clients, that is,
+ * server.io_waited_keys. */
+static int waitForSwappedKey(redisClient *c, robj *key) {
+    struct dictEntry *de;
+    robj *o;
+    list *l;
+
+    /* If the key does not exist or is already in RAM we don't need to
+     * block the client at all. */
+    de = dictFind(c->db->dict,key);
+    if (de == NULL) return 0;
+    o = dictGetEntryKey(de);
+    if (o->storage == REDIS_VM_MEMORY) {
+        return 0;
+    } else if (o->storage == REDIS_VM_SWAPPING) {
+        /* We were swapping the key, undo it! */
+        vmCancelThreadedIOJob(o);
+        return 0;
+    }
+    
+    /* OK: the key is either swapped, or being loaded just now. */
+
+    /* Add the key to the list of keys this client is waiting for.
+     * This maps clients to keys they are waiting for. */
+    listAddNodeTail(c->io_keys,key);
+    incrRefCount(key);
+
+    /* Add the client to the swapped keys => clients waiting map. */
+    de = dictFind(c->db->io_keys,key);
+    if (de == NULL) {
+        int retval;
+
+        /* For every key we take a list of clients blocked for it */
+        l = listCreate();
+        retval = dictAdd(c->db->io_keys,key,l);
+        incrRefCount(key);
+        assert(retval == DICT_OK);
+    } else {
+        l = dictGetEntryVal(de);
+    }
+    listAddNodeTail(l,c);
+
+    /* Are we already loading the key from disk? If not create a job */
+    if (o->storage == REDIS_VM_SWAPPED) {
+        iojob *j;
+
+        o->storage = REDIS_VM_LOADING;
+        j = zmalloc(sizeof(*j));
+        j->type = REDIS_IOJOB_LOAD;
+        j->db = c->db;
+        j->key = dupStringObject(key);
+        j->key->vtype = o->vtype;
+        j->page = o->vm.page;
+        j->val = NULL;
+        j->canceled = 0;
+        j->thread = (pthread_t) -1;
+        lockThreadedIO();
+        queueIOJob(j);
+        unlockThreadedIO();
+    }
+    return 1;
+}
+
 /* Is this client attempting to run a command against swapped keys?
- * If so, block it ASAP, load the keys in background, then resume it.4
+ * If so, block it ASAP, load the keys in background, then resume it.
  *
- * The improtat thing about this function is that it can fail! If keys will
- * still be swapped when the client is resumed, a few of key lookups will
- * just block loading keys from disk. */
-#if 0
-static void blockClientOnSwappedKeys(redisClient *c) {
+ * The important idea about this function is that it can fail! If keys will
+ * still be swapped when the client is resumed, this key lookups will
+ * just block loading keys from disk. In practical terms this should only
+ * happen with SORT BY command or if there is a bug in this function.
+ *
+ * Return 1 if the client is marked as blocked, 0 if the client can
+ * continue as the keys it is going to access appear to be in memory. */
+static int blockClientOnSwappedKeys(struct redisCommand *cmd, redisClient *c) {
+    if (cmd->proc == getCommand) {
+        waitForSwappedKey(c,c->argv[1]);
+    }
+    /* If the client was blocked for at least one key, mark it as blocked. */
+    if (listLength(c->io_keys)) {
+        c->flags |= REDIS_IO_WAIT;
+        aeDeleteFileEvent(server.el,c->fd,AE_READABLE);
+        server.vm_blocked_clients++;
+        return 1;
+    } else {
+        return 0;
+    }
+}
+
+/* Remove the 'key' from the list of blocked keys for a given client.
+ *
+ * The function returns 1 when there are no longer blocking keys after
+ * the current one was removed (and the client can be unblocked). */
+static int dontWaitForSwappedKey(redisClient *c, robj *key) {
+    list *l;
+    listNode *ln;
+    listIter li;
+    struct dictEntry *de;
+
+    /* Remove the key from the list of keys this client is waiting for. */
+    listRewind(c->io_keys,&li);
+    while ((ln = listNext(&li)) != NULL) {
+        if (compareStringObjects(ln->value,key) == 0) {
+            listDelNode(c->io_keys,ln);
+            break;
+        }
+    }
+    assert(ln != NULL);
+
+    /* Remove the client form the key => waiting clients map. */
+    de = dictFind(c->db->io_keys,key);
+    assert(de != NULL);
+    l = dictGetEntryVal(de);
+    ln = listSearchKey(l,c);
+    assert(ln != NULL);
+    listDelNode(l,ln);
+    if (listLength(l) == 0)
+        dictDelete(c->db->io_keys,key);
+
+    return listLength(c->io_keys) == 0;
+}
+
+static void handleClientsBlockedOnSwappedKey(redisDb *db, robj *key) {
+    struct dictEntry *de;
+    list *l;
+    listNode *ln;
+    int len;
+
+    de = dictFind(db->io_keys,key);
+    if (!de) return;
+
+    l = dictGetEntryVal(de);
+    len = listLength(l);
+    /* Note: we can't use something like while(listLength(l)) as the list
+     * can be freed by the calling function when we remove the last element. */
+    while (len--) {
+        ln = listFirst(l);
+        redisClient *c = ln->value;
+
+        if (dontWaitForSwappedKey(c,key)) {
+            /* Put the client in the list of clients ready to go as we
+             * loaded all the keys about it. */
+            listAddNodeTail(server.io_ready_clients,c);
+        }
+    }
 }
-#endif
 
 /* ================================= Debugging ============================== */
 
@@ -8020,6 +8228,7 @@ int main(int argc, char **argv) {
             redisLog(REDIS_NOTICE,"DB loaded from disk");
     }
     redisLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
+    aeSetBeforeSleepProc(server.el,beforeSleep);
     aeMain(server.el);
     aeDeleteEventLoop(server.el);
     return 0;