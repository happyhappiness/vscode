#include <sys/socket.h>
#include <sys/stat.h>

void replicationDiscardCachedMaster(void);
void replicationResurrectCachedMaster(int newfd);

/* ---------------------------------- MASTER -------------------------------- */

void createReplicationBacklog(void) {
    redisAssert(server.repl_backlog == NULL);
    server.repl_backlog = zmalloc(server.repl_backlog_size);
    server.repl_backlog_histlen = 0;
    server.repl_backlog_idx = 0;
    /* When a new backlog buffer is created, we increment the replication
     * offset by one to make sure we'll not be able to PSYNC with any
     * previous slave. This is needed because we avoid incrementing the
     * master_repl_offset if no backlog exists nor slaves are attached. */
    server.master_repl_offset++;

    /* We don't have any data inside our buffer, but virtually the first
     * byte we have is the next byte that will be generated for the
     * replication stream. */
    server.repl_backlog_off = server.master_repl_offset+1;
}

/* This function is called when the user modifies the replication backlog
 * size at runtime. It is up to the function to both update the
 * server.repl_backlog_size and to resize the buffer and setup it so that
 * it contains the same data as the previous one (possibly less data, but
 * the most recent bytes, or the same data and more free space in case the
 * buffer is enlarged). */
void resizeReplicationBacklog(long long newsize) {
    if (newsize < REDIS_REPL_BACKLOG_MIN_SIZE)
        newsize = REDIS_REPL_BACKLOG_MIN_SIZE;
    if (server.repl_backlog_size == newsize) return;

    server.repl_backlog_size = newsize;
    if (server.repl_backlog != NULL) {
        /* What we actually do is to flush the old buffer and realloc a new
         * empty one. It will refill with new data incrementally.
         * The reason is that copying a few gigabytes adds latency and even
         * worse often we need to alloc additional space before freeing the
         * old buffer. */
        zfree(server.repl_backlog);
        server.repl_backlog = zmalloc(server.repl_backlog_size);
        server.repl_backlog_histlen = 0;
        server.repl_backlog_idx = 0;
        /* Next byte we have is... the next since the buffer is emtpy. */
        server.repl_backlog_off = server.master_repl_offset+1;
    }
}

void freeReplicationBacklog(void) {
    redisAssert(server.repl_backlog != NULL);
    zfree(server.repl_backlog);
    server.repl_backlog = NULL;
}

/* Add data to the replication backlog.
 * This function also increments the global replication offset stored at
 * server.master_repl_offset, because there is no case where we want to feed
 * the backlog without incrementing the buffer. */
void feedReplicationBacklog(void *ptr, size_t len) {
    unsigned char *p = ptr;

    server.master_repl_offset += len;

    /* This is a circular buffer, so write as much data we can at every
     * iteration and rewind the "idx" index if we reach the limit. */
    while(len) {
        size_t thislen = server.repl_backlog_size - server.repl_backlog_idx;
        if (thislen > len) thislen = len;
        memcpy(server.repl_backlog+server.repl_backlog_idx,p,thislen);
        server.repl_backlog_idx += thislen;
        if (server.repl_backlog_idx == server.repl_backlog_size)
            server.repl_backlog_idx = 0;
        len -= thislen;
        p += thislen;
        server.repl_backlog_histlen += thislen;
    }
    if (server.repl_backlog_histlen > server.repl_backlog_size)
        server.repl_backlog_histlen = server.repl_backlog_size;
    /* Set the offset of the first byte we have in the backlog. */
    server.repl_backlog_off = server.master_repl_offset -
                              server.repl_backlog_histlen + 1;
}

/* Wrapper for feedReplicationBacklog() that takes Redis string objects
 * as input. */
void feedReplicationBacklogWithObject(robj *o) {
    char llstr[REDIS_LONGSTR_SIZE];
    void *p;
    size_t len;

    if (o->encoding == REDIS_ENCODING_INT) {
        len = ll2string(llstr,sizeof(llstr),(long)o->ptr);
        p = llstr;
    } else {
        len = sdslen(o->ptr);
        p = o->ptr;
    }
    feedReplicationBacklog(p,len);
}

#define FEEDSLAVE_BUF_SIZE (1024*64)
void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
    listNode *ln;
    listIter li;
    int j, i, len;
    char buf[FEEDSLAVE_BUF_SIZE], *b = buf;
    char llstr[REDIS_LONGSTR_SIZE];
    int buf_left = FEEDSLAVE_BUF_SIZE;
    robj *o;

    /* If there aren't slaves, and there is no backlog buffer to populate,
     * we can return ASAP. */
    if (server.repl_backlog == NULL && listLength(slaves) == 0) return;

    /* We can't have slaves attached and no backlog. */
    redisAssert(!(listLength(slaves) != 0 && server.repl_backlog == NULL));

    /* What we do here is to try to write as much data as possible in a static
     * buffer "buf" that is used to create an object that is later sent to all
     * the slaves. This way we do the decoding only one time for most commands
     * not containing big payloads. */

    /* Create the SELECT command into the static buffer if needed. */
    if (server.slaveseldb != dictid) {
        char *selectcmd;
        size_t sclen;

        if (dictid >= 0 && dictid < REDIS_SHARED_SELECT_CMDS) {
            selectcmd = shared.select[dictid]->ptr;
            sclen = sdslen(selectcmd);
            memcpy(b,selectcmd,sclen);
            b += sclen;
            buf_left -= sclen;
        } else {
            int dictid_len;

            dictid_len = ll2string(llstr,sizeof(llstr),dictid);
            sclen = snprintf(b,buf_left,"*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
                dictid_len, llstr);
            b += sclen;
            buf_left -= sclen;
        }
    }
    server.slaveseldb = dictid;
   
    /* Add the multi bulk reply size to the static buffer, that is, the number
     * of arguments of the command to send to every slave. */
    b[0] = '*';
    len = ll2string(b+1,REDIS_LONGSTR_SIZE,argc);
    b += len+1;
    buf_left -= len;
    b[0] = '\r';
    b[1] = '\n';
    b += 2;
    buf_left -= 2;

    /* Try to use the static buffer for as much arguments is possible. */
    for (j = 0; j < argc; j++) {
        int objlen;
        char *objptr;

        if (argv[j]->encoding != REDIS_ENCODING_RAW &&
            argv[j]->encoding != REDIS_ENCODING_INT) {
            redisPanic("Unexpected encoding");
        }
        if (argv[j]->encoding == REDIS_ENCODING_RAW) {
            objlen = sdslen(argv[j]->ptr);
            objptr = argv[j]->ptr;
        } else {
            objlen = ll2string(llstr,REDIS_LONGSTR_SIZE,(long)argv[j]->ptr);
            objptr = llstr;
        }
        /* We need enough space for bulk reply encoding, newlines, and
         * the data itself. */
        if (buf_left < objlen+REDIS_LONGSTR_SIZE+32) break;

        /* Write $...CRLF */
        b[0] = '$';
        len = ll2string(b+1,REDIS_LONGSTR_SIZE,objlen);
        b += len+1;
        buf_left -= len;
        b[0] = '\r';
        b[1] = '\n';
        b += 2;
        buf_left -= 2;

        /* And data plus CRLF */
        memcpy(b,objptr,objlen);
        b += objlen;
        buf_left -= objlen;
        b[0] = '\r';
        b[1] = '\n';
        b += 2;
        buf_left -= 2;
    }

    /* Create an object with the static buffer content. */
    redisAssert(buf_left < FEEDSLAVE_BUF_SIZE);
    o = createStringObject(buf,b-buf);

    /* If we have a backlog, populate it with data and increment
     * the global replication offset. */
    if (server.repl_backlog) {
        feedReplicationBacklogWithObject(o);
        for (i = j; i < argc; i++) {
            char aux[REDIS_LONGSTR_SIZE+3];
            long objlen = stringObjectLen(argv[i]);

            /* We need to feed the buffer with the object as a bulk reply
             * not just as a plain string, so create the $..CRLF payload len 
             * ad add the final CRLF */
            aux[0] = '$';
            len = ll2string(aux+1,objlen,sizeof(aux)-1);
            aux[len+1] = '\r';
            aux[len+2] = '\n';
            feedReplicationBacklog(aux,len+3);
            feedReplicationBacklogWithObject(argv[j]);
            feedReplicationBacklogWithObject(shared.crlf);
        }
    }

    /* Write data to slaves. Here we do two things:
     * 1) We write the "o" object that was created using the accumulated
     *    static buffer.
     * 2) We write any additional argument of the command to replicate that
     *    was not written inside the static buffer for lack of space.
     */
    listRewind(slaves,&li);
    while((ln = listNext(&li))) {
        redisClient *slave = ln->value;
