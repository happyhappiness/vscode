        resetManualFailover();
        server.cluster->mf_end = mstime() + REDIS_CLUSTER_MF_TIMEOUT;
        clusterSendMFStart(myself->slaveof);
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
