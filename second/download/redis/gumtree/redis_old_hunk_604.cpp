                dictSize(ri->slaves),
                dictSize(ri->sentinels)+1);
        }
        dictReleaseIterator(di);
    }

    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
        (unsigned long)sdslen(info)));
    addReplySds(c,info);
    addReply(c,shared.crlf);
}

/* Implements Sentinel verison of the ROLE command. The output is
 * "sentinel" and the list of currently monitored master names. */
void sentinelRoleCommand(redisClient *c) {
    dictIterator *di;
    dictEntry *de;

    addReplyMultiBulkLen(c,2);
    addReplyBulkCBuffer(c,"sentinel",8);
    addReplyMultiBulkLen(c,dictSize(sentinel.masters));
