            }
        }
        if (min_pong_node) {
            redisLog(REDIS_DEBUG,"Pinging node %.40s", min_pong_node->name);
            clusterSendPing(min_pong_node->link, CLUSTERMSG_TYPE_PING);
        }
    }
