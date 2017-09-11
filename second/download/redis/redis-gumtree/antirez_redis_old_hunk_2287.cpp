                failing->flags |= REDIS_NODE_FAIL;
                failing->fail_time = time(NULL);
                failing->flags &= ~REDIS_NODE_PFAIL;
                clusterUpdateState();
                clusterSaveConfigOrDie();
            }
        } else {
            redisLog(REDIS_NOTICE,
