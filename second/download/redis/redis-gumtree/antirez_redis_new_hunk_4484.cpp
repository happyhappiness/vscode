            "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>]\r\n"));
    }
}

static struct redisFunctionSym symsTable[] = {
{"freeStringObject", (unsigned long)freeStringObject},
{"freeListObject", (unsigned long)freeListObject},
{"freeSetObject", (unsigned long)freeSetObject},
{"decrRefCount", (unsigned long)decrRefCount},
{"createObject", (unsigned long)createObject},
{"freeClient", (unsigned long)freeClient},
{"rdbLoad", (unsigned long)rdbLoad},
{"addReply", (unsigned long)addReply},
{"addReplySds", (unsigned long)addReplySds},
{"incrRefCount", (unsigned long)incrRefCount},
{"rdbSaveBackground", (unsigned long)rdbSaveBackground},
{"createStringObject", (unsigned long)createStringObject},
{"replicationFeedSlaves", (unsigned long)replicationFeedSlaves},
{"syncWithMaster", (unsigned long)syncWithMaster},
{"tryObjectSharing", (unsigned long)tryObjectSharing},
{"removeExpire", (unsigned long)removeExpire},
{"expireIfNeeded", (unsigned long)expireIfNeeded},
{"deleteIfVolatile", (unsigned long)deleteIfVolatile},
{"deleteKey", (unsigned long)deleteKey},
{"getExpire", (unsigned long)getExpire},
{"setExpire", (unsigned long)setExpire},
{"updateSalvesWaitingBgsave", (unsigned long)updateSalvesWaitingBgsave},
{"freeMemoryIfNeeded", (unsigned long)freeMemoryIfNeeded},
{"authCommand", (unsigned long)authCommand},
{"pingCommand", (unsigned long)pingCommand},
{"echoCommand", (unsigned long)echoCommand},
{"setCommand", (unsigned long)setCommand},
{"setnxCommand", (unsigned long)setnxCommand},
{"getCommand", (unsigned long)getCommand},
{"delCommand", (unsigned long)delCommand},
{"existsCommand", (unsigned long)existsCommand},
{"incrCommand", (unsigned long)incrCommand},
{"decrCommand", (unsigned long)decrCommand},
{"incrbyCommand", (unsigned long)incrbyCommand},
{"decrbyCommand", (unsigned long)decrbyCommand},
{"selectCommand", (unsigned long)selectCommand},
{"randomkeyCommand", (unsigned long)randomkeyCommand},
{"keysCommand", (unsigned long)keysCommand},
{"dbsizeCommand", (unsigned long)dbsizeCommand},
{"lastsaveCommand", (unsigned long)lastsaveCommand},
{"saveCommand", (unsigned long)saveCommand},
{"bgsaveCommand", (unsigned long)bgsaveCommand},
{"shutdownCommand", (unsigned long)shutdownCommand},
{"moveCommand", (unsigned long)moveCommand},
{"renameCommand", (unsigned long)renameCommand},
{"renamenxCommand", (unsigned long)renamenxCommand},
{"lpushCommand", (unsigned long)lpushCommand},
{"rpushCommand", (unsigned long)rpushCommand},
{"lpopCommand", (unsigned long)lpopCommand},
{"rpopCommand", (unsigned long)rpopCommand},
{"llenCommand", (unsigned long)llenCommand},
{"lindexCommand", (unsigned long)lindexCommand},
{"lrangeCommand", (unsigned long)lrangeCommand},
{"ltrimCommand", (unsigned long)ltrimCommand},
{"typeCommand", (unsigned long)typeCommand},
{"lsetCommand", (unsigned long)lsetCommand},
{"saddCommand", (unsigned long)saddCommand},
{"sremCommand", (unsigned long)sremCommand},
{"smoveCommand", (unsigned long)smoveCommand},
{"sismemberCommand", (unsigned long)sismemberCommand},
{"scardCommand", (unsigned long)scardCommand},
{"sinterCommand", (unsigned long)sinterCommand},
{"sinterstoreCommand", (unsigned long)sinterstoreCommand},
{"sunionCommand", (unsigned long)sunionCommand},
{"sunionstoreCommand", (unsigned long)sunionstoreCommand},
{"sdiffCommand", (unsigned long)sdiffCommand},
{"sdiffstoreCommand", (unsigned long)sdiffstoreCommand},
{"syncCommand", (unsigned long)syncCommand},
{"flushdbCommand", (unsigned long)flushdbCommand},
{"flushallCommand", (unsigned long)flushallCommand},
{"sortCommand", (unsigned long)sortCommand},
{"lremCommand", (unsigned long)lremCommand},
{"infoCommand", (unsigned long)infoCommand},
{"mgetCommand", (unsigned long)mgetCommand},
{"monitorCommand", (unsigned long)monitorCommand},
{"expireCommand", (unsigned long)expireCommand},
{"getSetCommand", (unsigned long)getSetCommand},
{"ttlCommand", (unsigned long)ttlCommand},
{"slaveofCommand", (unsigned long)slaveofCommand},
{"debugCommand", (unsigned long)debugCommand},
{"processCommand", (unsigned long)processCommand},
{"setupSigSegvAction", (unsigned long)setupSigSegvAction},
{"segvHandler", (unsigned long)segvHandler},
{"readQueryFromClient", (unsigned long)readQueryFromClient},
{NULL,0}
};

/* This function try to convert a pointer into a function name. It's used in
 * oreder to provide a backtrace under segmentation fault that's able to
 * display functions declared as static (otherwise the backtrace is useless). */
static char *findFuncName(void *pointer, unsigned long *offset){
    int i, ret = -1;
    unsigned long off, minoff = 0;

    /* Try to match against the Symbol with the smallest offset */
    for (i=0; symsTable[i].pointer; i++) {
        unsigned long lp = (unsigned long) pointer;

        if (lp != (unsigned long)-1 && lp >= symsTable[i].pointer) {
            off=lp-symsTable[i].pointer;
            if (ret < 0 || off < minoff) {
                minoff=off;
                ret=i;
            }
        }
    }
    if (ret == -1) return NULL;
    *offset = minoff;
    return symsTable[ret].name;
}

static void *getMcontextEip(ucontext_t *uc) {
#if defined(__FreeBSD__)
    return (void*) uc->uc_mcontext.mc_eip;
#elif defined(__dietlibc__)
    return (void*) uc->uc_mcontext.eip;
#elif defined(__APPLE__)
    return (void*) uc->uc_mcontext->__ss.__eip;
#else /* Linux */
    return (void*) uc->uc_mcontext.gregs[REG_EIP];
#endif
}

static void segvHandler(int sig, siginfo_t *info, void *secret) {
    void *trace[100];
    char **messages = NULL;
    int i, trace_size = 0;
    unsigned long offset=0;
    time_t uptime = time(NULL)-server.stat_starttime;
    ucontext_t *uc = (ucontext_t*) secret;
    REDIS_NOTUSED(info);

    redisLog(REDIS_WARNING,
        "======= Ooops! Redis %s got signal: -%d- =======", REDIS_VERSION, sig);
    redisLog(REDIS_WARNING, "%s", sdscatprintf(sdsempty(),
        "redis_version:%s; "
        "uptime_in_seconds:%d; "
        "connected_clients:%d; "
        "connected_slaves:%d; "
        "used_memory:%zu; "
