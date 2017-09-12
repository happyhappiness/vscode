#include "redis.h"

#include <fcntl.h>
#include <pthread.h>
#include <math.h>
#include <signal.h>

/* dscache.c - Disk store cache for disk store backend.
 *
 * When Redis is configured for using disk as backend instead of memory, the
 * memory is used as a cache, so that recently accessed keys are taken in
 * memory for fast read and write operations.
 *
 * Modified keys are marked to be flushed on disk, and will be flushed
 * as long as the maxium configured flush time elapsed.
 *
 * This file implements the whole caching subsystem and contains further
 * documentation. */

/* TODO:
 *
 * - The WATCH helper will be used to signal the cache system
 *   we need to flush a given key/dbid into disk, adding this key/dbid
 *   pair into a server.ds_cache_dirty linked list AND hash table (so that we
 *   don't add the same thing multiple times).
 *
 * - cron() checks if there are elements on this list. When there are things
 *   to flush, we create an IO Job for the I/O thread.
 *   NOTE: We disalbe object sharing when server.ds_enabled == 1 so objects
 *   that are referenced an IO job for flushing on disk are marked as
 *   o->storage == REDIS_DS_SAVING.
 *
 * - This is what we do on key lookup:
 *   1) The key already exists in memory. object->storage == REDIS_DS_MEMORY
 *      or it is object->storage == REDIS_DS_DIRTY:
 *      We don't do nothing special, lookup, return value object pointer.
 *   2) The key is in memory but object->storage == REDIS_DS_SAVING.
 *      When this happens we block waiting for the I/O thread to process
 *      this object. Then continue.
 *   3) The key is not in memory. We block to load the key from disk.
 *      Of course the key may not be present at all on the disk store as well,
 *      in such case we just detect this condition and continue, returning
 *      NULL from lookup.
 *
 * - Preloading of needed keys:
 *   1) As it was done with VM, also with this new system we try preloading
 *      keys a client is going to use. We block the client, load keys
 *      using the I/O thread, unblock the client. Same code as VM more or less.
 *
 * - Reclaiming memory.
 *   In cron() we detect our memory limit was reached. What we
 *   do is deleting keys that are REDIS_DS_MEMORY, using LRU.
 *
 *   If this is not enough to return again under the memory limits we also
 *   start to flush keys that need to be synched on disk synchronously,
 *   removing it from the memory. We do this blocking as memory limit is a
 *   much "harder" barrirer in the new design.
 *
 * - IO thread operations are no longer stopped for sync loading/saving of
 *   things. When a key is found to be in the process of being saved
 *   we simply wait for the IO thread to end its work.
 *
 *   Otherwise if there is to load a key without any IO thread operation
 *   just started it is blocking-loaded in the lookup function.
 *
 * - What happens when an object is destroyed?
 *
 *   If o->storage == REDIS_DS_MEMORY then we simply destory the object.
 *   If o->storage == REDIS_DS_DIRTY we can still remove the object. It had
 *                    changes not flushed on disk, but is being removed so
 *                    who cares.
 *   if o->storage == REDIS_DS_SAVING then the object is being saved so
 *                    it is impossible that its refcount == 1, must be at
 *                    least two. When the object is saved the storage will
 *                    be set back to DS_MEMORY.
 *
 * - What happens when keys are deleted?
 *
 *   We simply schedule a key flush operation as usually, but when the
 *   IO thread will be created the object pointer will be set to NULL
 *   so the IO thread will know that the work to do is to delete the key
 *   from the disk store.
 *
 * - What happens with MULTI/EXEC?
 *
 *   Good question.
 */

/* Virtual Memory is composed mainly of two subsystems:
 * - Blocking Virutal Memory
 * - Threaded Virtual Memory I/O
 * The two parts are not fully decoupled, but functions are split among two
 * different sections of the source code (delimited by comments) in order to
 * make more clear what functionality is about the blocking VM and what about
 * the threaded (not blocking) VM.
 *
 * Redis VM design:
 *
 * Redis VM is a blocking VM (one that blocks reading swapped values from
 * disk into memory when a value swapped out is needed in memory) that is made
 * unblocking by trying to examine the command argument vector in order to
 * load in background values that will likely be needed in order to exec
 * the command. The command is executed only once all the relevant keys
 * are loaded into memory.
 *
 * This basically is almost as simple of a blocking VM, but almost as parallel
 * as a fully non-blocking VM.
 */

void spawnIOThread(void);

/* =================== Virtual Memory - Blocking Side  ====================== */

void dsInit(void) {
    int pipefds[2];
    size_t stacksize;

    zmalloc_enable_thread_safeness(); /* we need thread safe zmalloc() */

    redisLog(REDIS_NOTICE,"Initializing Disk Store at %s", server.ds_path);
    /* Open Disk Store */
    if (dsOpen() != REDIS_OK) {
        redisLog(REDIS_WARNING,"Fatal error opening disk store. Exiting.");
        exit(1);
    };

    /* Initialize threaded I/O for Object Cache */
    server.io_newjobs = listCreate();
    server.io_processing = listCreate();
    server.io_processed = listCreate();
    server.io_ready_clients = listCreate();
    pthread_mutex_init(&server.io_mutex,NULL);
    server.io_active_threads = 0;
    if (pipe(pipefds) == -1) {
        redisLog(REDIS_WARNING,"Unable to intialized DS: pipe(2): %s. Exiting."
            ,strerror(errno));
        exit(1);
    }
    server.io_ready_pipe_read = pipefds[0];
    server.io_ready_pipe_write = pipefds[1];
    redisAssert(anetNonBlock(NULL,server.io_ready_pipe_read) != ANET_ERR);
    /* LZF requires a lot of stack */
    pthread_attr_init(&server.io_threads_attr);
    pthread_attr_getstacksize(&server.io_threads_attr, &stacksize);

    /* Solaris may report a stacksize of 0, let's set it to 1 otherwise
     * multiplying it by 2 in the while loop later will not really help ;) */
    if (!stacksize) stacksize = 1;

    while (stacksize < REDIS_THREAD_STACK_SIZE) stacksize *= 2;
    pthread_attr_setstacksize(&server.io_threads_attr, stacksize);
    /* Listen for events in the threaded I/O pipe */
    if (aeCreateFileEvent(server.el, server.io_ready_pipe_read, AE_READABLE,
        vmThreadedIOCompletedJob, NULL) == AE_ERR)
        oom("creating file event");

    /* Spawn our I/O thread */
    spawnIOThread();
}

/* Compute how good candidate the specified object is for eviction.
 * An higher number means a better candidate. */
double computeObjectSwappability(robj *o) {
    /* actual age can be >= minage, but not < minage. As we use wrapping
     * 21 bit clocks with minutes resolution for the LRU. */
    return (double) estimateObjectIdleTime(o);
}

/* Try to free one entry from the diskstore object cache */
int cacheFreeOneEntry(void) {
    int j, i;
    struct dictEntry *best = NULL;
    double best_swappability = 0;
    redisDb *best_db = NULL;
    robj *val;
    sds key;

    for (j = 0; j < server.dbnum; j++) {
        redisDb *db = server.db+j;
        /* Why maxtries is set to 100?
         * Because this way (usually) we'll find 1 object even if just 1% - 2%
         * are swappable objects */
        int maxtries = 100;

        if (dictSize(db->dict) == 0) continue;
        for (i = 0; i < 5; i++) {
            dictEntry *de;
            double swappability;

            if (maxtries) maxtries--;
            de = dictGetRandomKey(db->dict);
            val = dictGetEntryVal(de);
            /* Only swap objects that are currently in memory.
             *
             * Also don't swap shared objects: not a good idea in general and
             * we need to ensure that the main thread does not touch the
             * object while the I/O thread is using it, but we can't
             * control other keys without adding additional mutex. */
            if (val->storage != REDIS_DS_MEMORY) {
                if (maxtries) i--; /* don't count this try */
                continue;
            }
            swappability = computeObjectSwappability(val);
            if (!best || swappability > best_swappability) {
                best = de;
                best_swappability = swappability;
                best_db = db;
            }
        }
    }
    if (best == NULL) {
        /* FIXME: If there are objects marked as DS_DIRTY or DS_SAVING
         * let's wait for this objects to be clear and retry...
         *
         * Object cache vm limit is considered an hard limit. */
        return REDIS_ERR;
    }
    key = dictGetEntryKey(best);
    val = dictGetEntryVal(best);

    redisLog(REDIS_DEBUG,"Key selected for cache eviction: %s swappability:%f",
        key, best_swappability);

    /* Delete this key from memory */
    {
        robj *kobj = createStringObject(key,sdslen(key));
        dbDelete(best_db,kobj);
        decrRefCount(kobj);
    }
}

/* Return true if it's safe to swap out objects in a given moment.
 * Basically we don't want to swap objects out while there is a BGSAVE
 * or a BGAEOREWRITE running in backgroud. */
int dsCanTouchDiskStore(void) {
    return (server.bgsavechildpid == -1 && server.bgrewritechildpid == -1);
}

/* =================== Virtual Memory - Threaded I/O  ======================= */

void freeIOJob(iojob *j) {
    decrRefCount(j->key);
    decrRefCount(j->val);
    zfree(j);
}

/* Every time a thread finished a Job, it writes a byte into the write side
 * of an unix pipe in order to "awake" the main thread, and this function
 * is called. */
void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
            int mask)
{
    char buf[1];
    int retval, processed = 0, toprocess = -1;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(mask);
    REDIS_NOTUSED(privdata);

    /* For every byte we read in the read side of the pipe, there is one
     * I/O job completed to process. */
    while((retval = read(fd,buf,1)) == 1) {
        iojob *j;
        listNode *ln;
        struct dictEntry *de;

        redisLog(REDIS_DEBUG,"Processing I/O completed job");

        /* Get the processed element (the oldest one) */
        lockThreadedIO();
        redisAssert(listLength(server.io_processed) != 0);
        if (toprocess == -1) {
            toprocess = (listLength(server.io_processed)*REDIS_MAX_COMPLETED_JOBS_PROCESSED)/100;
            if (toprocess <= 0) toprocess = 1;
        }
        ln = listFirst(server.io_processed);
        j = ln->value;
        listDelNode(server.io_processed,ln);
        unlockThreadedIO();

        /* Post process it in the main thread, as there are things we
         * can do just here to avoid race conditions and/or invasive locks */
        redisLog(REDIS_DEBUG,"COMPLETED Job type: %d, ID %p, key: %s", j->type, (void*)j->id, (unsigned char*)j->key->ptr);
        de = dictFind(j->db->dict,j->key->ptr);
        redisAssert(de != NULL);
        if (j->type == REDIS_IOJOB_LOAD) {
            dbAdd(j->db,j->key,j->val);
            freeIOJob(j);
            /* FIXME: notify clients waiting for this key */
        } else if (j->type == REDIS_IOJOB_SAVE) {
            redisAssert(j->val->storage == REDIS_DS_SAVING);
            j->val->storage = REDIS_DS_MEMORY;
            freeIOJob(j);
        }
        processed++;
        if (processed == toprocess) return;
    }
    if (retval < 0 && errno != EAGAIN) {
        redisLog(REDIS_WARNING,
            "WARNING: read(2) error in vmThreadedIOCompletedJob() %s",
            strerror(errno));
    }
}

void lockThreadedIO(void) {
    pthread_mutex_lock(&server.io_mutex);
}

void unlockThreadedIO(void) {
    pthread_mutex_unlock(&server.io_mutex);
}

void *IOThreadEntryPoint(void *arg) {
    iojob *j;
    listNode *ln;
    REDIS_NOTUSED(arg);

    pthread_detach(pthread_self());
    while(1) {
        /* Get a new job to process */
        lockThreadedIO();
        if (listLength(server.io_newjobs) == 0) {
            /* No new jobs in queue, exit. */
            redisLog(REDIS_DEBUG,"Thread %ld exiting, nothing to do",
                (long) pthread_self());
            server.io_active_threads--;
            unlockThreadedIO();
            return NULL;
        }
        ln = listFirst(server.io_newjobs);
        j = ln->value;
        listDelNode(server.io_newjobs,ln);
        /* Add the job in the processing queue */
        j->thread = pthread_self();
        listAddNodeTail(server.io_processing,j);
        ln = listLast(server.io_processing); /* We use ln later to remove it */
        unlockThreadedIO();
        redisLog(REDIS_DEBUG,"Thread %ld got a new job (type %d): %p about key '%s'",
            (long) pthread_self(), j->type, (void*)j, (char*)j->key->ptr);

        /* Process the Job */
        if (j->type == REDIS_IOJOB_LOAD) {
            vmpointer *vp = (vmpointer*)j->id;
            j->val = vmReadObjectFromSwap(j->page,vp->vtype);
        } else if (j->type == REDIS_IOJOB_PREPARE_SWAP) {
            j->pages = rdbSavedObjectPages(j->val);
        } else if (j->type == REDIS_IOJOB_DO_SWAP) {
            if (vmWriteObjectOnSwap(j->val,j->page) == REDIS_ERR)
                j->canceled = 1;
        }

        /* Done: insert the job into the processed queue */
        redisLog(REDIS_DEBUG,"Thread %ld completed the job: %p (key %s)",
            (long) pthread_self(), (void*)j, (char*)j->key->ptr);
        lockThreadedIO();
        listDelNode(server.io_processing,ln);
        listAddNodeTail(server.io_processed,j);
        unlockThreadedIO();

        /* Signal the main thread there is new stuff to process */
        redisAssert(write(server.io_ready_pipe_write,"x",1) == 1);
    }
    return NULL; /* never reached */
}

void spawnIOThread(void) {
    pthread_t thread;
    sigset_t mask, omask;
    int err;

    sigemptyset(&mask);
    sigaddset(&mask,SIGCHLD);
    sigaddset(&mask,SIGHUP);
    sigaddset(&mask,SIGPIPE);
    pthread_sigmask(SIG_SETMASK, &mask, &omask);
    while ((err = pthread_create(&thread,&server.io_threads_attr,IOThreadEntryPoint,NULL)) != 0) {
        redisLog(REDIS_WARNING,"Unable to spawn an I/O thread: %s",
            strerror(err));
        usleep(1000000);
    }
    pthread_sigmask(SIG_SETMASK, &omask, NULL);
    server.io_active_threads++;
}

/* We need to wait for the last thread to exit before we are able to
 * fork() in order to BGSAVE or BGREWRITEAOF. */
void waitEmptyIOJobsQueue(void) {
    while(1) {
        int io_processed_len;

        lockThreadedIO();
        if (listLength(server.io_newjobs) == 0 &&
            listLength(server.io_processing) == 0 &&
            server.io_active_threads == 0)
        {
            unlockThreadedIO();
            return;
        }
        /* While waiting for empty jobs queue condition we post-process some
         * finshed job, as I/O threads may be hanging trying to write against
         * the io_ready_pipe_write FD but there are so much pending jobs that
         * it's blocking. */
        io_processed_len = listLength(server.io_processed);
        unlockThreadedIO();
        if (io_processed_len) {
            vmThreadedIOCompletedJob(NULL,server.io_ready_pipe_read,
                                                        (void*)0xdeadbeef,0);
            usleep(1000); /* 1 millisecond */
        } else {
            usleep(10000); /* 10 milliseconds */
        }
    }
}

/* This function must be called while with threaded IO locked */
void queueIOJob(iojob *j) {
    redisLog(REDIS_DEBUG,"Queued IO Job %p type %d about key '%s'\n",
        (void*)j, j->type, (char*)j->key->ptr);
    listAddNodeTail(server.io_newjobs,j);
    if (server.io_active_threads < server.vm_max_threads)
        spawnIOThread();
}

int vmSwapObjectThreaded(robj *key, robj *val, redisDb *db) {
    iojob *j;

    j = zmalloc(sizeof(*j));
    j->type = REDIS_IOJOB_PREPARE_SWAP;
    j->db = db;
    j->key = key;
    incrRefCount(key);
    j->id = j->val = val;
    incrRefCount(val);
    j->canceled = 0;
    j->thread = (pthread_t) -1;
    val->storage = REDIS_VM_SWAPPING;

    lockThreadedIO();
    queueIOJob(j);
    unlockThreadedIO();
    return REDIS_OK;
}

/* ============ Virtual Memory - Blocking clients on missing keys =========== */

/* This function makes the clinet 'c' waiting for the key 'key' to be loaded.
 * If there is not already a job loading the key, it is craeted.
 * The key is added to the io_keys list in the client structure, and also
 * in the hash table mapping swapped keys to waiting clients, that is,
 * server.io_waited_keys. */
int waitForSwappedKey(redisClient *c, robj *key) {
    struct dictEntry *de;
    robj *o;
    list *l;

    /* If the key does not exist or is already in RAM we don't need to
     * block the client at all. */
    de = dictFind(c->db->dict,key->ptr);
    if (de == NULL) return 0;
    o = dictGetEntryVal(de);
    if (o->storage == REDIS_VM_MEMORY) {
        return 0;
    } else if (o->storage == REDIS_VM_SWAPPING) {
        /* We were swapping the key, undo it! */
        vmCancelThreadedIOJob(o);
        return 0;
    }

    /* OK: the key is either swapped, or being loaded just now. */

    /* Add the key to the list of keys this client is waiting for.
     * This maps clients to keys they are waiting for. */
    listAddNodeTail(c->io_keys,key);
    incrRefCount(key);

    /* Add the client to the swapped keys => clients waiting map. */
    de = dictFind(c->db->io_keys,key);
    if (de == NULL) {
        int retval;

        /* For every key we take a list of clients blocked for it */
        l = listCreate();
        retval = dictAdd(c->db->io_keys,key,l);
        incrRefCount(key);
        redisAssert(retval == DICT_OK);
    } else {
        l = dictGetEntryVal(de);
    }
    listAddNodeTail(l,c);

    /* Are we already loading the key from disk? If not create a job */
    if (o->storage == REDIS_VM_SWAPPED) {
        iojob *j;
        vmpointer *vp = (vmpointer*)o;

        o->storage = REDIS_VM_LOADING;
        j = zmalloc(sizeof(*j));
        j->type = REDIS_IOJOB_LOAD;
        j->db = c->db;
        j->id = (robj*)vp;
        j->key = key;
        incrRefCount(key);
        j->page = vp->page;
        j->val = NULL;
        j->canceled = 0;
        j->thread = (pthread_t) -1;
        lockThreadedIO();
        queueIOJob(j);
        unlockThreadedIO();
    }
    return 1;
}

/* Preload keys for any command with first, last and step values for
 * the command keys prototype, as defined in the command table. */
void waitForMultipleSwappedKeys(redisClient *c, struct redisCommand *cmd, int argc, robj **argv) {
    int j, last;
    if (cmd->vm_firstkey == 0) return;
    last = cmd->vm_lastkey;
    if (last < 0) last = argc+last;
    for (j = cmd->vm_firstkey; j <= last; j += cmd->vm_keystep) {
        redisAssert(j < argc);
        waitForSwappedKey(c,argv[j]);
    }
}

/* Preload keys needed for the ZUNIONSTORE and ZINTERSTORE commands.
 * Note that the number of keys to preload is user-defined, so we need to
 * apply a sanity check against argc. */
void zunionInterBlockClientOnSwappedKeys(redisClient *c, struct redisCommand *cmd, int argc, robj **argv) {
    int i, num;
    REDIS_NOTUSED(cmd);

    num = atoi(argv[2]->ptr);
    if (num > (argc-3)) return;
    for (i = 0; i < num; i++) {
        waitForSwappedKey(c,argv[3+i]);
    }
}

/* Preload keys needed to execute the entire MULTI/EXEC block.
 *
 * This function is called by blockClientOnSwappedKeys when EXEC is issued,
 * and will block the client when any command requires a swapped out value. */
void execBlockClientOnSwappedKeys(redisClient *c, struct redisCommand *cmd, int argc, robj **argv) {
    int i, margc;
    struct redisCommand *mcmd;
    robj **margv;
    REDIS_NOTUSED(cmd);
    REDIS_NOTUSED(argc);
    REDIS_NOTUSED(argv);

    if (!(c->flags & REDIS_MULTI)) return;
    for (i = 0; i < c->mstate.count; i++) {
        mcmd = c->mstate.commands[i].cmd;
        margc = c->mstate.commands[i].argc;
        margv = c->mstate.commands[i].argv;

        if (mcmd->vm_preload_proc != NULL) {
            mcmd->vm_preload_proc(c,mcmd,margc,margv);
        } else {
            waitForMultipleSwappedKeys(c,mcmd,margc,margv);
        }
    }
}

/* Is this client attempting to run a command against swapped keys?
 * If so, block it ASAP, load the keys in background, then resume it.
 *
 * The important idea about this function is that it can fail! If keys will
 * still be swapped when the client is resumed, this key lookups will
 * just block loading keys from disk. In practical terms this should only
 * happen with SORT BY command or if there is a bug in this function.
 *
 * Return 1 if the client is marked as blocked, 0 if the client can
 * continue as the keys it is going to access appear to be in memory. */
int blockClientOnSwappedKeys(redisClient *c, struct redisCommand *cmd) {
    if (cmd->vm_preload_proc != NULL) {
        cmd->vm_preload_proc(c,cmd,c->argc,c->argv);
    } else {
        waitForMultipleSwappedKeys(c,cmd,c->argc,c->argv);
    }

    /* If the client was blocked for at least one key, mark it as blocked. */
    if (listLength(c->io_keys)) {
        c->flags |= REDIS_IO_WAIT;
        aeDeleteFileEvent(server.el,c->fd,AE_READABLE);
        server.vm_blocked_clients++;
        return 1;
    } else {
        return 0;
    }
}

/* Remove the 'key' from the list of blocked keys for a given client.
 *
 * The function returns 1 when there are no longer blocking keys after
 * the current one was removed (and the client can be unblocked). */
int dontWaitForSwappedKey(redisClient *c, robj *key) {
    list *l;
    listNode *ln;
    listIter li;
    struct dictEntry *de;

    /* The key object might be destroyed when deleted from the c->io_keys
     * list (and the "key" argument is physically the same object as the
     * object inside the list), so we need to protect it. */
    incrRefCount(key);

    /* Remove the key from the list of keys this client is waiting for. */
    listRewind(c->io_keys,&li);
    while ((ln = listNext(&li)) != NULL) {
        if (equalStringObjects(ln->value,key)) {
            listDelNode(c->io_keys,ln);
            break;
        }
    }
    redisAssert(ln != NULL);

    /* Remove the client form the key => waiting clients map. */
    de = dictFind(c->db->io_keys,key);
    redisAssert(de != NULL);
    l = dictGetEntryVal(de);
    ln = listSearchKey(l,c);
    redisAssert(ln != NULL);
    listDelNode(l,ln);
    if (listLength(l) == 0)
        dictDelete(c->db->io_keys,key);

    decrRefCount(key);
    return listLength(c->io_keys) == 0;
}

/* Every time we now a key was loaded back in memory, we handle clients
 * waiting for this key if any. */
void handleClientsBlockedOnSwappedKey(redisDb *db, robj *key) {
    struct dictEntry *de;
    list *l;
    listNode *ln;
    int len;

    de = dictFind(db->io_keys,key);
    if (!de) return;

    l = dictGetEntryVal(de);
    len = listLength(l);
    /* Note: we can't use something like while(listLength(l)) as the list
     * can be freed by the calling function when we remove the last element. */
    while (len--) {
        ln = listFirst(l);
        redisClient *c = ln->value;

        if (dontWaitForSwappedKey(c,key)) {
            /* Put the client in the list of clients ready to go as we
             * loaded all the keys about it. */
            listAddNodeTail(server.io_ready_clients,c);
        }
    }
}
