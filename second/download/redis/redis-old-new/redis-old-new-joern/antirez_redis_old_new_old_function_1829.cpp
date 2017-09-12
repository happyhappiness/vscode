void sentinelCommand(redisClient *c) {
    if (!strcasecmp(c->argv[1]->ptr,"masters")) {
        /* SENTINEL MASTERS */
        if (c->argc != 2) goto numargserr;
        addReplyDictOfRedisInstances(c,sentinel.masters);
    } else if (!strcasecmp(c->argv[1]->ptr,"master")) {
        /* SENTINEL MASTER <name> */
        sentinelRedisInstance *ri;

        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
            == NULL) return;
        addReplySentinelRedisInstance(c,ri);
    } else if (!strcasecmp(c->argv[1]->ptr,"slaves")) {
        /* SENTINEL SLAVES <master-name> */
        sentinelRedisInstance *ri;

        if (c->argc != 3) goto numargserr;
        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2])) == NULL)
            return;
        addReplyDictOfRedisInstances(c,ri->slaves);
    } else if (!strcasecmp(c->argv[1]->ptr,"sentinels")) {
        /* SENTINEL SENTINELS <master-name> */
        sentinelRedisInstance *ri;

        if (c->argc != 3) goto numargserr;
        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2])) == NULL)
            return;
        addReplyDictOfRedisInstances(c,ri->sentinels);
    } else if (!strcasecmp(c->argv[1]->ptr,"is-master-down-by-addr")) {
        /* SENTINEL IS-MASTER-DOWN-BY-ADDR <ip> <port> <current-epoch> <runid>*/
        sentinelRedisInstance *ri;
        long long req_epoch;
        uint64_t leader_epoch = 0;
        char *leader = NULL;
        long port;
        int isdown = 0;

        if (c->argc != 6) goto numargserr;
        if (getLongFromObjectOrReply(c,c->argv[3],&port,NULL) != REDIS_OK ||
            getLongLongFromObjectOrReply(c,c->argv[4],&req_epoch,NULL)
                                                              != REDIS_OK)
            return;
        ri = getSentinelRedisInstanceByAddrAndRunID(sentinel.masters,
            c->argv[2]->ptr,port,NULL);

        /* It exists? Is actually a master? Is subjectively down? It's down.
         * Note: if we are in tilt mode we always reply with "0". */
        if (!sentinel.tilt && ri && (ri->flags & SRI_S_DOWN) &&
                                    (ri->flags & SRI_MASTER))
            isdown = 1;

        /* Vote for the master (or fetch the previous vote) if the request
         * includes a runid, otherwise the sender is not seeking for a vote. */
        if (ri && ri->flags & SRI_MASTER && strcasecmp(c->argv[5]->ptr,"*")) {
            leader = sentinelVoteLeader(ri,(uint64_t)req_epoch,
                                            c->argv[5]->ptr,
                                            &leader_epoch);
        }

        /* Reply with a three-elements multi-bulk reply:
         * down state, leader, vote epoch. */
        addReplyMultiBulkLen(c,3);
        addReply(c, isdown ? shared.cone : shared.czero);
        addReplyBulkCString(c, leader ? leader : "*");
        addReplyLongLong(c, (long long)leader_epoch);
        if (leader) sdsfree(leader);
    } else if (!strcasecmp(c->argv[1]->ptr,"reset")) {
        /* SENTINEL RESET <pattern> */
        if (c->argc != 3) goto numargserr;
        addReplyLongLong(c,sentinelResetMastersByPattern(c->argv[2]->ptr,SENTINEL_GENERATE_EVENT));
    } else if (!strcasecmp(c->argv[1]->ptr,"get-master-addr-by-name")) {
        /* SENTINEL GET-MASTER-ADDR-BY-NAME <master-name> */
        sentinelRedisInstance *ri;

        if (c->argc != 3) goto numargserr;
        ri = sentinelGetMasterByName(c->argv[2]->ptr);
        if (ri == NULL) {
            addReply(c,shared.nullmultibulk);
        } else if (ri->info_refresh == 0) {
            addReplySds(c,sdsnew("-IDONTKNOW I have not enough information to reply. Please ask another Sentinel.\r\n"));
        } else {
            sentinelAddr *addr = sentinelGetCurrentMasterAddress(ri);

            addReplyMultiBulkLen(c,2);
            addReplyBulkCString(c,addr->ip);
            addReplyBulkLongLong(c,addr->port);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"failover")) {
        /* SENTINEL FAILOVER <master-name> */
        sentinelRedisInstance *ri;

        if (c->argc != 3) goto numargserr;
        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2])) == NULL)
            return;
        if (ri->flags & SRI_FAILOVER_IN_PROGRESS) {
            addReplySds(c,sdsnew("-INPROG Failover already in progress\r\n"));
            return;
        }
        if (sentinelSelectSlave(ri) == NULL) {
            addReplySds(c,sdsnew("-NOGOODSLAVE No suitable slave to promote\r\n"));
            return;
        }
        redisLog(REDIS_WARNING,"Executing user requested FAILOVER of '%s'",
            ri->name);
        sentinelStartFailover(ri);
        ri->flags |= SRI_FORCE_FAILOVER;
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"pending-scripts")) {
        /* SENTINEL PENDING-SCRIPTS */

        if (c->argc != 2) goto numargserr;
        sentinelPendingScriptsCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"monitor")) {
        /* SENTINEL MONITOR <name> <ip> <port> <quorum> */
        long quorum, port;
        char buf[32];

        if (c->argc != 6) goto numargserr;
        if (getLongFromObjectOrReply(c,c->argv[5],&quorum,"Invalid quorum")
            != REDIS_OK) return;
        if (getLongFromObjectOrReply(c,c->argv[4],&port,"Invalid port")
            != REDIS_OK) return;
        /* Make sure the IP field is actually a valid IP before passing it
         * to createSentinelRedisInstance(), otherwise we may trigger a
         * DNS lookup at runtime. */
        if (anetResolveIP(NULL,c->argv[3]->ptr,buf,sizeof(buf)) == ANET_ERR) {
            addReplyError(c,"Invalid IP address specified");
            return;
        }
        if (createSentinelRedisInstance(c->argv[2]->ptr,SRI_MASTER,
                c->argv[3]->ptr,port,quorum,NULL) == NULL)
        {
            switch(errno) {
            case EBUSY:
                addReplyError(c,"Duplicated master name");
                break;
            case EINVAL:
                addReplyError(c,"Invalid port number");
                break;
            default:
                addReplyError(c,"Unspecified error adding the instance");
                break;
            }
        } else {
            sentinelFlushConfig();
            addReply(c,shared.ok);
        }
    } else {
        addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                               (char*)c->argv[1]->ptr);
    }
    return;

numargserr:
    addReplyErrorFormat(c,"Wrong number of commands for 'sentinel %s'",
                          (char*)c->argv[1]->ptr);
}