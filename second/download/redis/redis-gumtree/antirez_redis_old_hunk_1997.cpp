        clusterSendMFStart(myself->slaveof);
        redisLog(REDIS_WARNING,"Manual failover user request accepted.");
        addReply(c,shared.ok);
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
