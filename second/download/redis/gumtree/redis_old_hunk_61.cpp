#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>

/* ---------------------------------- MASTER -------------------------------- */

void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
    listNode *ln;
    listIter li;
    int j;

    listRewind(slaves,&li);
    while((ln = listNext(&li))) {
        redisClient *slave = ln->value;

        /* Don't feed slaves that are still waiting for BGSAVE to start */
        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) continue;

        /* Feed slaves that are waiting for the initial SYNC (so these commands
         * are queued in the output buffer until the initial SYNC completes),
         * or are already in sync with the master. */
        if (slave->slaveseldb != dictid) {
            robj *selectcmd;

            if (dictid >= 0 && dictid < REDIS_SHARED_SELECT_CMDS) {
                selectcmd = shared.select[dictid];
                incrRefCount(selectcmd);
            } else {
                selectcmd = createObject(REDIS_STRING,
                    sdscatprintf(sdsempty(),"select %d\r\n",dictid));
            }
            addReply(slave,selectcmd);
            decrRefCount(selectcmd);
            slave->slaveseldb = dictid;
        }
        addReplyMultiBulkLen(slave,argc);
        for (j = 0; j < argc; j++) addReplyBulk(slave,argv[j]);
    }
}

void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **argv, int argc) {
    listNode *ln;
    listIter li;
    int j, port;
    sds cmdrepr = sdsnew("+");
    robj *cmdobj;
    char ip[32];
    struct timeval tv;

    gettimeofday(&tv,NULL);
    cmdrepr = sdscatprintf(cmdrepr,"%ld.%06ld ",(long)tv.tv_sec,(long)tv.tv_usec);
    if (c->flags & REDIS_LUA_CLIENT) {
        cmdrepr = sdscatprintf(cmdrepr,"[%d lua] ",dictid);
    } else if (c->flags & REDIS_UNIX_SOCKET) {
        cmdrepr = sdscatprintf(cmdrepr,"[%d unix:%s] ",dictid,server.unixsocket);
    } else {
        anetPeerToString(c->fd,ip,&port);
        cmdrepr = sdscatprintf(cmdrepr,"[%d %s:%d] ",dictid,ip,port);
    }

    for (j = 0; j < argc; j++) {
        if (argv[j]->encoding == REDIS_ENCODING_INT) {
            cmdrepr = sdscatprintf(cmdrepr, "\"%ld\"", (long)argv[j]->ptr);
        } else {
