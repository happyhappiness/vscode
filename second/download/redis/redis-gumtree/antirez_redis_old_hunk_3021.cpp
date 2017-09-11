            clusterUpdateState();
            clusterSaveConfigOrDie();
        }
    } else {
        redisLog(REDIS_WARNING,"Received unknown packet type: %d", type);
    }
