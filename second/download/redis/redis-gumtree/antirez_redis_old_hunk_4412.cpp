    }
}

#ifdef HAVE_BACKTRACE
static struct redisFunctionSym symsTable[] = {
{"compareStringObjects", (unsigned long)compareStringObjects},
{"isStringRepresentableAsLong", (unsigned long)isStringRepresentableAsLong},
{"dictEncObjKeyCompare", (unsigned long)dictEncObjKeyCompare},
{"dictEncObjHash", (unsigned long)dictEncObjHash},
{"incrDecrCommand", (unsigned long)incrDecrCommand},
{"freeStringObject", (unsigned long)freeStringObject},
{"freeListObject", (unsigned long)freeListObject},
{"freeSetObject", (unsigned long)freeSetObject},
{"decrRefCount", (unsigned long)decrRefCount},
{"createObject", (unsigned long)createObject},
{"freeClient", (unsigned long)freeClient},
{"rdbLoad", (unsigned long)rdbLoad},
{"rdbSaveStringObject", (unsigned long)rdbSaveStringObject},
{"rdbSaveStringObjectRaw", (unsigned long)rdbSaveStringObjectRaw},
{"addReply", (unsigned long)addReply},
{"addReplySds", (unsigned long)addReplySds},
{"incrRefCount", (unsigned long)incrRefCount},
{"rdbSaveBackground", (unsigned long)rdbSaveBackground},
{"createStringObject", (unsigned long)createStringObject},
{"replicationFeedSlaves", (unsigned long)replicationFeedSlaves},
{"syncWithMaster", (unsigned long)syncWithMaster},
{"tryObjectSharing", (unsigned long)tryObjectSharing},
{"tryObjectEncoding", (unsigned long)tryObjectEncoding},
{"getDecodedObject", (unsigned long)getDecodedObject},
{"removeExpire", (unsigned long)removeExpire},
{"expireIfNeeded", (unsigned long)expireIfNeeded},
{"deleteIfVolatile", (unsigned long)deleteIfVolatile},
{"deleteKey", (unsigned long)deleteKey},
{"getExpire", (unsigned long)getExpire},
{"setExpire", (unsigned long)setExpire},
{"updateSlavesWaitingBgsave", (unsigned long)updateSlavesWaitingBgsave},
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
{"spopCommand", (unsigned long)spopCommand},
{"srandmemberCommand", (unsigned long)srandmemberCommand},
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
{"expireatCommand", (unsigned long)expireatCommand},
{"getsetCommand", (unsigned long)getsetCommand},
{"ttlCommand", (unsigned long)ttlCommand},
{"slaveofCommand", (unsigned long)slaveofCommand},
{"debugCommand", (unsigned long)debugCommand},
{"processCommand", (unsigned long)processCommand},
{"setupSigSegvAction", (unsigned long)setupSigSegvAction},
{"readQueryFromClient", (unsigned long)readQueryFromClient},
{"rdbRemoveTempFile", (unsigned long)rdbRemoveTempFile},
{"msetGenericCommand", (unsigned long)msetGenericCommand},
{"msetCommand", (unsigned long)msetCommand},
{"msetnxCommand", (unsigned long)msetnxCommand},
{"zslCreateNode", (unsigned long)zslCreateNode},
{"zslCreate", (unsigned long)zslCreate},
{"zslFreeNode",(unsigned long)zslFreeNode},
{"zslFree",(unsigned long)zslFree},
{"zslRandomLevel",(unsigned long)zslRandomLevel},
{"zslInsert",(unsigned long)zslInsert},
{"zslDelete",(unsigned long)zslDelete},
{"createZsetObject",(unsigned long)createZsetObject},
{"zaddCommand",(unsigned long)zaddCommand},
{"zrangeGenericCommand",(unsigned long)zrangeGenericCommand},
{"zrangeCommand",(unsigned long)zrangeCommand},
{"zrevrangeCommand",(unsigned long)zrevrangeCommand},
{"zremCommand",(unsigned long)zremCommand},
{"rdbSaveDoubleValue",(unsigned long)rdbSaveDoubleValue},
{"rdbLoadDoubleValue",(unsigned long)rdbLoadDoubleValue},
{"feedAppendOnlyFile",(unsigned long)feedAppendOnlyFile},
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
