    while(fgets(line,maxline,fp) != NULL) {
        int argc;
        sds *argv = sdssplitargs(line,&argc);
        clusterNode *n, *master;
        char *p, *s;

        /* Create this node if it does not exist */
        n = clusterLookupNode(argv[0]);
        if (!n) {
            n = createClusterNode(argv[0],0);
            clusterAddNode(n);
        }
        /* Address and port */
        if ((p = strchr(argv[1],':')) == NULL) goto fmterr;
        *p = '\0';
        memcpy(n->ip,argv[1],strlen(argv[1])+1);
        n->port = atoi(p+1);

        /* Parse flags */
        p = s = argv[2];
        while(p) {
            p = strchr(s,',');
            if (p) *p = '\0';
            if (!strcasecmp(s,"myself")) {
                redisAssert(server.cluster.myself == NULL);
                server.cluster.myself = n;
                n->flags |= REDIS_NODE_MYSELF;
            } else if (!strcasecmp(s,"master")) {
                n->flags |= REDIS_NODE_MASTER;
            } else if (!strcasecmp(s,"slave")) {
                n->flags |= REDIS_NODE_SLAVE;
            } else if (!strcasecmp(s,"fail?")) {
                n->flags |= REDIS_NODE_PFAIL;
            } else if (!strcasecmp(s,"fail")) {
                n->flags |= REDIS_NODE_FAIL;
            } else if (!strcasecmp(s,"handshake")) {
                n->flags |= REDIS_NODE_HANDSHAKE;
            } else if (!strcasecmp(s,"noaddr")) {
                n->flags |= REDIS_NODE_NOADDR;
            } else {
                redisPanic("Unknown flag in redis cluster config file");
            }
            if (p) s = p+1;
        }

        /* Get master if any. Set the master and populate master's
         * slave list. */
        if (argv[3][0] != '-') {
            master = clusterLookupNode(argv[3]);
            if (!master) {
                master = createClusterNode(argv[3],0);
                clusterAddNode(master);
            }
            n->slaveof = master;
            clusterNodeAddSlave(master,n);
        }

        /* Populate hash slots served by this instance. */
        for (j = 7; j < argc; j++) {
            int start, stop;

            if ((p = strchr(argv[j],'-')) != NULL) {
                *p = '\0';
                start = atoi(argv[j]);
                stop = atoi(p+1);
            } else {
                start = stop = atoi(argv[j]);
            }
            while(start <= stop) clusterAddSlot(n, start++);
        }

        sdssplitargs_free(argv,argc);
    }
    zfree(line);
    fclose(fp);

    /* Config sanity check */
    redisAssert(server.cluster.myself != NULL);
    redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s",
        server.cluster.myself->name);
    return REDIS_OK;
