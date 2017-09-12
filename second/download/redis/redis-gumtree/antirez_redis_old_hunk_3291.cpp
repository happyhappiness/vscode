            failing->flags |= REDIS_NODE_FAIL;
            failing->flags &= ~REDIS_NODE_PFAIL;
            clusterUpdateState();
        }
    } else {
        redisLog(REDIS_NOTICE,"Received unknown packet type: %d", type);
