                strcmp(ip,myself->ip))
            {
                memcpy(myself->ip,ip,REDIS_IP_STR_LEN);
                redisLog(REDIS_WARNING,"IP address for this node updated to %s",
                    myself->ip);
                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
            }
