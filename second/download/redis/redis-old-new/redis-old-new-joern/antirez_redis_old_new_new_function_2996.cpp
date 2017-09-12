void clusterCommand(redisClient *c) {
    if (server.cluster_enabled == 0) {
        addReplyError(c,"This instance has cluster support disabled");
        return;
    }

    if (!strcasecmp(c->argv[1]->ptr,"meet") && c->argc == 4) {
        clusterNode *n;
        struct sockaddr_in sa;
        long port;

        /* Perform sanity checks on IP/port */
        if (inet_aton(c->argv[2]->ptr,&sa.sin_addr) == 0) {
            addReplyError(c,"Invalid IP address in MEET");
            return;
        }
        if (getLongFromObjectOrReply(c, c->argv[3], &port, NULL) != REDIS_OK ||
                    port < 0 || port > (65535-REDIS_CLUSTER_PORT_INCR))
        {
            addReplyError(c,"Invalid TCP port specified");
            return;
        }

        /* Finally add the node to the cluster with a random name, this 
         * will get fixed in the first handshake (ping/pong). */
        n = createClusterNode(NULL,REDIS_NODE_HANDSHAKE|REDIS_NODE_MEET);
        strncpy(n->ip,inet_ntoa(sa.sin_addr),sizeof(n->ip));
        n->port = port;
        clusterAddNode(n);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"nodes") && c->argc == 2) {
        robj *o;
        sds ci = clusterGenNodesDescription();

        o = createObject(REDIS_STRING,ci);
        addReplyBulk(c,o);
        decrRefCount(o);
    } else if (!strcasecmp(c->argv[1]->ptr,"addslots") && c->argc >= 3) {
        int j;
        long long slot;
        unsigned char *slots = zmalloc(REDIS_CLUSTER_SLOTS);

        memset(slots,0,REDIS_CLUSTER_SLOTS);
        /* Check that all the arguments are parsable and that all the
         * slots are not already busy. */
        for (j = 2; j < c->argc; j++) {
            if (getLongLongFromObject(c->argv[j],&slot) != REDIS_OK ||
                slot < 0 || slot > REDIS_CLUSTER_SLOTS)
            {
                addReplyError(c,"Invalid or out of range slot index");
                zfree(slots);
                return;
            }
            if (server.cluster.slots[slot]) {
                addReplyErrorFormat(c,"Slot %lld is already busy", slot);
                zfree(slots);
                return;
            }
            if (slots[slot]++ == 1) {
                addReplyErrorFormat(c,"Slot %d specified multiple times",
                    (int)slot);
                zfree(slots);
                return;
            }
        }
        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
            if (slots[j]) {
                int retval = clusterAddSlot(server.cluster.myself,j);
                
                redisAssert(retval == REDIS_OK);
            }
        }
        zfree(slots);
        clusterUpdateState();
        clusterSaveConfigOrDie();
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
        char *statestr[] = {"ok","fail","needhelp"};
        int slots_assigned = 0, slots_ok = 0, slots_pfail = 0, slots_fail = 0;
        int j;

        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
            clusterNode *n = server.cluster.slots[j];

            if (n == NULL) continue;
            slots_assigned++;
            if (n->flags & REDIS_NODE_FAIL) {
                slots_fail++;
            } else if (n->flags & REDIS_NODE_PFAIL) {
                slots_pfail++;
            } else {
                slots_ok++;
            }
        }

        sds info = sdscatprintf(sdsempty(),
            "cluster_state:%s\r\n"
            "cluster_slots_assigned:%d\r\n"
            "cluster_slots_ok:%d\r\n"
            "cluster_slots_pfail:%d\r\n"
            "cluster_slots_fail:%d\r\n"
            , statestr[server.cluster.state],
            slots_assigned,
            slots_ok,
            slots_pfail,
            slots_fail
        );
        addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
            (unsigned long)sdslen(info)));
        addReplySds(c,info);
        addReply(c,shared.crlf);
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
}