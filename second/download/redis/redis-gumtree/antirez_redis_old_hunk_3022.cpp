            clusterSaveConfigOrDie();
        }
    } else {
        redisLog(REDIS_NOTICE,"Received unknown packet type: %d", type);
    }
    return 1;
}
